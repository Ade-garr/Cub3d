/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 13:48:06 by ade-garr          #+#    #+#             */
/*   Updated: 2020/06/12 15:05:31 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_join(char *line, char *left)
{
	char	*dup;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!(dup = malloc(sizeof(char) * (ft_strlen(line) + ft_strlen(left) + 1))))
		return (NULL);
	while (line != NULL && line[i] != '\0')
	{
		dup[i] = (line)[i];
		i++;
	}
	while (left[j] != '\0' && left[j] != '\n')
	{
		dup[i + j] = left[j];
		j++;
	}
	dup[i + j] = '\0';
	free(line);
	return (dup);
}

void	ft_moveleft(char *left, char *newleft)
{
	int	i;

	i = 0;
	while (newleft[i] != '\0')
	{
		left[i] = newleft[i];
		i++;
	}
	left[i] = '\0';
}

int		ft_fill_line(int fd, char **line, char (*left)[BUFFER_SIZE + 1])
{
	int		ret;

	*line = NULL;
	*line = ft_join(*line, *left);
	if (*line == NULL)
		return (-1);
	while (ft_checkleft(*left) == 0)
	{
		ret = read(fd, *left, BUFFER_SIZE);
		if (ret == -1)
			return (ft_free2(line));
		if (ret == 0)
		{
			*left[0] = '\0';
			return (0);
		}
		(*left)[ret] = '\0';
		*line = ft_join(*line, *left);
		if (*line == NULL)
			return (ft_free2(line));
	}
	return (1);
}

int		ft_give_line(char **line, char *left)
{
	*line = NULL;
	*line = ft_join(*line, left);
	if (*line == NULL)
		return (-1);
	ft_moveleft(left, left + ft_position(left) + 1);
	return (1);
}

int		get_next_line(int fd, char **line)
{
	static char	left[BUFFER_SIZE + 1] = "";
	int			ret;

	if (line == NULL || fd < 0 || BUFFER_SIZE < 1)
		return (-1);
	if (ft_checkleft(left) == 0)
	{
		ret = ft_fill_line(fd, line, &left);
		if (ret == -1 || ret == 0)
			return (ret);
		ft_moveleft(left, left + ft_position(left) + 1);
	}
	else
	{
		ret = ft_give_line(line, left);
		if (ret == -1)
			return (ret);
	}
	return (1);
}
