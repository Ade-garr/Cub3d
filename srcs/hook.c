/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 11:25:09 by ade-garr          #+#    #+#             */
/*   Updated: 2020/07/16 19:23:27 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_loop5(t_param *param, double rotspd)
{
	double	oldplaney;
	double	olddiry;

	if (param->tab[4] == 1)
	{
		olddiry = param->diry;
		param->diry = param->diry * cos(-rotspd) - param->dirx * sin(-rotspd);
		param->dirx = olddiry * sin(-rotspd) + param->dirx * cos(-rotspd);
		oldplaney = param->planey;
		param->planey = param->planey * cos(-rotspd) -
		param->planex * sin(-rotspd);
		param->planex = oldplaney * sin(-rotspd) +
		param->planex * cos(-rotspd);
	}
	if (param->tab[5] == 1)
	{
		olddiry = param->diry;
		param->diry = param->diry * cos(rotspd) - param->dirx * sin(rotspd);
		param->dirx = olddiry * sin(rotspd) + param->dirx * cos(rotspd);
		oldplaney = param->planey;
		param->planey = param->planey * cos(rotspd) -
		param->planex * sin(rotspd);
		param->planex = oldplaney * sin(rotspd) +
		param->planex * cos(rotspd);
	}
}

void	ft_loop4(t_param *param, double speed)
{
	double	olddirx;
	double	olddiry;

	if (param->tab[3] == 1)
	{
		olddirx = param->dirx;
		olddiry = param->diry;
		param->diry = param->diry * cos(-M_PI / 2) -
		param->dirx * sin(-M_PI / 2);
		param->dirx = olddiry * sin(-M_PI / 2) + param->dirx * cos(-M_PI / 2);
		if ((int)(param->posy + param->diry * speed) != 0 &&
		(int)(param->posy + param->diry * speed) != param->mapheight - 1 &&
		(int)(param->posx + param->dirx * speed) != 0 &&
		(int)(param->posx + param->dirx * speed) != param->mapwidth - 1 &&
		ft_bodycollision(param, speed) == 0)
		{
			param->posx += param->dirx * speed;
			param->posy += param->diry * speed;
		}
		param->dirx = olddirx;
		param->diry = olddiry;
	}
}

void	ft_loop3(t_param *param, double speed)
{
	double	olddirx;
	double	olddiry;

	if (param->tab[2] == 1)
	{
		olddirx = param->dirx;
		olddiry = param->diry;
		param->diry = param->diry * cos(M_PI / 2) - param->dirx * sin(M_PI / 2);
		param->dirx = olddiry * sin(M_PI / 2) + param->dirx * cos(M_PI / 2);
		if ((int)(param->posy + param->diry * speed) != 0 &&
		(int)(param->posy + param->diry * speed) != param->mapheight - 1 &&
		(int)(param->posx + param->dirx * speed) != 0 &&
		(int)(param->posx + param->dirx * speed) != param->mapwidth - 1 &&
		ft_bodycollision(param, speed) == 0)
		{
			param->posx += param->dirx * speed;
			param->posy += param->diry * speed;
		}
		param->dirx = olddirx;
		param->diry = olddiry;
	}
}

void	ft_loop2(t_param *param, double speed)
{
	double	olddirx;
	double	olddiry;

	if (param->tab[1] == 1)
	{
		olddirx = param->dirx;
		olddiry = param->diry;
		param->dirx = -param->dirx;
		param->diry = -param->diry;
		if ((int)(param->posy + param->diry * speed) != 0 &&
		(int)(param->posy + param->diry * speed) != param->mapheight - 1 &&
		(int)(param->posx + param->dirx * speed) != 0 &&
		(int)(param->posx + param->dirx * speed) != param->mapwidth - 1 &&
		ft_bodycollision(param, speed) == 0)
		{
			param->posx += param->dirx * speed;
			param->posy += param->diry * speed;
		}
		param->dirx = olddirx;
		param->diry = olddiry;
	}
}

int		ft_loop(t_param *param)
{
	double	speed;
	double	rotspeed;

	speed = 0.025;
	rotspeed = 0.025;
	if (param->tab[6] == 1)
		speed = 0.05;
	if (param->tab[0] == 1)
	{
		if ((int)(param->posy + param->diry * speed) != 0 && (int)(param->posy +
		param->diry * speed) != param->mapheight - 1 && (int)(param->posx +
		param->dirx * speed) != 0 && (int)(param->posx + param->dirx * speed) !=
		param->mapwidth - 1 && ft_bodycollision(param, speed) == 0)
		{
			param->posx += param->dirx * speed;
			param->posy += param->diry * speed;
		}
	}
	ft_loop2(param, speed);
	ft_loop3(param, speed);
	ft_loop4(param, speed);
	ft_loop5(param, rotspeed);
	ft_raycasting(param);
	mlx_put_image_to_window(param->mlx, param->win, param->img, 0, 0);
	return (1);
}
