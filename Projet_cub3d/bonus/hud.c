/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 13:32:59 by ade-garr          #+#    #+#             */
/*   Updated: 2020/07/21 16:34:23 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_hud5(t_param *param, int y)
{
	int		x;
	char	*adr;

	x = 10;
	while (x <= 213)
	{
		adr = param->imgadr + (y * param->imglenght + x * (param->imgbpp / 8));
		*(unsigned int *)adr = 0x000000;
		x++;
	}
	y++;
	x = 10;
	while (x <= 213)
	{
		adr = param->imgadr + (y * param->imglenght + x * (param->imgbpp / 8));
		*(unsigned int *)adr = 0x000000;
		x++;
	}
}

void	ft_hud4(t_param *param)
{
	int		y;
	int		x;
	char	*adr;

	y = 12;
	while (y <= 32)
	{
		ft_color_red(param, 10, y);
		ft_color_red(param, 11, y);
		x = 12;
		while (x - 11 <= param->stamina)
		{
			adr = param->imgadr + (y * param->imglenght +
			x * (param->imgbpp / 8));
			*(unsigned int *)adr = 0x339966;
			x++;
		}
		ft_color_red(param, 212, y);
		ft_color_red(param, 213, y);
		y++;
	}
	ft_hud5(param, y);
}

void	ft_hud3(t_param *param)
{
	int		y;
	int		x;
	char	*adr;

	x = 10;
	y = 10;
	while (x <= 213)
	{
		adr = param->imgadr + (y * param->imglenght + x * (param->imgbpp / 8));
		*(unsigned int *)adr = 0x000000;
		x++;
	}
	y = 11;
	x = 10;
	while (x <= 213)
	{
		adr = param->imgadr + (y * param->imglenght + x * (param->imgbpp / 8));
		*(unsigned int *)adr = 0x000000;
		x++;
	}
	ft_hud4(param);
}

void	ft_hud2(t_param *param)
{
	int		y;
	int		x;
	char	*adr;

	x = param->winx / 2 - 15;
	while (x < param->winx / 2 + 15)
	{
		y = param->winy / 2 - 1;
		while (y < param->winy / 2 + 1)
		{
			adr = param->imgadr + (y * param->imglenght +
			x * (param->imgbpp / 8));
			*(unsigned int *)adr = 0xFF3333;
			y++;
		}
		x++;
		if (x == param->winx / 2 - 3)
			x = param->winx / 2 + 3;
	}
	ft_hud3(param);
}

void	ft_hud(t_param *param)
{
	int		y;
	int		x;
	char	*adr;

	y = param->winy / 2 - 15;
	while (y < param->winy / 2 + 15)
	{
		x = param->winx / 2 - 1;
		while (x < param->winx / 2 + 1)
		{
			adr = param->imgadr + (y * param->imglenght +
			x * (param->imgbpp / 8));
			*(unsigned int *)adr = 0xFF3333;
			x++;
		}
		y++;
		if (y == param->winy / 2 - 3)
			y = param->winy / 2 + 3;
	}
	ft_hud2(param);
}
