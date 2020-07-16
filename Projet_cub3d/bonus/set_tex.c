/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_tex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 09:47:20 by ade-garr          #+#    #+#             */
/*   Updated: 2020/07/13 20:25:11 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_set_tex_sprite_tab_no_endian(t_param *param, char *adr,
		int bpp, int length)
{
	int	x;
	int	y;

	y = -1;
	while (++y < param->tex_sprite->height)
	{
		x = -1;
		while (++x < param->tex_sprite->width)
			param->tex_sprite->tab[y * param->tex_sprite->width + x] =
			*(unsigned int *)(adr + y * length + x * bpp / 8);
	}
}

void	ft_set_tex_sprite_tab_endian(t_param *param, char *adr,
		int bpp, int length)
{
	int				x;
	int				y;
	unsigned int	color;

	y = -1;
	while (++y < param->tex_sprite->height)
	{
		x = -1;
		while (++x < param->tex_sprite->width)
		{
			color = *(unsigned int *)(adr + y * length + x * bpp / 8);
			color = ((color >> 24) & 0xff) | ((color << 8) & 0xff0000) |
			((color >> 8) & 0xff00) | ((color << 24) & 0xff000000);
			param->tex_sprite->tab[y * param->tex_sprite->width + x] = color;
		}
	}
}

void	ft_set_tex_sprite(t_param *param)
{
	char	*adr;
	void	*ret;
	int		bpp;
	int		length;
	int		endian;

	ret = mlx_xpm_file_to_image(param->mlx, param->fn_tex_sprite,
	&param->tex_sprite->width, &param->tex_sprite->height);
	if (ret == NULL)
		ft_exit2(param);
	adr = mlx_get_data_addr(ret, &bpp, &length, &endian);
	param->tex_sprite->tab = malloc(sizeof(unsigned int) *
	(param->tex_sprite->height * param->tex_sprite->width));
	if (param->tex_sprite->tab == NULL)
		ft_exit2(param);
	if (param->local_endian != endian)
		ft_set_tex_sprite_tab_endian(param, adr, bpp, length);
	else
		ft_set_tex_sprite_tab_no_endian(param, adr, bpp, length);
	mlx_destroy_image(param->mlx, ret);
}

void	ft_set_tex_n_tab_no_endian(t_param *param, char *adr,
		int bpp, int length)
{
	int	x;
	int	y;

	y = -1;
	while (++y < param->tex_n->height)
	{
		x = -1;
		while (++x < param->tex_n->width)
			param->tex_n->tab[y * param->tex_n->width + x] =
			*(unsigned int *)(adr + y * length + x * bpp / 8);
	}
}

void	ft_set_tex_n_tab_endian(t_param *param, char *adr, int bpp, int length)
{
	int				x;
	int				y;
	unsigned int	color;

	y = -1;
	while (++y < param->tex_n->height)
	{
		x = -1;
		while (++x < param->tex_n->width)
		{
			color = *(unsigned int *)(adr + y * length + x * bpp / 8);
			color = ((color >> 24) & 0xff) | ((color << 8) & 0xff0000) |
			((color >> 8) & 0xff00) | ((color << 24) & 0xff000000);
			param->tex_n->tab[y * param->tex_n->width + x] = color;
		}
	}
}
