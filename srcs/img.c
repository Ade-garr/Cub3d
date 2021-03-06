/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 12:40:47 by ade-garr          #+#    #+#             */
/*   Updated: 2020/07/13 17:45:05 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_define_ptr(t_param *param, t_img *ptr)
{
	ptr->file_size = param->winx * param->winy * 4 + 54;
	ptr->reserved1 = 0;
	ptr->reserved2 = 0;
	ptr->offset_bits = 54;
	ptr->size_header = 40;
	ptr->width = param->winx;
	ptr->height = param->winy;
	ptr->planes = 1;
	ptr->bbp = 32;
	ptr->compression = 0;
	ptr->image_size = 0;
	ptr->ppm_x = 0;
	ptr->ppm_y = 0;
	ptr->clr_total = 0;
	ptr->clr_important = 0;
}

void	ft_tab_in_img(t_param *param, int fd)
{
	int				i;
	int				x;
	int				y;
	unsigned int	*tab;

	tab = malloc(sizeof(int) * (param->winy * param->winx));
	if (tab == NULL)
		ft_exit15(param);
	y = param->winy - 1;
	i = 0;
	while (i < (param->winx * param->winy))
	{
		x = -1;
		while (++x < param->winx)
			tab[i++] = *(unsigned int *)(param->imgadr + y * param->imglenght +
			x * param->imgbpp / 8);
		y--;
	}
	if (write(fd, tab, param->winx * param->winy * 4) == -1)
	{
		free(tab);
		ft_exit15(param);
	}
	free(tab);
}

void	ft_create_img(t_param *param)
{
	int		fd;
	t_img	ptr;

	ft_define_ptr(param, &ptr);
	fd = open("cub3d_img.bmp", O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
	if (fd == -1)
		ft_exit15(param);
	if (write(fd, "BM", 2) == -1 || write(fd, &ptr, 52) == -1)
		ft_exit15(param);
	ft_tab_in_img(param, fd);
	close(fd);
	ft_exit16(param);
}
