/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 13:59:13 by ade-garr          #+#    #+#             */
/*   Updated: 2020/06/22 14:27:09 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    ft_free_map(char **map, t_param *param)
{
    int y;

    y = 0;
    while (y < param->mapHeight)
    {
        free(map[y]);
        y++;
    }
    free(map);
}

void    ft_free_param2(t_param *param)
{
    if (param->tex_W != NULL)
        free(param->tex_W->tab);
    free(param->tex_W);
    if (param->tex_sprite != NULL)
        free(param->tex_sprite->tab);
    free(param->tex_sprite);    
    free(param->tab_sprite);
    free(param->tab_dist_wall);
    free(param->sprite_order);
    free(param->sprite_distance);
    if (param->worldMap != NULL)
        ft_free_map(param->worldMap, param);
}

void    ft_free_param(t_param *param)
{
    free(param->fn_tex_N);
    free(param->fn_tex_S);
    free(param->fn_tex_W);
    free(param->fn_tex_E);
    free(param->fn_tex_sprite);
    if (param->tex_N != NULL)
        free(param->tex_N->tab);
    free(param->tex_N);
    if (param->tex_S != NULL)
        free(param->tex_S->tab);
    free(param->tex_S);
    if (param->tex_E != NULL)
        free(param->tex_E->tab);
    free(param->tex_E);
    ft_free_param2(param);
}

void    ft_set_local_endian(t_param *param)
{
    int endian;

    endian = 0x11223344;
    if (((unsigned char *)&endian)[0] == 0x11)
        param->local_endian = 1;
    else
        param->local_endian = 0;   
}

void    ft_init(t_param *param)
{
    int i;

    i = 0;
    while (i <= 6)
    {
        param->tab[i] = 0;
        i++;
    }
    param->fn_tex_N = NULL;
    param->fn_tex_S = NULL;
    param->fn_tex_W = NULL;
    param->fn_tex_E = NULL;
    param->fn_tex_sprite = NULL;
    param->tex_N = NULL;
    param->tex_S = NULL;
    param->tex_E = NULL;
    param->tex_W = NULL;
    param->tex_sprite = NULL;
    param->tab_sprite = NULL;
    param->tab_dist_wall = NULL;
    param->sprite_order = NULL;
    param->sprite_distance = NULL;
    param->worldMap = NULL;
}