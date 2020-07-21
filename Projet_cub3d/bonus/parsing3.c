/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 11:02:44 by ade-garr          #+#    #+#             */
/*   Updated: 2020/07/21 17:24:59 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_analyse_resolution_info(t_param *param, char **spltline,
		int index, char *line)
{
	int	spltline_long;
	int	ret;
	int	screenx_max;
	int	screeny_max;

	spltline_long = ft_find_long_spltline(spltline);
	if (spltline_long != 3)
		ft_exit7(param, spltline, line, index);
	ret = ft_check_nb(spltline[1], spltline[2]);
	if (ret == -1)
		ft_exit7(param, spltline, line, index);
	param->winx = ft_atoi(spltline[1]);
	param->winy = ft_atoi(spltline[2]);
	mlx_get_screen_size(param->mlx, &screenx_max, &screeny_max);
	if (param->winx <= 0 || param->winy <= 0)
		ft_exit7(param, spltline, line, 8);
	if (param->winx > screenx_max)
		param->winx = screenx_max;
	if (param->winy > screeny_max)
		param->winy = screeny_max;
}

void	ft_param_texture_path(t_param *param, char **spltline,
		int index, char *line)
{
	if (index == 1)
	{
		if ((param->fn_tex_n = ft_strdup(spltline[1])) == NULL)
			ft_exit8(param, spltline, line);
	}
	if (index == 2)
	{
		if ((param->fn_tex_s = ft_strdup(spltline[1])) == NULL)
			ft_exit8(param, spltline, line);
	}
	if (index == 3)
	{
		if ((param->fn_tex_w = ft_strdup(spltline[1])) == NULL)
			ft_exit8(param, spltline, line);
	}
	if (index == 4)
	{
		if ((param->fn_tex_e = ft_strdup(spltline[1])) == NULL)
			ft_exit8(param, spltline, line);
	}
	if (index == 5)
	{
		if ((param->fn_tex_sprite = ft_strdup(spltline[1])) == NULL)
			ft_exit8(param, spltline, line);
	}
}

void	ft_analyse_texture_info(t_param *param, char **spltline,
		int index, char *line)
{
	int		spltline_long;
	void	*ret;
	int		i1;
	int		i2;

	spltline_long = ft_find_long_spltline(spltline);
	if (spltline_long != 2)
		ft_exit7(param, spltline, line, index);
	ret = mlx_xpm_file_to_image(param->mlx, spltline[1], &i1, &i2);
	if (ret == NULL)
		ft_exit7(param, spltline, line, index);
	ft_param_texture_path(param, spltline, index, line);
	mlx_destroy_image(param->mlx, ret);
}

void	ft_check_valid_b(char **spltline, int index, t_param *param, char *line)
{
	int	b;
	int	i;

	i = 0;
	b = -1;
	while (spltline[1][i] != ',')
		i++;
	i++;
	while (spltline[1][i] != ',')
		i++;
	i++;
	while (spltline[1][i] >= 48 && spltline[1][i] <= 57)
	{
		b = (b == -1) ? spltline[1][i] - 48 : b * 10 + spltline[1][i] - 48;
		i++;
	}
	while (spltline[1][i] == ' ')
		i++;
	if (spltline[1][i] != '\0' || (b < 0 || b > 255))
		ft_exit7(param, spltline, line, index);
	if (index == 6)
		param->floorb = b;
	if (index == 7)
		param->cellb = b;
}

void	ft_check_valid_g(char **spltline, int index, t_param *param, char *line)
{
	int	g;
	int i;

	i = 0;
	g = -1;
	while (spltline[1][i] != ',')
		i++;
	i++;
	while (spltline[1][i] >= 48 && spltline[1][i] <= 57)
	{
		if (g == -1)
			g = spltline[1][i] - 48;
		else
			g = g * 10 + spltline[1][i] - 48;
		i++;
	}
	if (spltline[1][i] != ',')
		ft_exit7(param, spltline, line, index);
	if ((g < 0 || g > 255))
		ft_exit7(param, spltline, line, index);
	if (index == 6)
		param->floorg = g;
	if (index == 7)
		param->cellg = g;
}
