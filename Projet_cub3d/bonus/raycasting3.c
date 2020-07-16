/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 13:45:42 by ade-garr          #+#    #+#             */
/*   Updated: 2020/07/13 20:17:22 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_raycasting_south2(t_param *param, t_raycast *raycast)
{
	while (raycast->drawstart < raycast->drawend)
	{
		raycast->texy = raycast->texpos;
		if (raycast->texy >= param->tex_s->height)
			raycast->texy = param->tex_s->height - 1;
		raycast->texpos = raycast->texpos + raycast->step;
		raycast->adr = param->imgadr + (raycast->drawstart *
		param->imglenght + raycast->x * (param->imgbpp / 8));
		*(unsigned int *)raycast->adr = param->tex_s->tab[param->tex_s->width *
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

void	ft_raycasting_south(t_param *param, t_raycast *raycast)
{
	raycast->texx = raycast->wallx * param->tex_s->width;
	if (raycast->side == 0 && raycast->raydirx > 0)
		raycast->texx = param->tex_s->width - raycast->texx - 1;
	if (raycast->side == 1 && raycast->raydiry < 0)
		raycast->texx = param->tex_s->width - raycast->texx - 1;
	raycast->step = 1.0 * param->tex_s->height / raycast->lineheight;
	raycast->texpos = (raycast->drawstart - param->winy / 2 +
	raycast->lineheight / 2) * raycast->step;
	raycast->xfloorcell = 0;
	while (raycast->xfloorcell < raycast->drawstart)
	{
		raycast->adr = param->imgadr + (raycast->xfloorcell *
		param->imglenght + raycast->x * (param->imgbpp / 8));
		*(unsigned int *)raycast->adr = param->cellcolor;
		raycast->xfloorcell++;
	}
	ft_raycasting_south2(param, raycast);
}

void	ft_raycasting_north2(t_param *param, t_raycast *raycast)
{
	while (raycast->drawstart < raycast->drawend)
	{
		raycast->texy = raycast->texpos;
		if (raycast->texy >= param->tex_n->height)
			raycast->texy = param->tex_n->height - 1;
		raycast->texpos = raycast->texpos + raycast->step;
		raycast->adr = param->imgadr + (raycast->drawstart *
		param->imglenght + raycast->x * (param->imgbpp / 8));
		*(unsigned int *)raycast->adr = param->tex_n->tab[param->tex_n->width *
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

void	ft_raycasting_north(t_param *param, t_raycast *raycast)
{
	raycast->texx = raycast->wallx * param->tex_n->width;
	if (raycast->side == 0 && raycast->raydirx > 0)
		raycast->texx = param->tex_n->width - raycast->texx - 1;
	if (raycast->side == 1 && raycast->raydiry < 0)
		raycast->texx = param->tex_n->width - raycast->texx - 1;
	raycast->step = 1.0 * param->tex_n->height / raycast->lineheight;
	raycast->texpos = (raycast->drawstart - param->winy / 2 +
	raycast->lineheight / 2) * raycast->step;
	raycast->xfloorcell = 0;
	while (raycast->xfloorcell < raycast->drawstart)
	{
		raycast->adr = param->imgadr + (raycast->xfloorcell *
		param->imglenght + raycast->x * (param->imgbpp / 8));
		*(unsigned int *)raycast->adr = param->cellcolor;
		raycast->xfloorcell++;
	}
	ft_raycasting_north2(param, raycast);
}
