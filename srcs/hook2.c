/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 12:21:08 by ade-garr          #+#    #+#             */
/*   Updated: 2020/07/29 13:10:50 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_exithook(t_param *param)
{
	(void)param;
	ft_free_param(param);
	exit(1);
	return (1);
}

int	ft_keypress(int key, t_param *param)
{
	if (key == 122)
		param->tab[0] = 1;
	if (key == 115)
		param->tab[1] = 1;
	if (key == 113)
		param->tab[2] = 1;
	if (key == 100)
		param->tab[3] = 1;
	if (key == 65363)
		param->tab[4] = 1;
	if (key == 65361)
		param->tab[5] = 1;
	if (key == 65505)
		param->tab[6] = 1;
	if (key == 65307)
		ft_exithook(param);
	return (1);
}

int	ft_keyrelease(int key, t_param *param)
{
	if (key == 122)
		param->tab[0] = 0;
	if (key == 115)
		param->tab[1] = 0;
	if (key == 113)
		param->tab[2] = 0;
	if (key == 100)
		param->tab[3] = 0;
	if (key == 65363)
		param->tab[4] = 0;
	if (key == 65361)
		param->tab[5] = 0;
	if (key == 65505)
		param->tab[6] = 0;
	return (1);
}
