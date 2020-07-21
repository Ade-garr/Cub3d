/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 12:21:08 by ade-garr          #+#    #+#             */
/*   Updated: 2020/07/21 16:13:24 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_exithook(t_param *param)
{
	(void)param;
	ft_free_param(param);
	write(1, "Program successfully exited\n", 28);
	exit(1);
	return (1);
}

int		ft_keypress(int key, t_param *param)
{
	if (key == 122)
		param->tab[0] = 1;
	if (key == 115)
		param->tab[1] = 1;
	if (key == 113)
		param->tab[2] = 1;
	if (key == 100)
		param->tab[3] = 1;
	if (key == 65363)
		param->tab[4] = 1;
	if (key == 65361)
		param->tab[5] = 1;
	if (key == 65505)
		param->tab[6] = 1;
	if (key == 65307)
		ft_exithook(param);
	if (key == 65507)
		param->tab[7] = 1;
	if (key == 65362)
		param->tab[8] = 1;
	if (key == 65364)
		param->tab[9] = 1;
	return (1);
}

int		ft_keyrelease(int key, t_param *param)
{
	if (key == 122)
		param->tab[0] = 0;
	if (key == 115)
		param->tab[1] = 0;
	if (key == 113)
		param->tab[2] = 0;
	if (key == 100)
		param->tab[3] = 0;
	if (key == 65363)
		param->tab[4] = 0;
	if (key == 65361)
		param->tab[5] = 0;
	if (key == 65505)
		param->tab[6] = 0;
	if (key == 65507)
		param->tab[7] = 0;
	if (key == 65362)
		param->tab[8] = 0;
	if (key == 65364)
		param->tab[9] = 0;
	return (1);
}

void	ft_loop7(t_param *param, double speed, double rotspd)
{
	if (param->tab[7] == 0)
		param->crouch = 0;
	if (param->tab[0] == 1)
	{
		if (param->worldmap[(int)(param->posy + param->diry * speed)]
		[(int)(param->posx + param->dirx * speed)] != '1' &&
		param->worldmap[(int)(param->posy + param->diry * speed)]
		[(int)(param->posx + param->dirx * speed)] != '2' &&
		ft_bodycollision(param, speed) == 0)
		{
			param->posx += param->dirx * speed;
			param->posy += param->diry * speed;
		}
	}
	ft_loop2(param, speed);
	ft_loop3(param, speed);
	ft_loop4(param, speed);
	ft_loop5(param, rotspd);
	ft_raycasting(param);
	mlx_put_image_to_window(param->mlx, param->win, param->img, 0, 0);
}

void	ft_loop6(t_param *param, double speed, double rotspd)
{
	if (param->tab[6] == 0)
	{
		param->stamina += 1;
		if (param->stamina > 200)
			param->stamina = 200;
	}
	if (param->tab[7] == 1)
	{
		param->crouch = -param->winy / 6;
		speed = speed / 2;
	}
	if (param->tab[8] == 1)
	{
		if (param->updown < param->winy / 2)
			param->updown += 5;
	}
	if (param->tab[9] == 1)
	{
		if (param->updown > -param->winy / 2)
			param->updown -= 5;
	}
	ft_loop7(param, speed, rotspd);
}
