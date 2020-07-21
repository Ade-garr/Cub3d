/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 13:43:48 by ade-garr          #+#    #+#             */
/*   Updated: 2020/07/21 17:22:08 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_raycasting5(t_param *param, t_raycast *raycast)
{
	if (raycast->side == 0)
		raycast->walldist = (raycast->mapx - param->posx +
		(1 - raycast->stepx) / 2) / raycast->raydirx;
	else
		raycast->walldist = (raycast->mapy - param->posy +
		(1 - raycast->stepy) / 2) / raycast->raydiry;
	raycast->lineheight = param->winy / raycast->walldist;
	raycast->lineheight = (raycast->lineheight < 0) ?
	INT_MAX : raycast->lineheight;
	raycast->drawstart = -raycast->lineheight / 2 + param->winy / 2;
	raycast->wallcrouch = param->crouch / raycast->walldist;
	raycast->drawstart += raycast->wallcrouch;
	raycast->drawstart += param->updown;
	if (raycast->drawstart < 0)
		raycast->drawstart = 0;
	raycast->drawend = raycast->lineheight / 2 + param->winy / 2;
	raycast->drawend += raycast->wallcrouch;
	raycast->drawend += param->updown;
	if (raycast->drawend > param->winy)
		raycast->drawend = param->winy;
	if (raycast->side == 0)
		raycast->wallx = param->posy + raycast->walldist * raycast->raydiry;
	else
		raycast->wallx = param->posx + raycast->walldist * raycast->raydirx;
	raycast->wallx -= floor(raycast->wallx);
}

void	ft_raycasting4(t_param *param, t_raycast *raycast)
{
	while (raycast->hit == 0)
	{
		if (raycast->sidedistx < raycast->sidedisty)
		{
			raycast->sidedistx += raycast->deltadistx;
			raycast->mapx += raycast->stepx;
			raycast->side = 0;
		}
		else
		{
			raycast->sidedisty += raycast->deltadisty;
			raycast->mapy += raycast->stepy;
			raycast->side = 1;
		}
		if (param->worldmap[raycast->mapy][raycast->mapx] == '1')
			raycast->hit = 1;
	}
}

void	ft_raycasting3(t_param *param, t_raycast *raycast)
{
	if (raycast->raydiry < 0)
	{
		raycast->stepy = -1;
		raycast->sidedisty = (param->posy - raycast->mapy) *
		raycast->deltadisty;
	}
	else
	{
		raycast->stepy = 1;
		raycast->sidedisty = (raycast->mapy + 1.0 - param->posy) *
		raycast->deltadisty;
	}
}

void	ft_raycasting2(t_param *param, t_raycast *raycast)
{
	raycast->camerax = 2 * raycast->x / param->winx - 1;
	raycast->raydirx = param->dirx + param->planex * raycast->camerax;
	raycast->raydiry = param->diry + param->planey * raycast->camerax;
	raycast->mapx = param->posx;
	raycast->mapy = param->posy;
	raycast->deltadistx = fabs(1 / raycast->raydirx);
	raycast->deltadisty = fabs(1 / raycast->raydiry);
	raycast->hit = 0;
	if (raycast->raydirx < 0)
	{
		raycast->stepx = -1;
		raycast->sidedistx = (param->posx - raycast->mapx) *
		raycast->deltadistx;
	}
	else
	{
		raycast->stepx = 1;
		raycast->sidedistx = (raycast->mapx + 1.0 - param->posx) *
		raycast->deltadistx;
	}
}

void	ft_raycasting(t_param *param)
{
	t_raycast	*raycast;
	t_raycast	struct_raycast;

	raycast = &struct_raycast;
	raycast->x = 0;
	while (raycast->x < param->winx)
	{
		ft_raycasting2(param, raycast);
		ft_raycasting3(param, raycast);
		ft_raycasting4(param, raycast);
		ft_raycasting5(param, raycast);
		if (raycast->side == 1 && raycast->raydiry < 0)
			ft_raycasting_north(param, raycast);
		if (raycast->side == 1 && raycast->raydiry > 0)
			ft_raycasting_south(param, raycast);
		if (raycast->side == 0 && raycast->raydirx < 0)
			ft_raycasting_west(param, raycast);
		if (raycast->side == 0 && raycast->raydirx > 0)
			ft_raycasting_east(param, raycast);
	}
	ft_spritecasting(param);
	if (param->winx >= 400 && param->winy >= 400)
		ft_hud(param);
}
