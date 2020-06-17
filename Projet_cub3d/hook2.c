/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 12:21:08 by ade-garr          #+#    #+#             */
/*   Updated: 2020/06/17 16:09:21 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_exit2(t_param *param)
{
    (void)param;
	write(1, "Program successfully exited\n", 28);
	exit(1);
	return (1);
}

int	ft_keypress(int key, t_param *param)
{
	//LINUX
	/*if (key == 122)
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
		exit(1);*/

	//MACOS
	if (key == 13)
		param->tab[0] = 1;
	if (key == 1)
		param->tab[1] = 1;
	if (key == 0)
		param->tab[2] = 1;
	if (key == 2)
		param->tab[3] = 1;
	if (key == 124)
		param->tab[4] = 1;
	if (key == 123)
		param->tab[5] = 1;
	if (key == 257)
		param->tab[6] = 1;
	if (key == 53)
		ft_exit2(param);
	return (1);
}

int ft_keyrelease(int key, t_param *param)
{
	//LINUX
	/*if (key == 122)
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
		param->tab[6] = 0;*/
	
	//MACOS
	if (key == 13)
		param->tab[0] = 0;
	if (key == 1)
		param->tab[1] = 0;
	if (key == 0)
		param->tab[2] = 0;
	if (key == 2)
		param->tab[3] = 0;
	if (key == 124)
		param->tab[4] = 0;
	if (key == 123)
		param->tab[5] = 0;
	if (key == 257)
		param->tab[6] = 0;
	return (1);
}