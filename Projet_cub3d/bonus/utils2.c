/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 20:58:18 by ade-garr          #+#    #+#             */
/*   Updated: 2020/07/21 17:29:34 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_map(char **map, t_param *param)
{
	int y;

	y = 0;
	while (y < param->mapheight)
	{
		free(map[y]);
		y++;
	}
	free(map);
}

void	ft_free_param2(t_param *param)
{
	if (param->tex_w != NULL)
		free(param->tex_w->tab);
	free(param->tex_w);
	if (param->tex_sprite != NULL)
		free(param->tex_sprite->tab);
	free(param->tex_sprite);
	free(param->tab_sprite);
	free(param->tab_dist_wall);
	free(param->sprite_order);
	free(param->sprite_distance);
	if (param->worldmap != NULL)
		ft_free_map(param->worldmap, param);
	if (param->img != NULL)
		mlx_destroy_image(param->mlx, param->img);
	if (param->win != NULL)
		mlx_destroy_window(param->mlx, param->win);
	if (param->mlx != NULL)
		free(param->mlx);
	free(param);
}

void	ft_free_param(t_param *param)
{
	free(param->fn_tex_n);
	free(param->fn_tex_s);
	free(param->fn_tex_w);
	free(param->fn_tex_e);
	free(param->fn_tex_sprite);
	if (param->tex_n != NULL)
		free(param->tex_n->tab);
	free(param->tex_n);
	if (param->tex_s != NULL)
		free(param->tex_s->tab);
	free(param->tex_s);
	if (param->tex_e != NULL)
		free(param->tex_e->tab);
	free(param->tex_e);
	ft_free_param2(param);
}

void	ft_set_local_endian(t_param *param)
{
	int endian;

	endian = 0x11223344;
	if (((unsigned char *)&endian)[0] == 0x11)
		param->local_endian = 1;
	else
		param->local_endian = 0;
}

void	ft_init(t_param *param)
{
	int i;

	i = -1;
	while (++i <= 9)
		param->tab[i] = 0;
	param->fn_tex_n = NULL;
	param->fn_tex_s = NULL;
	param->fn_tex_w = NULL;
	param->fn_tex_e = NULL;
	param->fn_tex_sprite = NULL;
	param->tex_n = NULL;
	param->tex_s = NULL;
	param->tex_e = NULL;
	param->tex_w = NULL;
	ft_init2(param);
}
