/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 11:25:09 by ade-garr          #+#    #+#             */
/*   Updated: 2020/06/17 15:31:40 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    ft_loop5(t_param *param, double rotSpeed)
{
    double	oldPlaneY;
    double	oldDirY;

    if (param->tab[4] == 1)
	{
		oldDirY = param->dirY;
		param->dirY = param->dirY * cos(-rotSpeed) - param->dirX * sin(-rotSpeed);
		param->dirX = oldDirY * sin(-rotSpeed) + param->dirX * cos(-rotSpeed);
		oldPlaneY = param->planeY;
		param->planeY = param->planeY * cos(-rotSpeed) - param->planeX * sin(-rotSpeed);
		param->planeX = oldPlaneY * sin(-rotSpeed) + param->planeX * cos(-rotSpeed);
	}
	if (param->tab[5] == 1)
	{
		oldDirY = param->dirY;
		param->dirY = param->dirY * cos(rotSpeed) - param->dirX * sin(rotSpeed);
		param->dirX = oldDirY * sin(rotSpeed) + param->dirX * cos(rotSpeed);
		oldPlaneY = param->planeY;
		param->planeY = param->planeY * cos(rotSpeed) - param->planeX * sin(rotSpeed);
		param->planeX = oldPlaneY * sin(rotSpeed) + param->planeX * cos(rotSpeed);
	}
}

void    ft_loop4(t_param *param, double Speed)
{
    double	oldDirX;
	double	oldDirY;

    if (param->tab[3] == 1)
	{
		oldDirX = param->dirX;
		oldDirY = param->dirY;
		param->dirY = param->dirY * cos(-M_PI/2) - param->dirX * sin(-M_PI/2);
		param->dirX = oldDirY * sin(-M_PI/2) + param->dirX * cos(-M_PI/2);
		if(param->worldMap[(int)(param->posY + param->dirY * Speed)][(int)(param->posX + param->dirX * Speed)] != '1' && ft_bodycollision(param, Speed) == 0) 
		{
			param->posX += param->dirX * Speed;
			param->posY += param->dirY * Speed;
		}
		param->dirX = oldDirX;
		param->dirY = oldDirY;
	}
}

void    ft_loop3(t_param *param, double Speed)
{
    double	oldDirX;
	double	oldDirY;

	if (param->tab[2] == 1)
	{
		oldDirX = param->dirX;
		oldDirY = param->dirY;
		param->dirY = param->dirY * cos(M_PI/2) - param->dirX * sin(M_PI/2);
		param->dirX = oldDirY * sin(M_PI/2) + param->dirX * cos(M_PI/2);
		if(param->worldMap[(int)(param->posY + param->dirY * Speed)][(int)(param->posX + param->dirX * Speed)] != '1' && ft_bodycollision(param, Speed) == 0) 
		{
			param->posX += param->dirX * Speed;
			param->posY += param->dirY * Speed;
		}
		param->dirX = oldDirX;
		param->dirY = oldDirY;
	}
}

void    ft_loop2(t_param *param, double Speed)
{
    double	oldDirX;
	double	oldDirY;

    if (param->tab[1] == 1)
	{
		oldDirX = param->dirX;
		oldDirY = param->dirY;
		param->dirX = - param->dirX;
		param->dirY = - param->dirY;
		if (param->worldMap[(int)(param->posY + param->dirY * Speed)][(int)(param->posX + param->dirX * Speed)] != '1' && ft_bodycollision(param, Speed) == 0)
		{
			param->posX += param->dirX * Speed;
			param->posY += param->dirY * Speed;
		}
		param->dirX = oldDirX;
		param->dirY = oldDirY;
	}
}

int	ft_loop(t_param *param)
{
	double	Speed;
	double	rotSpeed;

	Speed = 0.025;
	rotSpeed = 0.025;
	if (param->tab[6] == 1)
		Speed = 0.05;
	if (param->tab[0] == 1)
	{
		if (param->worldMap[(int)(param->posY + param->dirY * Speed)][(int)(param->posX + param->dirX * Speed)] != '1' && ft_bodycollision(param, Speed) == 0)
		{	
			param->posX += param->dirX * Speed;
			param->posY += param->dirY * Speed;
		}
	}
    ft_loop2(param, Speed);
    ft_loop3(param, Speed);
    ft_loop4(param, Speed);
    ft_loop5(param, rotSpeed);
    ft_raycasting(param);
	mlx_put_image_to_window(param->mlx, param->win, param->img, 0, 0);
	return (1);
}