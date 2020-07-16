/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 18:45:55 by ade-garr          #+#    #+#             */
/*   Updated: 2020/07/14 12:46:23 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_exit10(t_param *param)
{
	write(1, "Error : impossible to read cub file or to set up the game", 57);
	write(1, ", program stopped\n", 18);
	ft_free_param(param);
	exit(1);
}

void	ft_exit9(t_param *param, char **spltline, char *line)
{
	write(1, "Error : information unknown or in double in .cub file\n", 54);
	free(line);
	ft_free_param(param);
	spltline = ft_free(&spltline);
	exit(1);
}

void	ft_exit8(t_param *param, char **spltline, char *line)
{
	write(1, "Error : impossible to read cub file or to set up the game", 57);
	write(1, ", program stopped\n", 18);
	free(line);
	ft_free_param(param);
	spltline = ft_free(&spltline);
	exit(1);
}

void	ft_exit7(t_param *param, char **spltline, char *line, int nb)
{
	if (nb == 0)
		write(1, "Error : resolution information incorrect\n", 41);
	if (nb == 1)
		write(1, "Error : north texture information incorrect\n", 44);
	if (nb == 2)
		write(1, "Error : south texture information incorrect\n", 44);
	if (nb == 3)
		write(1, "Error : west texture information incorrect\n", 43);
	if (nb == 4)
		write(1, "Error : east texture information incorrect\n", 43);
	if (nb == 5)
		write(1, "Error : sprite texture information incorrect\n", 45);
	if (nb == 6)
		write(1, "Error : floor color information incorrect\n", 42);
	if (nb == 7)
		write(1, "Error : cell color information incorrect\n", 41);
	if (nb == 8)
		write(1, "Error : resolution <= 0\n", 24);
	free(line);
	ft_free_param(param);
	spltline = ft_free(&spltline);
	exit(1);
}

void	ft_exit6(t_param *param, char *line)
{
	write(1, "Error : impossible to read cub file or to set up the game", 57);
	write(1, ", program stopped\n", 18);
	free(line);
	ft_free_param(param);
	exit(1);
}
