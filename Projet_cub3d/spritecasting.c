/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spritecasting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 14:15:56 by ade-garr          #+#    #+#             */
/*   Updated: 2020/07/13 14:18:26 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_spritecasting3(t_param *param, t_spritecast *spritecast)
{
	while (spritecast->x < spritecast->draw_endX)
	{
		spritecast->texX = ((spritecast->x - (-spritecast->sprite_width / 2 + spritecast->sprite_screenX)) * param->tex_sprite->width / spritecast->sprite_width);
		if (spritecast->transformY > 0 && spritecast->x >= 0 && spritecast->x < param->winX && spritecast->transformY < param->tab_dist_wall[spritecast->x])
		{
			spritecast->y = spritecast->draw_startY;
			while (spritecast->y < spritecast->draw_endY)
			{
				spritecast->d = spritecast->y - param->winY / 2 + spritecast->sprite_height / 2;
				spritecast->texY = ((spritecast->d * param->tex_sprite->height) / spritecast->sprite_height);
				if (param->tex_sprite->tab[spritecast->texY * param->tex_sprite->width + spritecast->texX] != 0xFFFFFF)
				{
					spritecast->adr = param->imgadr + (spritecast->y * param->imglenght + spritecast->x * (param->imgbpp / 8));
					*(unsigned int *)spritecast->adr = param->tex_sprite->tab[param->tex_sprite->width * spritecast->texY + spritecast->texX];
				}
				spritecast->y++;
			}
		}
		spritecast->x++;
	}
}

void	ft_spritecasting2(t_param *param, t_spritecast *spritecast)
{
	spritecast->spriteX = param->tab_sprite[param->sprite_order[spritecast->i]].x - param->posX;
	spritecast->spriteY = param->tab_sprite[param->sprite_order[spritecast->i]].y - param->posY;
	spritecast->invDet = 1 / (param->planeX * param->dirY - param->dirX * param->planeY);
	spritecast->transformX = spritecast->invDet * (param->dirY * spritecast->spriteX - param->dirX * spritecast->spriteY);
	spritecast->transformY = spritecast->invDet * (-param->planeY * spritecast->spriteX + param->planeX * spritecast->spriteY);
	spritecast->sprite_screenX = ((param->winX / 2) * (1 + spritecast->transformX / spritecast->transformY));
	spritecast->sprite_height = (fabs(param->winY / spritecast->transformY));
	spritecast->draw_startY = -spritecast->sprite_height / 2 + param->winY / 2;
	if (spritecast->draw_startY < 0)
		spritecast->draw_startY = 0;
	spritecast->draw_endY = spritecast->sprite_height / 2 + param->winY / 2;
	if (spritecast->draw_endY >= param->winY)
		spritecast->draw_endY = param->winY;
	spritecast->sprite_width = (fabs(param->winY / spritecast->transformY));
	spritecast->draw_startX = -spritecast->sprite_width / 2 + spritecast->sprite_screenX;
	if (spritecast->draw_startX < 0)
		spritecast->draw_startX = 0;
	spritecast->draw_endX = spritecast->sprite_width / 2 + spritecast->sprite_screenX;
	if (spritecast->draw_endX >= param->winX)
		spritecast->draw_endX = param->winX;
	spritecast->x = spritecast->draw_startX;
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
		param->sprite_distance[spritecast->i] = (param->posX - param->tab_sprite[spritecast->i].x) * (param->posX - param->tab_sprite[spritecast->i].x) + (param->posY - param->tab_sprite[spritecast->i].y) * (param->posY - param->tab_sprite[spritecast->i].y);
		spritecast->i++;
	}
	ft_sort_sprites(param);
	spritecast->i = 0;
	while (spritecast->i < param->nb_sprite)
	{
		ft_spritecasting2(param, spritecast);
		ft_spritecasting3(param, spritecast);
		spritecast->i++;
	}
}