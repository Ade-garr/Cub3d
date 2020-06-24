/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 11:03:39 by ade-garr          #+#    #+#             */
/*   Updated: 2020/06/24 20:06:48 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_check_valid_r(char **spltline, int index, t_param *param, char *line)
{
	int	R;
	int	i;

	i = 0;
	R = -1;
	while (spltline[1][i] >= 48 && spltline[1][i] <= 57)
	{
		if (R == -1)
			R = spltline[1][i] - 48;
		else
			R = R * 10 + spltline[1][i] - 48;
		i++;
	}
	if (spltline[1][i] != ',')
		ft_exit7(param, spltline, line, index);
	if ((R < 0 || R > 255))
		ft_exit7(param, spltline, line, index);
	if (index == 6)
		param->floorR = R;
	if (index == 7)
		param->cellR = R;
}

void	ft_analyse_color_info(t_param *param, char **spltline, int index, char *line)
{
	int	spltline_long;

	spltline_long = ft_find_long_spltline(spltline);
	if (spltline_long != 2)
		ft_exit7(param, spltline, line, index);
	ft_check_valid_r(spltline, index, param, line);
	ft_check_valid_g(spltline, index, param, line);
	ft_check_valid_b(spltline, index, param, line);
}

void	ft_analyse_line_info(t_param *param, char **spltline, int index, char *line)
{
	if (index == 0)
		ft_analyse_resolution_info(param, spltline, index, line);
	if (index > 0 && index <= 5)
		ft_analyse_texture_info(param, spltline, index), line;
	if (index > 5)
	{
		ft_analyse_color_info(param, spltline, index, line);
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
		ft_exit6(param, line);
	index = ft_analyse_line_index(spltline, tab);
	if (index >= 0 && index <= 7)
	{
		ft_analyse_line_info(param, spltline, index, line);
		spltline = ft_free(&spltline);
		tab[index] = 1;
	}
	else
		ft_exit9(param, spltline, line);
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