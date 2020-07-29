/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 13:53:54 by ade-garr          #+#    #+#             */
/*   Updated: 2019/11/12 15:44:56 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_checkres(int k, int l, long j)
{
	if (k == 1)
		j = j * -1;
	if (j > 2147483647 || (l > 10 && k == 0))
		return (-1);
	if (j < -2147483648 || (l > 10 && k == 1))
		return (0);
	return (j);
}

int			ft_atoi(const char *nptr)
{
	int		i;
	long	j;
	int		k;
	int		l;

	l = 0;
	i = 0;
	j = 0;
	k = 0;
	while (nptr[i] == ' ' || nptr[i] == '\r' || nptr[i] == '\t' ||
			nptr[i] == '\v' || nptr[i] == '\f' || nptr[i] == '\n')
		i++;
	if (nptr[i] == '-')
		k++;
	if (nptr[i] == '-' || nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9' && l <= 10)
	{
		j = j * 10 + (nptr[i] - 48);
		i++;
		l++;
	}
	return (ft_checkres(k, l, j));
}
