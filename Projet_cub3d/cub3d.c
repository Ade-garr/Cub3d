/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 18:44:08 by ade-garr          #+#    #+#             */
/*   Updated: 2020/07/13 17:01:10 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_set_tabs_tex(t_param *param)
{
	if ((param->tab_dist_wall = malloc(sizeof(double) * param->winx)) == NULL)
		ft_exit2(param);
	if ((param->tex_n = malloc(sizeof(t_tex) * 1)) == NULL)
		ft_exit2(param);
	param->tex_n->tab = NULL;
	if ((param->tex_s = malloc(sizeof(t_tex) * 1)) == NULL)
		ft_exit2(param);
	param->tex_s->tab = NULL;
	if ((param->tex_w = malloc(sizeof(t_tex) * 1)) == NULL)
		ft_exit2(param);
	param->tex_w->tab = NULL;
	if ((param->tex_e = malloc(sizeof(t_tex) * 1)) == NULL)
		ft_exit2(param);
	param->tex_e->tab = NULL;
	if ((param->tex_sprite = malloc(sizeof(t_tex) * 1)) == NULL)
		ft_exit2(param);
	param->tex_sprite->tab = NULL;
	ft_set_local_endian(param);
	ft_set_tex_n(param);
	ft_set_tex_s(param);
	ft_set_tex_w(param);
	ft_set_tex_e(param);
	ft_set_tex_sprite(param);
}

void	ft_launch_cub3d(t_param *param, int argc)
{
	param->img = mlx_new_image(param->mlx, param->winx, param->winy);
	if (param->img == NULL)
		ft_exit2(param);
	param->imgadr = mlx_get_data_addr(param->img, &param->imgbpp,
	&param->imglenght, &param->endian);
	if (argc == 2)
	{
		param->win = mlx_new_window(param->mlx,
		param->winx, param->winy, "Cub3d");
		if (param->win == NULL)
			ft_exit2(param);
		mlx_hook(param->win, 2, 1L << 0, ft_keypress, param);
		mlx_hook(param->win, 3, 1L << 1, ft_keyrelease, param);
		mlx_hook(param->win, 17, 1L << 17, ft_exithook, param);
		mlx_loop_hook(param->mlx, ft_loop, param);
		mlx_loop(param->mlx);
	}
	else
	{
		ft_raycasting(param);
		ft_create_img(param);
	}
}

int		main(int argc, char **argv)
{
	t_param	*param;

	if ((argc == 2 && ft_check_filename(argv[1]) == 1) || (argc == 3 &&
	ft_check_arg(argv[2]) == 1 && ft_check_filename(argv[1]) == 1))
	{
		param = malloc(sizeof(t_param) * 1);
		if (param == NULL)
			ft_exit1();
		ft_init(param);
		param->mlx = mlx_init();
		if (param->mlx == NULL)
			ft_exit2(param);
		ft_parsing(param, argv[1]);
		ft_set_tabs_tex(param);
		ft_set_sprite(param);
		ft_launch_cub3d(param, argc);
	}
	else
		ft_exit17();
	return (1);
}
