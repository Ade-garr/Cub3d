/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 18:45:55 by ade-garr          #+#    #+#             */
/*   Updated: 2020/07/29 13:50:58 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_exit10(t_param *param)
{
	write(1, "Error\nImpossible to read cub file or to set up the game", 55);
	write(1, ", program stopped\n", 18);
	ft_free_param(param);
	exit(1);
}

void	ft_exit9(t_param *param, char **spltline, char *line)
{
	write(1, "Error\nInformation unknown or in double in .cub file\n", 52);
	free(line);
	ft_free_param(param);
	spltline = ft_free(&spltline);
	exit(1);
}

void	ft_exit8(t_param *param, char **spltline, char *line)
{
	write(1, "Error\nImpossible to read cub file or to set up the game", 55);
	write(1, ", program stopped\n", 18);
	free(line);
	ft_free_param(param);
	spltline = ft_free(&spltline);
	exit(1);
}

void	ft_exit7(t_param *param, char **spltline, char *line, int nb)
{
	if (nb == 0)
		write(1, "Error\nResolution information incorrect\n", 39);
	if (nb == 1)
		write(1, "Error\nNorth texture information incorrect\n", 42);
	if (nb == 2)
		write(1, "Error\nSouth texture information incorrect\n", 42);
	if (nb == 3)
		write(1, "Error\nWest texture information incorrect\n", 41);
	if (nb == 4)
		write(1, "Error\nEast texture information incorrect\n", 41);
	if (nb == 5)
		write(1, "Error\nSprite texture information incorrect\n", 43);
	if (nb == 6)
		write(1, "Error\nFloor color information incorrect\n", 40);
	if (nb == 7)
		write(1, "Error\nCell color information incorrect\n", 39);
	if (nb == 8)
		write(1, "Error\nResolution <= 0\n", 22);
	free(line);
	ft_free_param(param);
	spltline = ft_free(&spltline);
	exit(1);
}

void	ft_exit6(t_param *param, char *line)
{
	write(1, "Error\nImpossible to read cub file or to set up the game", 55);
	write(1, ", program stopped\n", 18);
	free(line);
	ft_free_param(param);
	exit(1);
}
