/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 13:45:03 by ade-garr          #+#    #+#             */
/*   Updated: 2020/07/21 17:25:46 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_raycasting_west2(t_param *param, t_raycast *raycast)
{
	while (raycast->drawstart < raycast->drawend)
	{
		raycast->texy = raycast->texpos;
		if (raycast->texy >= param->tex_w->height)
			raycast->texy = param->tex_w->height - 1;
		raycast->texpos = raycast->texpos + raycast->step;
		raycast->adr = param->imgadr + (raycast->drawstart *
		param->imglenght + raycast->x * (param->imgbpp / 8));
		*(unsigned int *)raycast->adr = param->tex_w->tab[param->tex_w->width *
		raycast->texy + raycast->texx];
		raycast->drawstart++;
	}
	raycast->xfloorcell = raycast->drawend;
	while (raycast->xfloorcell < param->winy)
	{
		raycast->adr = param->imgadr + (raycast->xfloorcell *
		param->imglenght + raycast->x * (param->imgbpp / 8));
		*(unsigned int *)raycast->adr = param->floorcolor;
		raycast->xfloorcell++;
	}
	param->tab_dist_wall[raycast->x] = raycast->walldist;
	raycast->x++;
}

void	ft_raycasting_west(t_param *param, t_raycast *raycast)
{
	raycast->texx = raycast->wallx * param->tex_w->width;
	if (raycast->side == 0 && raycast->raydirx > 0)
		raycast->texx = param->tex_w->width - raycast->texx - 1;
	if (raycast->side == 1 && raycast->raydiry < 0)
		raycast->texx = param->tex_w->width - raycast->texx - 1;
	raycast->step = 1.0 * param->tex_w->height / raycast->lineheight;
	raycast->texpos = (raycast->drawstart - raycast->wallcrouch -
	param->updown - param->winy / 2 + raycast->lineheight / 2) * raycast->step;
	raycast->xfloorcell = 0;
	while (raycast->xfloorcell < raycast->drawstart)
	{
		raycast->adr = param->imgadr + (raycast->xfloorcell *
		param->imglenght + raycast->x * (param->imgbpp / 8));
		*(unsigned int *)raycast->adr = param->cellcolor;
		raycast->xfloorcell++;
	}
	ft_raycasting_west2(param, raycast);
}

void	ft_raycasting_east2(t_param *param, t_raycast *raycast)
{
	while (raycast->drawstart < raycast->drawend)
	{
		raycast->texy = raycast->texpos;
		if (raycast->texy >= param->tex_e->height)
			raycast->texy = param->tex_e->height - 1;
		raycast->texpos = raycast->texpos + raycast->step;
		raycast->adr = param->imgadr + (raycast->drawstart *
		param->imglenght + raycast->x * (param->imgbpp / 8));
		*(unsigned int *)raycast->adr = param->tex_e->tab[param->tex_e->width *
		raycast->texy + raycast->texx];
		raycast->drawstart++;
	}
	raycast->xfloorcell = raycast->drawend;
	while (raycast->xfloorcell < param->winy)
	{
		raycast->adr = param->imgadr + (raycast->xfloorcell *
		param->imglenght + raycast->x * (param->imgbpp / 8));
		*(unsigned int *)raycast->adr = param->floorcolor;
		raycast->xfloorcell++;
	}
	param->tab_dist_wall[raycast->x] = raycast->walldist;
	raycast->x++;
}

void	ft_raycasting_east(t_param *param, t_raycast *raycast)
{
	raycast->texx = raycast->wallx * param->tex_e->width;
	if (raycast->side == 0 && raycast->raydirx > 0)
		raycast->texx = param->tex_e->width - raycast->texx - 1;
	if (raycast->side == 1 && raycast->raydiry < 0)
		raycast->texx = param->tex_e->width - raycast->texx - 1;
	raycast->step = 1.0 * param->tex_e->height / raycast->lineheight;
	raycast->texpos = (raycast->drawstart - raycast->wallcrouch -
	param->updown - param->winy / 2 + raycast->lineheight / 2) * raycast->step;
	raycast->xfloorcell = 0;
	while (raycast->xfloorcell < raycast->drawstart)
	{
		raycast->adr = param->imgadr + (raycast->xfloorcell *
		param->imglenght + raycast->x * (param->imgbpp / 8));
		*(unsigned int *)raycast->adr = param->cellcolor;
		raycast->xfloorcell++;
	}
	ft_raycasting_east2(param, raycast);
}
