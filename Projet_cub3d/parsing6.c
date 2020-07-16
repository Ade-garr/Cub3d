/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing6.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 16:17:43 by ade-garr          #+#    #+#             */
/*   Updated: 2020/07/16 17:57:17 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_get_mapwidth(t_param *param)
{
	int	i;

	i = 0;
	param->mapwidth = 0;
	while (i < param->mapheight)
	{
		if ((size_t)param->mapwidth < ft_strlen(param->worldmap[i]))
			param->mapwidth = ft_strlen(param->worldmap[i]);
		i++;
	}
}

void	ft_fill_tmp_worldmap(t_param *param, char **tmp_worldmap)
{
	int	i;
	int	j;

	i = -1;
	while (++i < param->mapheight)
	{
		tmp_worldmap[i] = malloc(sizeof(char) * param->mapwidth + 1);
		if (tmp_worldmap[i] == NULL)
			ft_exit13(param, tmp_worldmap);
		j = 0;
		while ((size_t)j < ft_strlen(param->worldmap[i]))
		{
			if (param->worldmap[i][j] == ' ')
				tmp_worldmap[i][j] = '1';
			else
				tmp_worldmap[i][j] = param->worldmap[i][j];
			j++;
		}
		while (j < param->mapwidth)
		{
			tmp_worldmap[i][j] = '1';
			j++;
		}
		tmp_worldmap[i][j] = '\0';
	}
}

void	ft_check_map_nobonus(t_param *param)
{
	int	i;
	int	j;

	i = 0;
	while (i < param->mapheight)
	{
		if (i == 0 || i == param->mapheight - 1)
		{
			j = 0;
			while (j < param->mapwidth)
			{
				if (param->worldmap[i][j] != '1')
					ft_exit12(param);
				j++;
			}
		}
		else
		{
			if (param->worldmap[i][0] != '1'
			|| param->worldmap[i][param->mapwidth - 1] != '1')
				ft_exit12(param);
		}
		i++;
	}
}
