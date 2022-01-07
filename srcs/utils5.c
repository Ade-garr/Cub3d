/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 18:46:44 by ade-garr          #+#    #+#             */
/*   Updated: 2022/01/07 12:51:26 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_exit5(t_param *param, char *line)
{
	write(1, "Error\nIncorrect .cub file\n", 26);
	free(line);
	ft_free_param(param);
	exit(1);
}

void	ft_exit4(t_param *param, char *line)
{
	write(1, "Error\nIncorrect map\n", 20);
	free(line);
	ft_free_param(param);
	exit(1);
}

void	ft_exit3(t_param *param)
{
	write(1, "Error\nInvalid .cub filename or couldn't open the file\n", 54);
	ft_free_param(param);
	exit(1);
}

void	ft_exit2(t_param *param)
{
	write(1, "Error\nImpossible to read cub file or to set up the game", 55);
	write(1, ", program stopped\n", 18);
	ft_free_param(param);
	exit(1);
}

void	ft_exit1(void)
{
	write(1, "Error\nImpossible to read cub file or to set up the game", 55);
	write(1, ", program stopped\n", 18);
	exit(1);
}
