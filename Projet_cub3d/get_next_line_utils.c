/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 19:28:30 by ade-garr          #+#    #+#             */
/*   Updated: 2020/06/17 14:16:43 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_position(char *left)
{
	int	i;

	i = 0;
	while (left[i])
	{
		if (left[i] == '\n')
			return (i);
		i++;
	}
	return (0);
}

int		ft_free_line(char **line)
{
	free(*line);
	*line = NULL;
	return (-1);
}

int		ft_checkleft(char *left)
{
	int i;

	i = 0;
	if (left == NULL)
		return (0);
	while (left[i] != '\0')
	{
		if (left[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}