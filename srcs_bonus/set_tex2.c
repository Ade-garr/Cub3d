/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_tex2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 11:21:11 by ade-garr          #+#    #+#             */
/*   Updated: 2020/07/13 20:30:36 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_set_tex_w_tab_endian(t_param *param, char *adr, int bpp, int length)
{
	int				x;
	int				y;
	unsigned int	color;

	y = -1;
	while (++y < param->tex_w->height)
	{
		x = -1;
		while (++x < param->tex_w->width)
		{
			color = *(unsigned int *)(adr + y * length + x * bpp / 8);
			color = ((color >> 24) & 0xff) | ((color << 8) & 0xff0000) |
			((color >> 8) & 0xff00) | ((color << 24) & 0xff000000);
			param->tex_w->tab[y * param->tex_w->width + x] = color;
		}
	}
}

void	ft_set_tex_w(t_param *param)
{
	char	*adr;
	void	*ret;
	int		bpp;
	int		length;
	int		endian;

	ret = mlx_xpm_file_to_image(param->mlx, param->fn_tex_w,
	&param->tex_w->width, &param->tex_w->height);
	if (ret == NULL)
		ft_exit2(param);
	adr = mlx_get_data_addr(ret, &bpp, &length, &endian);
	param->tex_w->tab = malloc(sizeof(unsigned int) *
	(param->tex_w->height * param->tex_w->width));
	if (param->tex_w->tab == NULL)
		ft_exit2(param);
	if (param->local_endian != endian)
		ft_set_tex_w_tab_endian(param, adr, bpp, length);
	else
		ft_set_tex_w_tab_no_endian(param, adr, bpp, length);
	mlx_destroy_image(param->mlx, ret);
}

void	ft_set_tex_e_tab_no_endian(t_param *param, char *adr,
		int bpp, int length)
{
	int	x;
	int	y;

	y = -1;
	while (++y < param->tex_e->height)
	{
		x = -1;
		while (++x < param->tex_e->width)
			param->tex_e->tab[y * param->tex_e->width + x] =
			*(unsigned int *)(adr + y * length + x * bpp / 8);
	}
}

void	ft_set_tex_e_tab_endian(t_param *param, char *adr, int bpp, int length)
{
	int				x;
	int				y;
	unsigned int	color;

	y = -1;
	while (++y < param->tex_e->height)
	{
		x = -1;
		while (++x < param->tex_e->width)
		{
			color = *(unsigned int *)(adr + y * length + x * bpp / 8);
			color = ((color >> 24) & 0xff) | ((color << 8) & 0xff0000) |
			((color >> 8) & 0xff00) | ((color << 24) & 0xff000000);
			param->tex_e->tab[y * param->tex_e->width + x] = color;
		}
	}
}

void	ft_set_tex_e(t_param *param)
{
	char	*adr;
	void	*ret;
	int		bpp;
	int		length;
	int		endian;

	ret = mlx_xpm_file_to_image(param->mlx, param->fn_tex_e,
	&param->tex_e->width, &param->tex_e->height);
	if (ret == NULL)
		ft_exit2(param);
	adr = mlx_get_data_addr(ret, &bpp, &length, &endian);
	param->tex_e->tab = malloc(sizeof(unsigned int) *
	(param->tex_e->height * param->tex_e->width));
	if (param->tex_e->tab == NULL)
		ft_exit2(param);
	if (param->local_endian != endian)
		ft_set_tex_e_tab_endian(param, adr, bpp, length);
	else
		ft_set_tex_e_tab_no_endian(param, adr, bpp, length);
	mlx_destroy_image(param->mlx, ret);
}
