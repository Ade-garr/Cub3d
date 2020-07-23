/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 18:46:44 by ade-garr          #+#    #+#             */
/*   Updated: 2020/07/14 12:46:49 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_exit5(t_param *param, char *line)
{
	write(1, "Error : incorrect .cub file\n", 28);
	free(line);
	ft_free_param(param);
	exit(1);
}

void	ft_exit4(t_param *param, char *line)
{
	write(1, "Error : incorrect map\n", 22);
	free(line);
	ft_free_param(param);
	exit(1);
}

void	ft_exit3(t_param *param)
{
	write(1, "Error : invalid .cub filename or couldn't open the file\n", 56);
	ft_free_param(param);
	exit(1);
}

void	ft_exit2(t_param *param)
{
	write(1, "Error : impossible to read cub file or to set up the game", 57);
	write(1, ", program stopped\n", 18);
	ft_free_param(param);
	exit(1);
}

void	ft_exit1(void)
{
	write(1, "Error : impossible to read cub file or to set up the game", 57);
	write(1, ", program stopped\n", 18);
	exit(1);
}
