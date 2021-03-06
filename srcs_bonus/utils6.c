/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 19:43:41 by ade-garr          #+#    #+#             */
/*   Updated: 2020/07/21 17:29:45 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_check_filename(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
		i++;
	if (ft_strlen(str) >= 4 && str[i - 1] == 'b' && str[i - 2] == 'u'
	&& str[i - 3] == 'c' && str[i - 4] == '.')
		return (1);
	return (0);
}

void	ft_param_orient2(t_param *param, char c)
{
	if (c == 'W')
	{
		param->dirx = -1;
		param->diry = 0;
		param->planex = 0;
		param->planey = -0.66;
	}
	if (c == 'E')
	{
		param->dirx = 1;
		param->diry = 0;
		param->planex = 0;
		param->planey = 0.66;
	}
}

int		ft_checking2(char **check_map, int x, int y, int max)
{
	int	ret1;
	int	ret2;
	int	ret3;
	int	ret4;

	ret1 = 1;
	ret2 = 1;
	ret3 = 1;
	ret4 = 1;
	if (check_map[y - 1][x] == '0' || check_map[y - 1][x] == '2')
		ret1 = ft_checking(check_map, x, y - 1, max);
	if (check_map[y + 1][x] == '0' || check_map[y + 1][x] == '2')
		ret2 = ft_checking(check_map, x, y + 1, max);
	if (check_map[y][x - 1] == '0' || check_map[y][x - 1] == '2')
		ret3 = ft_checking(check_map, x - 1, y, max);
	if (check_map[y][x + 1] == '0' || check_map[y][x + 1] == '2')
		ret4 = ft_checking(check_map, x + 1, y, max);
	if (ret1 == 1 && ret2 == 1 && ret3 == 1 && ret4 == 1)
		return (1);
	return (-1);
}

void	ft_color_red(t_param *param, int x, int y)
{
	char	*adr;

	adr = param->imgadr + (y * param->imglenght + x * (param->imgbpp / 8));
	*(unsigned int *)adr = 0x000000;
}

void	ft_init2(t_param *param)
{
	param->tex_sprite = NULL;
	param->tab_sprite = NULL;
	param->tab_dist_wall = NULL;
	param->sprite_order = NULL;
	param->sprite_distance = NULL;
	param->worldmap = NULL;
	param->mlx = NULL;
	param->win = NULL;
	param->img = NULL;
	param->crouch = 0;
	param->updown = 0;
	param->stamina = 200;
}
