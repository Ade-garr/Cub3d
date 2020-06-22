/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 11:03:39 by ade-garr          #+#    #+#             */
/*   Updated: 2020/06/22 12:57:52 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_check_valid_r(char *str, int index, t_param *param, int i)
{
	int	R;

	R = -1;
	while (str[i] >= 48 && str[i] <= 57)
	{
		if (R == -1)
			R = str[i] - 48;
		else
			R = R * 10 + str[i] - 48;
		i++;
	}
	if (str[i] != ',')
		ft_exit(index + 7);
	i++;
	if ((R < 0 || R > 255))
		ft_exit(index + 7);
	if (index == 6)
		param->floorR = R;
	if (index == 7)
		param->cellR = R;
	return (i);
}

void	ft_analyse_color_info(t_param *param, char **spltline, int index)
{
	int	spltline_long;
	int	i;

	i = 0;
	spltline_long = ft_find_long_spltline(spltline);
	if (spltline_long != 2)
		ft_exit(index + 7);
	i = ft_check_valid_r(spltline[1], index, param, i);
	i = ft_check_valid_g(spltline[1], index, param, i);
	i = ft_check_valid_b(spltline[1], index, param, i);
}

void	ft_analyse_line_info(t_param *param, char **spltline, int index)
{
	if (index == 0)
		ft_analyse_resolution_info(param, spltline, index);
	if (index > 0 && index <= 5)
		ft_analyse_texture_info(param, spltline, index);
	if (index > 5)
	{
		ft_analyse_color_info(param, spltline, index);
		param->floorcolor = param->floorB + param->floorG * 256 + param->floorR * 65536;
		param->cellcolor = param->cellB + param->cellG * 256 + param->cellR * 65536;
	}
}

void	ft_analyse_line(t_param *param, char *line, int	tab[8])
{
	char **spltline;
	int	index;

	spltline = ft_split(line, ' ');
	if (spltline == NULL)
		ft_exit(4);
	index = ft_analyse_line_index(spltline, tab);
	if (index >= 0 && index <= 7)
	{
		ft_analyse_line_info(param, spltline, index);
		spltline = ft_free(&spltline);
		tab[index] = 1;
	}
	else
		ft_exit(6);
}

void	ft_check_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != '2' && line[i] != 'N' 
		&& line[i] != 'S' && line[i] != 'E' && line[i] != 'W' && line[i] != ' ')
			ft_exit(16);
		i++;
	}
}