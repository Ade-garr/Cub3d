/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_sprite.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 10:46:39 by ade-garr          #+#    #+#             */
/*   Updated: 2020/06/17 16:28:13 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_sort_sprites(t_param *param)
{
	int		i;
	double	tmp_dist;
	int		tmp_order;

	i = 0;
	if (param->nb_sprite >= 2)
	{
		while (i < param->nb_sprite - 1)
		{
			if (param->sprite_distance[i] < param->sprite_distance[i + 1])
			{
				tmp_dist = param->sprite_distance[i];
				param->sprite_distance[i] = param->sprite_distance[i + 1];
				param->sprite_distance[i + 1] = tmp_dist;
				tmp_order = param->sprite_order[i];
				param->sprite_order[i] = param->sprite_order[i + 1];
				param->sprite_order[i + 1] = tmp_order;
				i = -1;
			}
			i++;
		}
	}
}

void    ft_find_nb_sprite(t_param *param)
{
	int		x;
	int		y;

    y = 0;
	param->nb_sprite = 0;
	while (y < param->mapHeight)
	{
		x = 0;
		while (param->worldMap[y][x] != '\0')
		{
			if (param->worldMap[y][x] == '2')
				param->nb_sprite++;
			x++;
		}
		y++;
	}
}

void    ft_param_sprites(t_param *param)
{
    int x;
	int y;
    int i;

    y = 0;
	i = 0;
	while (y < param->mapHeight)
	{
		x = 0;
		while (param->worldMap[y][x] != '\0')
		{
			if (param->worldMap[y][x] == '2')
			{
				param->tab_sprite[i].x = x + 0.5;
				param->tab_sprite[i].y = y + 0.5;
				i++;
			}
			x++;
		}
		y++;
	}
}

void	ft_set_sprite(t_param *param)
{
    ft_find_nb_sprite(param);	
	param->tab_sprite = malloc(sizeof(t_sprite) * param->nb_sprite);
	if (param->tab_sprite == NULL)
		ft_exit(4);
	ft_param_sprites(param);
    param->sprite_order = malloc(sizeof(int) * param->nb_sprite);
	if (param->sprite_order == NULL)
		ft_exit(4);
	param->sprite_distance = malloc(sizeof(double) * param->nb_sprite);
	if (param->sprite_order == NULL)
		ft_exit(4);
}