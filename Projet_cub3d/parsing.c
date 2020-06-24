/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 13:57:32 by ade-garr          #+#    #+#             */
/*   Updated: 2020/06/24 20:06:06 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_param_orient(t_param *param, char c)
{
	if (c == 'N')
	{
		param->dirX = 0;
		param->dirY = -1;
		param->planeX = 0.66;
		param->planeY = 0;
	}
	if (c == 'S')
	{
		param->dirX = 0;
		param->dirY = 1;
		param->planeX = -0.66;
		param->planeY = 0;
	}
	if (c == 'W')
	{
		param->dirX = -1;
		param->dirY = 0;
		param->planeX = 0;
		param->planeY = -0.66;
	}
	if (c == 'E')
	{
		param->dirX = 1;
		param->dirY = 0;
		param->planeX = 0;
		param->planeY = 0.66;
	}
}

void	ft_check_NSWE(t_param *param)
{
	int	compteur;
	int	i;
	int	j;

	i = 0;
	compteur = 0;
	while (i < param->mapHeight)
	{
		j = 0;
		while (param->worldMap[i][j] != '\0')
		{
			if (param->worldMap[i][j] == 'N' || param->worldMap[i][j] == 'S'
			|| param->worldMap[i][j] == 'E' || param->worldMap[i][j] == 'W')
			{
				compteur++;
				param->posX = j + 0.5;
				param->posY = i + 0.5;
				ft_param_orient(param, param->worldMap[i][j]);
			}
			j++;
		}
		i++;
	}
	if (compteur != 1)
		ft_exit(16);
}

int		ft_checking(char **check_map, int x, int y, int max)
{
	int	ret1;
	int	ret2;
	int	ret3;
	int	ret4;

	ret1 = 1;
	ret2 = 1;
	ret3 = 1;
	ret4 = 1;
	if (y == max - 1 || y == 0 || x == 0 || (size_t)x == ft_strlen(check_map[y]) - 1 || check_map[y][x - 1] == ' ' 
	|| check_map[y][x + 1] == ' ' || (size_t)x >= ft_strlen(check_map[y - 1]) || (size_t)x >= ft_strlen(check_map[y + 1])
	|| check_map[y - 1][x] == ' ' || check_map[y + 1][x] == ' ')
		return (-1);
	check_map[y][x] = 'V';
	if (check_map[y - 1][x] == '0' || check_map[y - 1][x] == '2')
		ret1 = ft_checking(check_map, x, y - 1, max);
	if (check_map[y + 1][x] == '0' || check_map[y + 1][x] == '2')
		ret2 = ft_checking(check_map, x, y + 1, max);
	if (check_map[y][x - 1] == '0' || check_map[y][x - 1] == '2')
		ret3 = ft_checking(check_map, x - 1, y, max);
	if (check_map[y][x + 1] == '0' || check_map[y][x + 1] == '2')
		ret4 = ft_checking(check_map, x + 1, y, max);
	if (ret1 == 1 && ret2 == 1 && ret3 == 1 && ret4 == 1)
		return(1);
	return(-1);
}

void	ft_check_map(t_param *param)
{
	char	**check_map;
	int		i;
	int		x;
	int		y;
	int		ret;

	i = 0;
	check_map = malloc(sizeof(char *) * (param->mapHeight + 1));
	if (check_map == NULL)
		ft_exit(4);
	while (i < param->mapHeight)
	{
		check_map[i] = ft_strdup(param->worldMap[i]);
		if (check_map[i] == NULL)
			ft_exit(4);
		i++;
	}
	check_map[i] = NULL;
	x = param->posX;
	y = param->posY;
	ret = ft_checking(check_map, x, y, param->mapHeight);
	if (ret == -1)
		ft_exit(16);
	ft_free_map(check_map, param);
}

void	ft_parsing(t_param *param, char *str)
{
    int 	fd;
	char	*line;

	fd = open(str, O_RDONLY);
    if (fd == -1)
        ft_exit3(param);
	ft_parsing_get_info(param, fd); 
	line = ft_parsing_empty_line(fd); // A REPRENDRE ICI
	ft_parsing_map(param, fd, line);
	ft_check_NSWE(param);
	ft_check_map(param);
	if (close(fd) == -1)
		ft_exit(4);
}
