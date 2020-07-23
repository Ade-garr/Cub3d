/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 13:57:32 by ade-garr          #+#    #+#             */
/*   Updated: 2020/07/13 19:10:18 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_param_orient(t_param *param, char c)
{
	if (c == 'N')
	{
		param->dirx = 0;
		param->diry = -1;
		param->planex = 0.66;
		param->planey = 0;
	}
	if (c == 'S')
	{
		param->dirx = 0;
		param->diry = 1;
		param->planex = -0.66;
		param->planey = 0;
	}
	ft_param_orient2(param, c);
}

void	ft_check_nswe(t_param *param)
{
	int	compteur;
	int	i;
	int	j;

	i = 0;
	compteur = 0;
	while (i < param->mapheight)
	{
		j = 0;
		while (param->worldmap[i][j] != '\0')
		{
			if (param->worldmap[i][j] == 'N' || param->worldmap[i][j] == 'S'
			|| param->worldmap[i][j] == 'E' || param->worldmap[i][j] == 'W')
			{
				compteur++;
				param->posx = j + 0.5;
				param->posy = i + 0.5;
				ft_param_orient(param, param->worldmap[i][j]);
			}
			j++;
		}
		i++;
	}
	if (compteur != 1)
		ft_exit12(param);
}

int		ft_checking(char **check_map, int x, int y, int max)
{
	if (y == max - 1 || y == 0 || x == 0
	|| (size_t)x == ft_strlen(check_map[y]) - 1 || check_map[y][x - 1] == ' '
	|| check_map[y][x + 1] == ' ' || (size_t)x >= ft_strlen(check_map[y - 1])
	|| (size_t)x >= ft_strlen(check_map[y + 1]) || check_map[y - 1][x] == ' '
	|| check_map[y + 1][x] == ' ')
		return (-1);
	check_map[y][x] = 'V';
	return (ft_checking2(check_map, x, y, max));
}

void	ft_check_map(t_param *param)
{
	char	**check_map;
	int		i;
	int		ret;

	i = 0;
	check_map = malloc(sizeof(char *) * (param->mapheight));
	if (check_map == NULL)
		ft_exit10(param);
	while (i < param->mapheight)
	{
		check_map[i] = ft_strdup(param->worldmap[i]);
		if (check_map[i] == NULL)
			ft_exit13(param, check_map);
		i++;
	}
	ret = ft_checking(check_map, param->posx, param->posy, param->mapheight);
	if (ret == -1)
		ft_exit14(param, check_map);
	ft_free_map(check_map, param);
}

void	ft_parsing(t_param *param, char *str)
{
	int		fd;
	char	*line;

	fd = open(str, O_RDONLY);
	if (fd == -1)
		ft_exit3(param);
	ft_parsing_get_info(param, fd);
	line = ft_parsing_empty_line(param, fd);
	ft_parsing_map(param, fd, line);
	ft_check_nswe(param);
	ft_check_map(param);
	close(fd);
}
