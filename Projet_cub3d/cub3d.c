/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 18:44:08 by ade-garr          #+#    #+#             */
/*   Updated: 2020/06/24 20:06:12 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_spritecasting(t_param *param)
{
	int	i;
	double	spriteX;
	double	spriteY;
	double	invDet;
	double	transformX;
	double	transformY;
	int	sprite_screenX;
	int	sprite_height;
	int	sprite_width;
	int	draw_startY;
	int	draw_endY;
	int	draw_startX;
	int	draw_endX;
	int	x;
	int	y;
	int	texX;
	int	texY;
	char	*adr;
	int	d;

	i = 0;
	while (i < param->nb_sprite)
	{
		param->sprite_order[i] = i;
		param->sprite_distance[i] = (param->posX - param->tab_sprite[i].x) * (param->posX - param->tab_sprite[i].x) + (param->posY - param->tab_sprite[i].y) * (param->posY - param->tab_sprite[i].y);
		i++;
	}
	ft_sort_sprites(param);
	i = 0;
	while (i < param->nb_sprite)
	{
		spriteX = param->tab_sprite[param->sprite_order[i]].x - param->posX;
		spriteY = param->tab_sprite[param->sprite_order[i]].y - param->posY;
		invDet = 1 / (param->planeX * param->dirY - param->dirX * param->planeY);
		transformX = invDet * (param->dirY * spriteX - param->dirX * spriteY);
		transformY = invDet * (-param->planeY * spriteX + param->planeX * spriteY);
		sprite_screenX = ((param->winX / 2) * (1 + transformX / transformY));
		sprite_height = (fabs(param->winY / transformY));
		draw_startY = -sprite_height / 2 + param->winY / 2;
		if (draw_startY < 0)
			draw_startY = 0;
		draw_endY = sprite_height / 2 + param->winY / 2;
		if (draw_endY >= param->winY)
			draw_endY = param->winY;
		sprite_width = (fabs(param->winY / transformY));
		draw_startX = -sprite_width / 2 + sprite_screenX;
		if (draw_startX < 0)
			draw_startX = 0;
		draw_endX = sprite_width / 2 + sprite_screenX;
		if (draw_endX >= param->winX)
			draw_endX = param->winX;
		x = draw_startX;
		while (x < draw_endX)
		{
			texX = ((x - (-sprite_width / 2 + sprite_screenX)) * param->tex_sprite->width / sprite_width);
			if (transformY > 0 && x >= 0 && x < param->winX && transformY < param->tab_dist_wall[x])
			{
				y = draw_startY;
				while (y < draw_endY)
				{
					d = y - param->winY / 2 + sprite_height / 2;
					texY = ((d * param->tex_sprite->height) / sprite_height);
					if (param->tex_sprite->tab[texY * param->tex_sprite->width + texX] != 0xFFFFFF)
					{
						adr = param->imgadr + (y * param->imglenght + x * (param->imgbpp / 8));
						*(unsigned int *)adr = param->tex_sprite->tab[param->tex_sprite->width * texY + texX];
					}
					y++;
				}
			}
			x++;
		}
		i++;
	}
}

void	ft_raycasting(t_param *param)
{
	int		x;
	char	*adr;
	double	wallX;
	int		texX;
	double	step;
	double	texPos;
	int		texY;
	int		xfloorcell;

	x = 0;
	while (x < param->winX)
	{
		param->cameraX = 2 * x / param->winX - 1;
		param->rayDirX = param->dirX + param->planeX * param->cameraX;
		param->rayDirY = param->dirY + param->planeY * param->cameraX;
		param->mapX = param->posX;
		param->mapY = param->posY;
		param->deltaDistX = fabs(1 / param->rayDirX);
		param->deltaDistY = fabs(1 / param->rayDirY);
		param->hit = 0;
		if (param->rayDirX < 0)
		{
			param->stepX = -1;
			param->sideDistX = (param->posX - param->mapX) * param->deltaDistX;
		}
		else
		{
			param->stepX = 1;
			param->sideDistX = (param->mapX + 1.0 - param->posX) * param->deltaDistX;
		}
		if (param->rayDirY < 0)
		{
			param->stepY = -1;
			param->sideDistY = (param->posY - param->mapY) * param->deltaDistY;
		}
		else
		{
			param->stepY = 1;
			param->sideDistY = (param->mapY + 1.0 - param->posY) * param->deltaDistY;
		}
		while (param->hit == 0)
		{
			if (param->sideDistX < param->sideDistY)
			{
				param->sideDistX += param->deltaDistX;
				param->mapX += param->stepX;
				param->side = 0;
			}
			else
			{
				param->sideDistY += param->deltaDistY;
				param->mapY += param->stepY;
				param->side = 1;
			}
			if (param->worldMap[param->mapY][param->mapX] == '1')
				param->hit = 1;
		}
		if (param->side == 0)
			param->wallDist = (param->mapX - param->posX + (1 - param->stepX) / 2) / param->rayDirX;
		else
			param->wallDist = (param->mapY - param->posY + (1 - param->stepY) / 2) / param->rayDirY;
		param->lineHeight = param->winY / param->wallDist;
		param->lineHeight = (param->lineHeight < 0) ? INT_MAX : param->lineHeight;
		param->drawStart = -param->lineHeight / 2 + param->winY / 2;
		if (param->drawStart < 0)
			param->drawStart = 0;
		param->drawEnd = param->lineHeight / 2 + param->winY / 2;
		if (param->drawEnd >= param->winY)
			param->drawEnd = param->winY - 1;
		if (param->side == 0)
			wallX = param->posY + param->wallDist * param->rayDirY;
		else
			wallX = param->posX + param->wallDist * param->rayDirX;
		wallX -= floor(wallX);
		if (param->side == 1 && param->rayDirY < 0)
		{
			//ft_raycasting_north(param, raycast);
			texX = wallX * param->tex_N->width;
			if (param->side == 0 && param->rayDirX > 0)
				texX = param->tex_N->width - texX - 1;
			if (param->side == 1 && param->rayDirY < 0)
				texX = param->tex_N->width - texX - 1;
			step = 1.0 * param->tex_N->height / param->lineHeight;
			texPos = (param->drawStart - param->winY / 2 + param->lineHeight / 2) * step;
			xfloorcell = 0;
			while (xfloorcell < param->drawStart)
			{
				adr = param->imgadr + (xfloorcell * param->imglenght + x * (param->imgbpp / 8));
				*(unsigned int *)adr = param->cellcolor;
				xfloorcell++;
			}
			while (param->drawStart < param->drawEnd)
			{
				texY = texPos;
				if (texY >= param->tex_N->height)
					texY = param->tex_N->height - 1;
				texPos = texPos + step;
				adr = param->imgadr + (param->drawStart * param->imglenght + x * (param->imgbpp / 8));
				*(unsigned int *)adr = param->tex_N->tab[param->tex_N->width * texY + texX];
				param->drawStart++;
			}
			xfloorcell = param->drawEnd;
			while (xfloorcell < param->winY)
			{
				adr = param->imgadr + (xfloorcell * param->imglenght + x * (param->imgbpp / 8));
				*(unsigned int *)adr = param->floorcolor;
				xfloorcell++;
			}
			param->tab_dist_wall[x] = param->wallDist;
			x++;
		}
		if (param->side == 1 && param->rayDirY > 0)
		{
			//ft_raycasting_south(param, raycast);
			texX = wallX * param->tex_S->width;
			if (param->side == 0 && param->rayDirX > 0)
				texX = param->tex_S->width - texX - 1;
			if (param->side == 1 && param->rayDirY < 0)
				texX = param->tex_S->width - texX - 1;
			step = 1.0 * param->tex_S->height / param->lineHeight;
			texPos = (param->drawStart - param->winY / 2 + param->lineHeight / 2) * step;
			xfloorcell = 0;
			while (xfloorcell < param->drawStart)
			{
				adr = param->imgadr + (xfloorcell * param->imglenght + x * (param->imgbpp / 8));
				*(unsigned int *)adr = param->cellcolor;
				xfloorcell++;
			}
			while (param->drawStart < param->drawEnd)
			{
				texY = texPos;
				if (texY >= param->tex_S->height)
					texY = param->tex_S->height - 1;
				texPos = texPos + step;
				adr = param->imgadr + (param->drawStart * param->imglenght + x * (param->imgbpp / 8));
				*(unsigned int *)adr = param->tex_S->tab[param->tex_S->width * texY + texX];
				param->drawStart++;
			}
			xfloorcell = param->drawEnd;
			while (xfloorcell < param->winY)
			{
				adr = param->imgadr + (xfloorcell * param->imglenght + x * (param->imgbpp / 8));
				*(unsigned int *)adr = param->floorcolor;
				xfloorcell++;
			}
			param->tab_dist_wall[x] = param->wallDist;
			x++;
		}
		if (param->side == 0 && param->rayDirX < 0)
		{
			//ft_raycasting_west(param, raycast);
			texX = wallX * param->tex_W->width;
			if (param->side == 0 && param->rayDirX > 0)
				texX = param->tex_W->width - texX - 1;
			if (param->side == 1 && param->rayDirY < 0)
				texX = param->tex_W->width - texX - 1;
			step = 1.0 * param->tex_W->height / param->lineHeight;
			texPos = (param->drawStart - param->winY / 2 + param->lineHeight / 2) * step;
			xfloorcell = 0;
			while (xfloorcell < param->drawStart)
			{
				adr = param->imgadr + (xfloorcell * param->imglenght + x * (param->imgbpp / 8));
				*(unsigned int *)adr = param->cellcolor;
				xfloorcell++;
			}
			while (param->drawStart < param->drawEnd)
			{
				texY = texPos;
				if (texY >= param->tex_W->height)
					texY = param->tex_W->height - 1;
				texPos = texPos + step;
				adr = param->imgadr + (param->drawStart * param->imglenght + x * (param->imgbpp / 8));
				*(unsigned int *)adr = param->tex_W->tab[param->tex_W->width * texY + texX];
				param->drawStart++;
			}
			xfloorcell = param->drawEnd;
			while (xfloorcell < param->winY)
			{
				adr = param->imgadr + (xfloorcell * param->imglenght + x * (param->imgbpp / 8));
				*(unsigned int *)adr = param->floorcolor;
				xfloorcell++;
			}
			param->tab_dist_wall[x] = param->wallDist;
			x++;
		}
		if (param->side == 0 && param->rayDirX > 0)
		{
			//ft_raycasting_east(param, raycast);
			texX = wallX * param->tex_E->width;
			if (param->side == 0 && param->rayDirX > 0)
				texX = param->tex_E->width - texX - 1;
			if (param->side == 1 && param->rayDirY < 0)
				texX = param->tex_E->width - texX - 1;
			step = 1.0 * param->tex_E->height / param->lineHeight;
			texPos = (param->drawStart - param->winY / 2 + param->lineHeight / 2) * step;
			xfloorcell = 0;
			while (xfloorcell < param->drawStart)
			{
				adr = param->imgadr + (xfloorcell * param->imglenght + x * (param->imgbpp / 8));
				*(unsigned int *)adr = param->cellcolor;
				xfloorcell++;
			}
			while (param->drawStart < param->drawEnd)
			{
				texY = texPos;
				if (texY >= param->tex_E->height)
					texY = param->tex_E->height - 1;
				texPos = texPos + step;
				adr = param->imgadr + (param->drawStart * param->imglenght + x * (param->imgbpp / 8));
				*(unsigned int *)adr = param->tex_E->tab[param->tex_E->width * texY + texX];
				param->drawStart++;
			}
			xfloorcell = param->drawEnd;
			while (xfloorcell < param->winY)
			{
				adr = param->imgadr + (xfloorcell * param->imglenght + x * (param->imgbpp / 8));
				*(unsigned int *)adr = param->floorcolor;
				xfloorcell++;
			}
			param->tab_dist_wall[x] = param->wallDist;
			x++;
		}
	}
	ft_spritecasting(param);
}

void	ft_set_tabs_tex(t_param *param)
{
	if ((param->tab_dist_wall = malloc(sizeof(double) * param->winX)) == NULL)
		ft_exit(4);
	if ((param->tex_N = malloc(sizeof(t_tex) * 1)) == NULL)
		ft_exit(4);
	if ((param->tex_S = malloc(sizeof(t_tex) * 1)) == NULL)
		ft_exit(4);
	if ((param->tex_W = malloc(sizeof(t_tex) * 1)) == NULL)
		ft_exit(4);
	if ((param->tex_E = malloc(sizeof(t_tex) * 1)) == NULL)
		ft_exit(4);
	if ((param->tex_sprite = malloc(sizeof(t_tex) * 1)) == NULL)
		ft_exit(4);
	ft_set_tex_n(param);
	ft_set_tex_s(param);
	ft_set_tex_w(param);
	ft_set_tex_e(param);
	ft_set_tex_sprite(param);
	ft_set_local_endian(param);
}

int main(int argc, char **argv)
{
	t_param	*param;

	if (argc == 2 || (argc == 3 && ft_check_arg(argv[2]) == 1))
	{
		param = malloc(sizeof(t_param) * 1);
		if (param == NULL)
			ft_exit1();
		param->mlx = mlx_init();
		if (param->mlx == NULL)
			ft_exit2(param);
		ft_parsing(param, argv[1]);
		ft_set_tabs_tex(param);
		ft_set_sprite(param);
		param->img = mlx_new_image(param->mlx, param->winX, param->winY);
		if (param->img == NULL)
			ft_exit(4);
		param->imgadr = mlx_get_data_addr(param->img, &param->imgbpp, &param->imglenght, &param->endian);
		if (argc == 2)
		{
			param->win = mlx_new_window(param->mlx, param->winX, param->winY, "Cub3d");
			if (param->win == NULL)
				ft_exit(4);
			mlx_hook(param->win, 2, 1L<<0, ft_keypress, param);
			mlx_hook(param->win, 3, 1L<<1, ft_keyrelease, param);
			mlx_hook(param->win, 17, 1L<<17, ft_exithook, param);
			mlx_loop_hook(param->mlx, ft_loop, param);
			mlx_loop(param->mlx);
		}
		else
		{
			ft_raycasting(param);
			ft_create_img(param);
		}
	}
	else
		ft_exit(2);
	return (1);
}
