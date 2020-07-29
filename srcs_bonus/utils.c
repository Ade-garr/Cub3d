/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 12:23:43 by ade-garr          #+#    #+#             */
/*   Updated: 2020/07/29 13:52:13 by ade-garr         ###   ########.fr       */
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

int		ft_check_arg(char *str)
{
	char	cmp[7];
	int		i;

	cmp[0] = '-';
	cmp[1] = '-';
	cmp[2] = 's';
	cmp[3] = 'a';
	cmp[4] = 'v';
	cmp[5] = 'e';
	cmp[6] = '\0';
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

void	ft_exit17(void)
{
	write(1, "Error\nInvalid arguments\n", 24);
	exit(1);
}

void	ft_exit16(t_param *param)
{
	ft_free_param(param);
	exit(1);
}
