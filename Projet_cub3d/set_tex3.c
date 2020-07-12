/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_tex3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 11:22:17 by ade-garr          #+#    #+#             */
/*   Updated: 2020/06/24 20:06:00 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_set_tex_n(t_param *param)
{
	char	*adr;
	void	*ret;
	int		bpp;
	int		length;
	int		endian;

	ret = mlx_xpm_file_to_image(param->mlx, param->fn_tex_N, &param->tex_N->width, &param->tex_N->height);
	if (ret == NULL)
		ft_exit2(param);
	adr = mlx_get_data_addr(ret, &bpp, &length, &endian);
	param->tex_N->tab = malloc(sizeof(unsigned int) * (param->tex_N->height * param->tex_N->width));
	if (param->tex_N->tab == NULL)
		ft_exit2(param);
	if (param->local_endian != endian)
		ft_set_tex_n_tab_endian(param, adr, bpp, length);
	else
		ft_set_tex_n_tab_no_endian(param, adr, bpp, length);
	mlx_destroy_image(param->mlx, ret);
}

void	ft_set_tex_s_tab_no_endian(t_param *param, char *adr, int bpp, int length)
{
	int	x;
	int	y;

	y = -1;
	while (++y < param->tex_S->height)
	{
		x = -1;
		while (++x < param->tex_S->width)
			param->tex_S->tab[y * param->tex_S->width + x] = *(unsigned int *)(adr + y * length + x * bpp / 8);
	}
}

void	ft_set_tex_s_tab_endian(t_param *param, char *adr, int bpp, int length)
{
	int	x;
	int	y;
	unsigned int	color;

	y = -1;
	while (++y < param->tex_S->height)
	{
		x = -1;
		while (++x < param->tex_S->width)
		{
			color = *(unsigned int *)(adr + y * length + x * bpp / 8);
			color = ((color>>24)&0xff) | ((color<<8)&0xff0000) | ((color>>8)&0xff00) | ((color<<24)&0xff000000);
			param->tex_S->tab[y * param->tex_S->width + x] = color;
		}
	}
}

void	ft_set_tex_s(t_param *param)
{
	char	*adr;
	void	*ret;
	int		bpp;
	int		length;
	int		endian;

	ret = mlx_xpm_file_to_image(param->mlx, param->fn_tex_S, &param->tex_S->width, &param->tex_S->height);
	if (ret == NULL)
		ft_exit2(param);
	adr = mlx_get_data_addr(ret, &bpp, &length, &endian);
	param->tex_S->tab = malloc(sizeof(unsigned int) * (param->tex_S->height * param->tex_S->width));
	if (param->tex_S->tab == NULL)
		ft_exit2(param);
	if (param->local_endian != endian)
		ft_set_tex_s_tab_endian(param, adr, bpp, length);
	else
		ft_set_tex_s_tab_no_endian(param, adr, bpp, length);
	mlx_destroy_image(param->mlx, ret);
}

void	ft_set_tex_w_tab_no_endian(t_param *param, char *adr, int bpp, int length)
{
	int	x;
	int	y;

	y = -1;
	while (++y < param->tex_W->height)
	{
		x = -1;
		while (++x < param->tex_W->width)
			param->tex_W->tab[y * param->tex_W->width + x] = *(unsigned int *)(adr + y * length + x * bpp / 8);
	}
}