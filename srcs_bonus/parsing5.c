/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 11:04:47 by ade-garr          #+#    #+#             */
/*   Updated: 2020/07/13 19:49:07 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_parsing_empty_line(t_param *param, int fd)
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
		ft_exit6(param, line);
	ft_check_line(param, line);
	return (line);
}

void	ft_merge_lines(t_param *param, char *line, int height)
{
	int		i;
	char	**tmp_worldmap;

	i = 0;
	tmp_worldmap = param->worldmap;
	param->worldmap = malloc(sizeof(char *) * param->mapheight);
	if (param->worldmap == NULL)
		ft_exit11(param, tmp_worldmap, line);
	while (i < height - 1)
	{
		param->worldmap[i] = tmp_worldmap[i];
		i++;
	}
	param->worldmap[i] = line;
	free(tmp_worldmap);
}

void	ft_parsing_map(t_param *param, int fd, char *line)
{
	int		ret;

	ret = 1;
	param->mapheight = 1;
	param->worldmap = malloc(sizeof(char *) * param->mapheight);
	if (param->worldmap == NULL)
		ft_exit6(param, line);
	param->worldmap[0] = line;
	while (ret == 1)
	{
		ret = get_next_line(fd, &line);
		if (ret >= 0)
		{
			ft_check_line(param, line);
			param->mapheight++;
			ft_merge_lines(param, line, param->mapheight);
		}
	}
	if (ret == -1)
		ft_exit10(param);
}

void	ft_parsing_get_info(t_param *param, int fd)
{
	int		tab[8];
	int		ret;
	char	*line;
	int		i;

	i = 0;
	while (i < 8)
	{
		tab[i] = 0;
		i++;
	}
	while (ft_check_tab(tab) == 0)
	{
		ret = get_next_line(fd, &line);
		if (ret == -1)
			ft_exit2(param);
		if (ret == 0)
			ft_exit5(param, line);
		if (line[0] != '\0')
			ft_analyse_line(param, line, tab);
		free(line);
	}
}
