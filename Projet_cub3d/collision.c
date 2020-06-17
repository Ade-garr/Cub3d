/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 13:09:22 by ade-garr          #+#    #+#             */
/*   Updated: 2020/06/17 14:46:38 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_checkcollision(t_param *param, double Speed, double rectX, double rectY)
{
	double	deltaX;
	double	deltaY;
	double	radius;
	
	radius = 0.1;
	deltaX = param->posX + param->dirX * Speed - ft_max(rectX, ft_min(param->posX + param->dirX * Speed, rectX + 1));
	deltaY = param->posY + param->dirY * Speed - ft_max(rectY, ft_min(param->posY + param->dirY * Speed, rectY + 1));
	if (deltaX * deltaX + deltaY * deltaY < radius * radius)
		return (1);
	return (0);
}

int	ft_bodycollision3(t_param *param, double Speed)
{
    double	rectX;
	double	rectY;
    
    rectY = floor(param->posY) + 1;
    rectX = floor(param->posX);
	if (param->worldMap[(int)rectY][(int)rectX] == '1')
	{
		if (ft_checkcollision(param, Speed, rectX, rectY) == 1)
			return (1);
	}
	rectX = floor(param->posX) + 1;
	if (param->worldMap[(int)rectY][(int)rectX] == '1')
	{
		if (ft_checkcollision(param, Speed, rectX, rectY) == 1)
			return (1);
	}
	return (0);
}

int	ft_bodycollision2(t_param *param, double Speed)
{
    double	rectX;
	double	rectY;

    rectX = floor(param->posX) - 1;
	rectY = floor(param->posY);
	if (param->worldMap[(int)rectY][(int)rectX] == '1')
	{
		if (ft_checkcollision(param, Speed, rectX, rectY) == 1)
			return (1);
	}
	rectX = floor(param->posX) + 1;
	if (param->worldMap[(int)rectY][(int)rectX] == '1')
	{
		if (ft_checkcollision(param, Speed, rectX, rectY) == 1)
			return (1);
	}
	rectX = floor(param->posX) - 1;
	rectY = floor(param->posY) + 1;
	if (param->worldMap[(int)rectY][(int)rectX] == '1')
	{
		if (ft_checkcollision(param, Speed, rectX, rectY) == 1)
			return (1);
	}
    return(ft_bodycollision3(param, Speed));
}

int	ft_bodycollision(t_param *param, double Speed)
{	
	double	rectX;
	double	rectY;

	rectX = floor(param->posX) - 1;
	rectY = floor(param->posY) - 1;
	if (param->worldMap[(int)rectY][(int)rectX] == '1')
	{
		if (ft_checkcollision(param, Speed, rectX, rectY) == 1)
			return (1);
	}
	rectX = floor(param->posX);
	if (param->worldMap[(int)rectY][(int)rectX] == '1')
	{
		if (ft_checkcollision(param, Speed, rectX, rectY) == 1)
			return (1);
	}
	rectX = floor(param->posX) + 1;
	if (param->worldMap[(int)rectY][(int)rectX] == '1')
	{
		if (ft_checkcollision(param, Speed, rectX, rectY) == 1)
			return (1);
	}
    return(ft_bodycollision2(param, Speed));
}