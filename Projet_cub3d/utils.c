/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 12:23:43 by ade-garr          #+#    #+#             */
/*   Updated: 2020/06/17 13:08:47 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_max(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}

double	ft_min(double a, double b)
{
	if (a < b)
		return (a);
	return (b);
}

int	ft_check_arg(char *str)
{
	char cmp[] = "--save";
	int	i;

	i = 0;
	if (ft_strlen(str) != 6)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] != cmp[i])
			return (0);
		i++;
	}
	return (1);
}

void    ft_exit_bis(int nb)
{
    if (nb == 10)
		write(1, "Error : west texture information incorrect\n", 43);
	if (nb == 11)
		write(1, "Error : east texture information incorrect\n", 43);
	if (nb == 12)
		write(1, "Error : sprite texture information incorrect\n", 45);
	if (nb == 13)
		write(1, "Error : floor color information incorrect\n", 42);
	if (nb == 14)
		write(1, "Error : cell color information incorrect\n", 41);
	if (nb == 15)
		write(1, "Error : resolution <= 0\n", 24);
	if (nb == 16)
		write(1, "Error : incorrect map\n", 22);
	if (nb == 17)
		write(1, "Image successfully created\n", 27);
	exit(1);
}

void	ft_exit(int nb)
{
	if (nb == 1)
		write(1, "Error : failed to create an image\n", 34);
	if (nb == 2)
		write(1, "Error : invalid arguments\n", 26);
	if (nb == 3)
		write(1, "Error : invalid .cub filename or couldn't open the file\n", 56);
	if (nb == 4)
		write(1, "Error : impossible to read cub file or to set up the game, program stopped\n", 75);
	if (nb == 5)
		write(1, "Error : incorrect .cub file\n", 28);
	if (nb == 6)
		write(1, "Error : information unknown or in double in .cub file\n", 54);
	if (nb == 7)
		write(1, "Error : resolution information incorrect\n", 41);
	if (nb == 8)
		write(1, "Error : north texture information incorrect\n", 44);
	if (nb == 9)
		write(1, "Error : south texture information incorrect\n", 44);
    ft_exit_bis(nb);
}