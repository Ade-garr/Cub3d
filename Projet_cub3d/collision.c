/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 13:09:22 by ade-garr          #+#    #+#             */
/*   Updated: 2020/07/16 19:19:27 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_checkcollision(t_param *param, double speed, double rectx, double recty)
{
	double	deltax;
	double	deltay;
	double	radius;

	radius = 0.1;
	deltax = param->posx + param->dirx * speed -
	ft_max(rectx, ft_min(param->posx + param->dirx * speed, rectx + 1));
	deltay = param->posy + param->diry * speed -
	ft_max(recty, ft_min(param->posy + param->diry * speed, recty + 1));
	if (deltax * deltax + deltay * deltay < radius * radius)
		return (1);
	return (0);
}

int	ft_bodycollision4(t_param *param, double speed)
{
	double	rectx;
	double	recty;

	recty = floor(param->posy) + 1;
	rectx = floor(param->posx);
	if ((int)recty == 0 || (int)recty == param->mapheight - 1 ||
	(int)rectx == 0 || (int)rectx == param->mapwidth - 1)
	{
		if (ft_checkcollision(param, speed, rectx, recty) == 1)
			return (1);
	}
	rectx = floor(param->posx) + 1;
	if ((int)recty == 0 || (int)recty == param->mapheight - 1 ||
	(int)rectx == 0 || (int)rectx == param->mapwidth - 1)
	{
		if (ft_checkcollision(param, speed, rectx, recty) == 1)
			return (1);
	}
	return (0);
}

int	ft_bodycollision3(t_param *param, double speed)
{
	double	rectx;
	double	recty;

	recty = floor(param->posy);
	rectx = floor(param->posx) + 1;
	if ((int)recty == 0 || (int)recty == param->mapheight - 1 ||
	(int)rectx == 0 || (int)rectx == param->mapwidth - 1)
	{
		if (ft_checkcollision(param, speed, rectx, recty) == 1)
			return (1);
	}
	rectx = floor(param->posx) - 1;
	recty = floor(param->posy) + 1;
	if ((int)recty == 0 || (int)recty == param->mapheight - 1 ||
	(int)rectx == 0 || (int)rectx == param->mapwidth - 1)
	{
		if (ft_checkcollision(param, speed, rectx, recty) == 1)
			return (1);
	}
	return (ft_bodycollision4(param, speed));
}

int	ft_bodycollision2(t_param *param, double speed)
{
	double	rectx;
	double	recty;

	recty = floor(param->posy) - 1;
	rectx = floor(param->posx) + 1;
	if ((int)recty == 0 || (int)recty == param->mapheight - 1 ||
	(int)rectx == 0 || (int)rectx == param->mapwidth - 1)
	{
		if (ft_checkcollision(param, speed, rectx, recty) == 1)
			return (1);
	}
	rectx = floor(param->posx) - 1;
	recty = floor(param->posy);
	if ((int)recty == 0 || (int)recty == param->mapheight - 1 ||
	(int)rectx == 0 || (int)rectx == param->mapwidth - 1)
	{
		if (ft_checkcollision(param, speed, rectx, recty) == 1)
			return (1);
	}
	return (ft_bodycollision3(param, speed));
}

int	ft_bodycollision(t_param *param, double speed)
{
	double	rectx;
	double	recty;

	rectx = floor(param->posx) - 1;
	recty = floor(param->posy) - 1;
	if ((int)recty == 0 || (int)recty == param->mapheight - 1 ||
	(int)rectx == 0 || (int)rectx == param->mapwidth - 1)
	{
		if (ft_checkcollision(param, speed, rectx, recty) == 1)
			return (1);
	}
	rectx = floor(param->posx);
	if ((int)recty == 0 || (int)recty == param->mapheight - 1 ||
	(int)rectx == 0 || (int)rectx == param->mapwidth - 1)
	{
		if (ft_checkcollision(param, speed, rectx, recty) == 1)
			return (1);
	}
	return (ft_bodycollision2(param, speed));
}
