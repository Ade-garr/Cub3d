/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 13:45:42 by ade-garr          #+#    #+#             */
/*   Updated: 2020/07/13 13:49:41 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_raycasting_south2(t_param *param, t_raycast *raycast)
{
	while (raycast->drawStart < raycast->drawEnd)
	{
		raycast->texY = raycast->texPos;
		if (raycast->texY >= param->tex_S->height)
			raycast->texY = param->tex_S->height - 1;
		raycast->texPos = raycast->texPos + raycast->step;
		raycast->adr = param->imgadr + (raycast->drawStart * param->imglenght + raycast->x * (param->imgbpp / 8));
		*(unsigned int *)raycast->adr = param->tex_S->tab[param->tex_S->width * raycast->texY + raycast->texX];
		raycast->drawStart++;
	}
	raycast->xfloorcell = raycast->drawEnd;
	while (raycast->xfloorcell < param->winY)
	{
		raycast->adr = param->imgadr + (raycast->xfloorcell * param->imglenght + raycast->x * (param->imgbpp / 8));
		*(unsigned int *)raycast->adr = param->floorcolor;
		raycast->xfloorcell++;
	}
	param->tab_dist_wall[raycast->x] = raycast->wallDist;
	raycast->x++;
}

void	ft_raycasting_south(t_param *param, t_raycast *raycast)
{
	raycast->texX = raycast->wallX * param->tex_S->width;
	if (raycast->side == 0 && raycast->rayDirX > 0)
		raycast->texX = param->tex_S->width - raycast->texX - 1;
	if (raycast->side == 1 && raycast->rayDirY < 0)
		raycast->texX = param->tex_S->width - raycast->texX - 1;
	raycast->step = 1.0 * param->tex_S->height / raycast->lineHeight;
	raycast->texPos = (raycast->drawStart - param->winY / 2 + raycast->lineHeight / 2) * raycast->step;
	raycast->xfloorcell = 0;
	while (raycast->xfloorcell < raycast->drawStart)
	{
		raycast->adr = param->imgadr + (raycast->xfloorcell * param->imglenght + raycast->x * (param->imgbpp / 8));
		*(unsigned int *)raycast->adr = param->cellcolor;
		raycast->xfloorcell++;
	}
	ft_raycasting_south2(param, raycast);
}

void	ft_raycasting_north2(t_param *param, t_raycast *raycast)
{
	while (raycast->drawStart < raycast->drawEnd)
	{
		raycast->texY = raycast->texPos;
		if (raycast->texY >= param->tex_N->height)
			raycast->texY = param->tex_N->height - 1;
		raycast->texPos = raycast->texPos + raycast->step;
		raycast->adr = param->imgadr + (raycast->drawStart * param->imglenght + raycast->x * (param->imgbpp / 8));
		*(unsigned int *)raycast->adr = param->tex_N->tab[param->tex_N->width * raycast->texY + raycast->texX];
		raycast->drawStart++;
	}
	raycast->xfloorcell = raycast->drawEnd;
	while (raycast->xfloorcell < param->winY)
	{
		raycast->adr = param->imgadr + (raycast->xfloorcell * param->imglenght + raycast->x * (param->imgbpp / 8));
		*(unsigned int *)raycast->adr = param->floorcolor;
		raycast->xfloorcell++;
	}
	param->tab_dist_wall[raycast->x] = raycast->wallDist;
	raycast->x++;
}

void	ft_raycasting_north(t_param *param, t_raycast *raycast)
{
	raycast->texX = raycast->wallX * param->tex_N->width;
	if (raycast->side == 0 && raycast->rayDirX > 0)
		raycast->texX = param->tex_N->width - raycast->texX - 1;
	if (raycast->side == 1 && raycast->rayDirY < 0)
		raycast->texX = param->tex_N->width - raycast->texX - 1;
	raycast->step = 1.0 * param->tex_N->height / raycast->lineHeight;
	raycast->texPos = (raycast->drawStart - param->winY / 2 + raycast->lineHeight / 2) * raycast->step;
	raycast->xfloorcell = 0;
	while (raycast->xfloorcell < raycast->drawStart)
	{
		raycast->adr = param->imgadr + (raycast->xfloorcell * param->imglenght + raycast->x * (param->imgbpp / 8));
		*(unsigned int *)raycast->adr = param->cellcolor;
		raycast->xfloorcell++;
	}
	ft_raycasting_north2(param, raycast);
}