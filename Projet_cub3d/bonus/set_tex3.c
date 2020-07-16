/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_tex3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 11:22:17 by ade-garr          #+#    #+#             */
/*   Updated: 2020/07/13 20:34:31 by ade-garr         ###   ########.fr       */
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

	ret = mlx_xpm_file_to_image(param->mlx, param->fn_tex_n,
	&param->tex_n->width, &param->tex_n->height);
	if (ret == NULL)
		ft_exit2(param);
	adr = mlx_get_data_addr(ret, &bpp, &length, &endian);
	param->tex_n->tab = malloc(sizeof(unsigned int) *
	(param->tex_n->height * param->tex_n->width));
	if (param->tex_n->tab == NULL)
		ft_exit2(param);
	if (param->local_endian != endian)
		ft_set_tex_n_tab_endian(param, adr, bpp, length);
	else
		ft_set_tex_n_tab_no_endian(param, adr, bpp, length);
	mlx_destroy_image(param->mlx, ret);
}

void	ft_set_tex_s_tab_no_endian(t_param *param, char *adr,
		int bpp, int length)
{
	int	x;
	int	y;

	y = -1;
	while (++y < param->tex_s->height)
	{
		x = -1;
		while (++x < param->tex_s->width)
			param->tex_s->tab[y * param->tex_s->width + x] =
			*(unsigned int *)(adr + y * length + x * bpp / 8);
	}
}

void	ft_set_tex_s_tab_endian(t_param *param, char *adr, int bpp, int length)
{
	int				x;
	int				y;
	unsigned int	color;

	y = -1;
	while (++y < param->tex_s->height)
	{
		x = -1;
		while (++x < param->tex_s->width)
		{
			color = *(unsigned int *)(adr + y * length + x * bpp / 8);
			color = ((color >> 24) & 0xff) | ((color << 8) & 0xff0000) |
			((color >> 8) & 0xff00) | ((color << 24) & 0xff000000);
			param->tex_s->tab[y * param->tex_s->width + x] = color;
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

	ret = mlx_xpm_file_to_image(param->mlx, param->fn_tex_s,
	&param->tex_s->width, &param->tex_s->height);
	if (ret == NULL)
		ft_exit2(param);
	adr = mlx_get_data_addr(ret, &bpp, &length, &endian);
	param->tex_s->tab = malloc(sizeof(unsigned int) *
	(param->tex_s->height * param->tex_s->width));
	if (param->tex_s->tab == NULL)
		ft_exit2(param);
	if (param->local_endian != endian)
		ft_set_tex_s_tab_endian(param, adr, bpp, length);
	else
		ft_set_tex_s_tab_no_endian(param, adr, bpp, length);
	mlx_destroy_image(param->mlx, ret);
}

void	ft_set_tex_w_tab_no_endian(t_param *param, char *adr,
		int bpp, int length)
{
	int	x;
	int	y;

	y = -1;
	while (++y < param->tex_w->height)
	{
		x = -1;
		while (++x < param->tex_w->width)
			param->tex_w->tab[y * param->tex_w->width + x] =
			*(unsigned int *)(adr + y * length + x * bpp / 8);
	}
}
