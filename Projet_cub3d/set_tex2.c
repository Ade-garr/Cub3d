/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_tex2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 11:21:11 by ade-garr          #+#    #+#             */
/*   Updated: 2020/06/24 20:06:01 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_set_tex_w_tab_endian(t_param *param, char *adr, int bpp, int length)
{
	int	x;
	int	y;
	unsigned int	color;

	y = -1;
	while (++y < param->tex_W->height)
	{
		x = -1;
		while (++x < param->tex_W->width)
		{
			color = *(unsigned int *)(adr + y * length + x * bpp / 8);
			color = ((color>>24)&0xff) | ((color<<8)&0xff0000) | ((color>>8)&0xff00) | ((color<<24)&0xff000000);
			param->tex_W->tab[y * param->tex_W->width + x] = color;
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

	ret = mlx_xpm_file_to_image(param->mlx, param->fn_tex_W, &param->tex_W->width, &param->tex_W->height);
	if (ret == NULL)
		ft_exit2(param);
	adr = mlx_get_data_addr(ret, &bpp, &length, &endian);
	param->tex_W->tab = malloc(sizeof(unsigned int) * (param->tex_W->height * param->tex_W->width));
	if (param->tex_W->tab == NULL)
		ft_exit2(param);
	if (param->local_endian != endian)
		ft_set_tex_w_tab_endian(param, adr, bpp, length);
	else
		ft_set_tex_w_tab_no_endian(param, adr, bpp, length);
	mlx_destroy_image(param->mlx, ret);
}

void	ft_set_tex_e_tab_no_endian(t_param *param, char *adr, int bpp, int length)
{
	int	x;
	int	y;

	y = -1;
	while (++y < param->tex_E->height)
	{
		x = -1;
		while (++x < param->tex_E->width)
			param->tex_E->tab[y * param->tex_E->width + x] = *(unsigned int *)(adr + y * length + x * bpp / 8);
	}
}

void	ft_set_tex_e_tab_endian(t_param *param, char *adr, int bpp, int length)
{
	int	x;
	int	y;
	unsigned int	color;

	y = -1;
	while (++y < param->tex_E->height)
	{
		x = -1;
		while (++x < param->tex_E->width)
		{
			color = *(unsigned int *)(adr + y * length + x * bpp / 8);
			color = ((color>>24)&0xff) | ((color<<8)&0xff0000) | ((color>>8)&0xff00) | ((color<<24)&0xff000000);
			param->tex_E->tab[y * param->tex_E->width + x] = color;
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

	ret = mlx_xpm_file_to_image(param->mlx, param->fn_tex_E, &param->tex_E->width, &param->tex_E->height);
	if (ret == NULL)
		ft_exit2(param);
	adr = mlx_get_data_addr(ret, &bpp, &length, &endian);
	param->tex_E->tab = malloc(sizeof(unsigned int) * (param->tex_E->height * param->tex_E->width));
	if (param->tex_E->tab == NULL)
		ft_exit2(param);
	if (param->local_endian != endian)
		ft_set_tex_e_tab_endian(param, adr, bpp, length);
	else
		ft_set_tex_e_tab_no_endian(param, adr, bpp, length);
	mlx_destroy_image(param->mlx, ret);
}