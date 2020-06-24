/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 11:04:47 by ade-garr          #+#    #+#             */
/*   Updated: 2020/06/24 20:06:03 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_parsing_empty_line(int fd)
{
	char	*line;
	int		ret;

	ret = get_next_line(fd, &line);
	while (ret == 1 && line[0] == '\0')
	{
		free(line);
		ret = get_next_line(fd, &line);	
	}
	if (ret == -1 || ret == 0)
		ft_exit(4);
	ft_check_line(line);
	return (line);
}

void	ft_merge_lines(t_param *param, char *line, int height)
{
	int	i;
	char	**tmp_worldMap;

	i = 0;
	tmp_worldMap = param->worldMap;
	param->worldMap = malloc(sizeof(char *) * param->mapHeight);
	if (param->worldMap == NULL)
		ft_exit(4);
	while (i < height - 1)
	{
		param->worldMap[i] = tmp_worldMap[i];
		i++;
	}
	param->worldMap[i] = line;
	free(tmp_worldMap);
}

void	ft_parsing_map(t_param *param, int fd, char *line)
{
	int		ret;

	ret = 1;
	param->mapHeight = 1;
	param->worldMap = malloc(sizeof(char *) * param->mapHeight);
	if (param->worldMap == NULL)
		ft_exit(4);
	param->worldMap[0] = line;
	while (ret == 1)
	{	
		ret = get_next_line(fd, &line);
		if (ret >= 0)
		{
			ft_check_line(line);
			param->mapHeight++;
			ft_merge_lines(param, line, param->mapHeight);
		}
	}
	if (ret == -1)
		ft_exit(4);
}

void	ft_parsing_get_info(t_param *param, int fd)
{
	int	tab[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int	ret;
	char *line;

	while (ft_check_tab(tab) == 0)
	{
		ret = get_next_line(fd, &line);
		if (ret == -1)
			ft_exit4(param);
		if (ret == 0)
			ft_exit5(param, line);
		if (line[0] != '\0')
			ft_analyse_line(param, line, tab);
		free(line);
	}
}