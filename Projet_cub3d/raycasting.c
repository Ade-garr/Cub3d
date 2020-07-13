/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 13:43:48 by ade-garr          #+#    #+#             */
/*   Updated: 2020/07/13 13:49:38 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_raycasting5(t_param *param, t_raycast *raycast)
{
	if (raycast->side == 0)
		raycast->wallDist = (raycast->mapX - param->posX + (1 - raycast->stepX) / 2) / raycast->rayDirX;
	else
		raycast->wallDist = (raycast->mapY - param->posY + (1 - raycast->stepY) / 2) / raycast->rayDirY;
	raycast->lineHeight = param->winY / raycast->wallDist;
	raycast->lineHeight = (raycast->lineHeight < 0) ? INT_MAX : raycast->lineHeight;
	raycast->drawStart = -raycast->lineHeight / 2 + param->winY / 2;
	if (raycast->drawStart < 0)
		raycast->drawStart = 0;
	raycast->drawEnd = raycast->lineHeight / 2 + param->winY / 2;
	if (raycast->drawEnd >= param->winY)
		raycast->drawEnd = param->winY - 1;
	if (raycast->side == 0)
		raycast->wallX = param->posY + raycast->wallDist * raycast->rayDirY;
	else
		raycast->wallX = param->posX + raycast->wallDist * raycast->rayDirX;
	raycast->wallX -= floor(raycast->wallX);
}

void	ft_raycasting4(t_param *param, t_raycast *raycast)
{
	while (raycast->hit == 0)
	{
		if (raycast->sideDistX < raycast->sideDistY)
		{
			raycast->sideDistX += raycast->deltaDistX;
			raycast->mapX += raycast->stepX;
			raycast->side = 0;
		}
		else
		{
			raycast->sideDistY += raycast->deltaDistY;
			raycast->mapY += raycast->stepY;
			raycast->side = 1;
		}
		if (param->worldMap[raycast->mapY][raycast->mapX] == '1')
			raycast->hit = 1;
	}
}	

void	ft_raycasting3(t_param *param, t_raycast *raycast)
{
		if (raycast->rayDirY < 0)
		{
			raycast->stepY = -1;
			raycast->sideDistY = (param->posY - raycast->mapY) * raycast->deltaDistY;
		}
		else
		{
			raycast->stepY = 1;
			raycast->sideDistY = (raycast->mapY + 1.0 - param->posY) * raycast->deltaDistY;
		}
}

void	ft_raycasting2(t_param *param, t_raycast *raycast)
{
	raycast->cameraX = 2 * raycast->x / param->winX - 1;
	raycast->rayDirX = param->dirX + param->planeX * raycast->cameraX;
	raycast->rayDirY = param->dirY + param->planeY * raycast->cameraX;
	raycast->mapX = param->posX;
	raycast->mapY = param->posY;
	raycast->deltaDistX = fabs(1 / raycast->rayDirX);
	raycast->deltaDistY = fabs(1 / raycast->rayDirY);
	raycast->hit = 0;
	if (raycast->rayDirX < 0)
	{
		raycast->stepX = -1;
		raycast->sideDistX = (param->posX - raycast->mapX) * raycast->deltaDistX;
	}
	else
	{
		raycast->stepX = 1;
		raycast->sideDistX = (raycast->mapX + 1.0 - param->posX) * raycast->deltaDistX;
	}
}

void	ft_raycasting(t_param *param)
{
	t_raycast	*raycast;
	t_raycast	struct_raycast;

	raycast = &struct_raycast;
	raycast->x = 0;
	while (raycast->x < param->winX)
	{
		ft_raycasting2(param, raycast);
		ft_raycasting3(param, raycast);
		ft_raycasting4(param, raycast);
		ft_raycasting5(param, raycast);
		if (raycast->side == 1 && raycast->rayDirY < 0)
			ft_raycasting_north(param, raycast);
		if (raycast->side == 1 && raycast->rayDirY > 0)
			ft_raycasting_south(param, raycast);
		if (raycast->side == 0 && raycast->rayDirX < 0)
			ft_raycasting_west(param, raycast);
		if (raycast->side == 0 && raycast->rayDirX > 0)
			ft_raycasting_east(param, raycast);
	}
	ft_spritecasting(param);
}