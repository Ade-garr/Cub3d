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

void    ft_set_local_endian(t_param *param)
{
    int endian;

    endian = 0x11223344;
    if (((unsigned char *)&endian)[0] == 0x11)
        param->local_endian = 1;
    else
        param->local_endian = 0;   
}