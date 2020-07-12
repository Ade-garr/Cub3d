/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 11:02:44 by ade-garr          #+#    #+#             */
/*   Updated: 2020/06/24 20:06:05 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_analyse_resolution_info(t_param *param, char **spltline, int index, char *line)
{
	int	spltline_long;
	int	ret;
	int	screenX_max;
	int	screenY_max;

	spltline_long = ft_find_long_spltline(spltline);
	if (spltline_long != 3)
		ft_exit7(param, spltline, line, index);
	ret = ft_check_nb(spltline[1], spltline[2]);
	if (ret == -1)
		ft_exit7(param, spltline, line, index);
	param->winX = ft_atoi(spltline[1]);
	param->winY = ft_atoi(spltline[2]);
	//mlx_get_screen_size(param->mlx, &screenX_max, &screenY_max); // A MODIFIER AVEC MLX LINUX
	if (param->winX <= 0 || param->winY <= 0)
		ft_exit7(param, spltline, line, 8);
	screenX_max = 1920;// A ENLEVER
	screenY_max = 1080;// A ENLEVER	
	if (param->winX > screenX_max)
		param->winX = screenX_max;
	if (param->winY > screenY_max)
		param->winY = screenY_max;
}

void	ft_param_texture_path(t_param *param, char **spltline, int index, char *line)
{
	if (index == 1)
	{
		if ((param->fn_tex_N = ft_strdup(spltline[1])) == NULL)
			ft_exit8(param, spltline, line);
	}
	if (index == 2)
	{
		if ((param->fn_tex_S = ft_strdup(spltline[1])) == NULL)
			ft_exit8(param, spltline, line);
	}
	if (index == 3)
	{
		if ((param->fn_tex_W = ft_strdup(spltline[1])) == NULL)
			ft_exit8(param, spltline, line);
	}
	if (index == 4)
	{
		if ((param->fn_tex_E = ft_strdup(spltline[1])) == NULL)
			ft_exit8(param, spltline, line);
	}
	if (index == 5)
	{
		if ((param->fn_tex_sprite = ft_strdup(spltline[1])) == NULL)
			ft_exit8(param, spltline, line);
	}
}

void	ft_analyse_texture_info(t_param *param, char **spltline, int index, char *line)
{
	int	spltline_long;
	void	*ret;
	int	i1;
	int	i2;

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
	int	B;
	int	i;

	i = 0;
	B = -1;
	while (spltline[1][i] != ',')
		i++;
	i++;
	while (spltline[1][i] != ',')
		i++;
	i++;
	while (spltline[1][i] >= 48 && spltline[1][i] <= 57)
	{
		if (B == -1)
			B = spltline[1][i] - 48;
		else
			B = B * 10 + spltline[1][i] - 48;
		i++;
	}
	while (spltline[1][i] == ' ')
		i++;
	if (spltline[1][i] != '\0')
		ft_exit7(param, spltline, line, index);
	if ((B < 0 || B > 255))
		ft_exit7(param, spltline, line, index);
	if (index == 6)
		param->floorB = B;
	if (index == 7)
		param->cellB = B;
}

void	ft_check_valid_g(char **spltline, int index, t_param *param, char *line)
{
	int	G;
	int i;

	i = 0;
	G = -1;
	while (spltline[1][i] != ',')
		i++;
	i++;
	while (spltline[1][i] >= 48 && spltline[1][i] <= 57)
	{
		if (G == -1)
			G = spltline[1][i] - 48;
		else
			G = G * 10 + spltline[1][i] - 48;
		i++;
	}
	if (spltline[1][i] != ',')
		ft_exit7(param, spltline, line, index);
	if ((G < 0 || G > 255))
		ft_exit7(param, spltline, line, index);
	if (index == 6)
		param->floorG = G;
	if (index == 7)
		param->cellG = G;
}