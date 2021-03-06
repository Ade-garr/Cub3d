/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 18:44:32 by ade-garr          #+#    #+#             */
/*   Updated: 2020/07/29 13:52:59 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_exit15(t_param *param)
{
	write(1, "Error\nFailed to create an image\n", 32);
	ft_free_param(param);
	exit(1);
}

void	ft_exit14(t_param *param, char **check_map)
{
	write(1, "Error\nIncorrect map\n", 20);
	ft_free_map(check_map, param);
	ft_free_param(param);
	exit(1);
}

void	ft_exit13(t_param *param, char **check_map)
{
	int	i;

	i = 0;
	write(1, "Error\nImpossible to read cub file or to set up the game", 55);
	write(1, ", program stopped\n", 18);
	while (check_map[i] != NULL)
	{
		free(check_map[i]);
		check_map[i] = NULL;
		i++;
	}
	free(check_map);
	ft_free_param(param);
	exit(1);
}

void	ft_exit12(t_param *param)
{
	write(1, "Error\nIncorrect map\n", 20);
	ft_free_param(param);
	exit(1);
}

void	ft_exit11(t_param *param, char **map, char *line)
{
	write(1, "Error\nImpossible to read cub file or to set up the game", 55);
	write(1, ", program stopped\n", 18);
	free(line);
	ft_free_map(map, param);
	ft_free_param(param);
	exit(1);
}
