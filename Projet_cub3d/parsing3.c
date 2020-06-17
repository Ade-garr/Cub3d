/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 11:02:44 by ade-garr          #+#    #+#             */
/*   Updated: 2020/06/17 11:03:27 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_analyse_resolution_info(t_param *param, char **spltline, int index)
{
	int	spltline_long;
	int	ret;
	int	screenX_max;
	int	screenY_max;

	spltline_long = ft_find_long_spltline(spltline);
	if (spltline_long != 3)
		ft_exit(index + 7);
	ret = ft_check_nb(spltline[1], spltline[2]);
	if (ret == -1)
		ft_exit(index + 7);
	param->winX = ft_atoi(spltline[1]);
	param->winY = ft_atoi(spltline[2]);
	//mlx_get_screen_size(param->mlx, &screenX_max, &screenY_max); // A MODIFIER AVEC MLX LINUX
	if (param->winX <= 0 || param->winY <= 0)
		ft_exit(15);
	screenX_max = 5000;// A ENLEVER
	screenY_max = 5000;// A ENLEVER	
	if (param->winX > screenX_max)
		param->winX = screenX_max;
	if (param->winY > screenY_max)
		param->winY = screenY_max;
}

void	ft_param_texture_path(t_param *param, char *str, int index)
{
	if (index == 1)
	{
		if ((param->fn_tex_N = ft_strdup(str)) == NULL)
			ft_exit(4);
	}
	if (index == 2)
	{
		if ((param->fn_tex_S = ft_strdup(str)) == NULL)
			ft_exit(4);
	}
	if (index == 3)
	{
		if ((param->fn_tex_W = ft_strdup(str)) == NULL)
			ft_exit(4);
	}
	if (index == 4)
	{
		if ((param->fn_tex_E = ft_strdup(str)) == NULL)
			ft_exit(4);
	}
	if (index == 5)
	{
		if ((param->fn_tex_sprite = ft_strdup(str)) == NULL)
			ft_exit(4);
	}
}

void	ft_analyse_texture_info(t_param *param, char **spltline, int index)
{
	int	spltline_long;
	void	*ret;
	int	i1;
	int	i2;

	spltline_long = ft_find_long_spltline(spltline);
	if (spltline_long != 2)
		ft_exit(index + 7);
	ret = mlx_xpm_file_to_image(param->mlx, spltline[1], &i1, &i2);
	if (ret == NULL)
		ft_exit(index + 7);
	ft_param_texture_path(param, spltline[1], index);
	mlx_destroy_image(param->mlx, ret);
}

int	ft_check_valid_b(char *str, int index, t_param *param, int i)
{
	int	B;

	B = -1;
	while (str[i] >= 48 && str[i] <= 57)
	{
		if (B == -1)
			B = str[i] - 48;
		else
			B = B * 10 + str[i] - 48;
		i++;
	}
	while (str[i] == ' ')
		i++;
	if (str[i] != '\0')
		ft_exit(index + 7);
	if ((B < 0 || B > 255))
		ft_exit(index + 7);
	if (index == 6)
		param->floorB = B;
	if (index == 7)
		param->cellB = B;
	return (i);
}

int	ft_check_valid_g(char *str, int index, t_param *param, int i)
{
	int	G;

	G = -1;
	while (str[i] >= 48 && str[i] <= 57)
	{
		if (G == -1)
			G = str[i] - 48;
		else
			G = G * 10 + str[i] - 48;
		i++;
	}
	if (str[i] != ',')
		ft_exit(index + 7);
	i++;
	if ((G < 0 || G > 255))
		ft_exit(index + 7);
	if (index == 6)
		param->floorG = G;
	if (index == 7)
		param->cellG = G;
	return (i);
}