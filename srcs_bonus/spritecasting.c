/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spritecasting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 14:15:56 by ade-garr          #+#    #+#             */
/*   Updated: 2020/07/21 17:27:32 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_spritecasting5(t_param *param, t_spritecast *spritecast)
{
	spritecast->y = spritecast->draw_starty;
	while (spritecast->y < spritecast->draw_endy)
	{
		spritecast->d = spritecast->y - spritecast->spritecrouch -
		param->updown - param->winy / 2 + spritecast->sprite_height / 2;
		spritecast->texy = ((spritecast->d *
		param->tex_sprite->height) / spritecast->sprite_height);
		if (param->tex_sprite->tab[spritecast->texy *
		param->tex_sprite->width + spritecast->texx] != 0xFFFFFF)
		{
			spritecast->adr = param->imgadr + (spritecast->y *
			param->imglenght + spritecast->x * (param->imgbpp / 8));
			*(unsigned int *)spritecast->adr =
			param->tex_sprite->tab[param->tex_sprite->width *
			spritecast->texy + spritecast->texx];
		}
		spritecast->y++;
	}
}

void	ft_spritecasting4(t_param *param, t_spritecast *spritecast)
{
	while (spritecast->x < spritecast->draw_endx)
	{
		spritecast->texx = ((spritecast->x - (-spritecast->sprite_width / 2 +
		spritecast->sprite_screenx)) * param->tex_sprite->width /
		spritecast->sprite_width);
		if (spritecast->transformy > 0 && spritecast->x >= 0 &&
		spritecast->x < param->winx && spritecast->transformy <
		param->tab_dist_wall[spritecast->x])
			ft_spritecasting5(param, spritecast);
		spritecast->x++;
	}
}

void	ft_spritecasting3(t_param *param, t_spritecast *spritecast)
{
	if (spritecast->draw_starty < 0)
		spritecast->draw_starty = 0;
	spritecast->draw_endy = spritecast->sprite_height / 2 + param->winy / 2
	+ spritecast->spritecrouch + param->updown;
	if (spritecast->draw_endy >= param->winy)
		spritecast->draw_endy = param->winy;
	spritecast->sprite_width = (fabs(param->winy / spritecast->transformy));
	spritecast->draw_startx = -spritecast->sprite_width / 2 +
	spritecast->sprite_screenx;
	if (spritecast->draw_startx < 0)
		spritecast->draw_startx = 0;
	spritecast->draw_endx = spritecast->sprite_width / 2 +
	spritecast->sprite_screenx;
	if (spritecast->draw_endx >= param->winx)
		spritecast->draw_endx = param->winx;
	spritecast->x = spritecast->draw_startx;
}

void	ft_spritecasting2(t_param *param, t_spritecast *spritecast)
{
	spritecast->spritex =
	param->tab_sprite[param->sprite_order[spritecast->i]].x - param->posx;
	spritecast->spritey =
	param->tab_sprite[param->sprite_order[spritecast->i]].y - param->posy;
	spritecast->invdet = 1 / (param->planex * param->diry - param->dirx *
	param->planey);
	spritecast->transformx = spritecast->invdet * (param->diry *
	spritecast->spritex - param->dirx * spritecast->spritey);
	spritecast->transformy = spritecast->invdet * (-param->planey *
	spritecast->spritex + param->planex * spritecast->spritey);
	spritecast->sprite_screenx = ((param->winx / 2) * (1 +
	spritecast->transformx / spritecast->transformy));
	spritecast->sprite_height = (fabs(param->winy / spritecast->transformy));
	spritecast->spritecrouch = param->crouch / spritecast->transformy * 0.8;
	spritecast->draw_starty = -spritecast->sprite_height / 2 +
	param->winy / 2 + spritecast->spritecrouch + param->updown;
	ft_spritecasting3(param, spritecast);
}

void	ft_spritecasting(t_param *param)
{
	t_spritecast	*spritecast;
	t_spritecast	struct_spritecast;

	spritecast = &struct_spritecast;
	spritecast->i = 0;
	while (spritecast->i < param->nb_sprite)
	{
		param->sprite_order[spritecast->i] = spritecast->i;
		param->sprite_distance[spritecast->i] = (param->posx -
		param->tab_sprite[spritecast->i].x) * (param->posx -
		param->tab_sprite[spritecast->i].x) + (param->posy -
		param->tab_sprite[spritecast->i].y) * (param->posy -
		param->tab_sprite[spritecast->i].y);
		spritecast->i++;
	}
	ft_sort_sprites(param);
	spritecast->i = 0;
	while (spritecast->i < param->nb_sprite)
	{
		ft_spritecasting2(param, spritecast);
		ft_spritecasting4(param, spritecast);
		spritecast->i++;
	}
}
