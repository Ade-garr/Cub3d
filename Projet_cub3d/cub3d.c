/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 18:44:08 by ade-garr          #+#    #+#             */
/*   Updated: 2020/06/08 13:29:43 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define screenWidth 640
#define screenHeight 480
#define mapWidth 24
#define mapHeight 24

#include <mlx.h>
#include <math.h>
#include <unistd.h> // A SUPPRIMER -> inclu dans libft
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef struct		s_img
{
    int             file_size;
    short           reserved1;
    short           reserved2;
    unsigned int    offset_bits;
    unsigned int    size_header;
    unsigned int    width;
    unsigned int    height;
    short int       planes;
    short int       bbp;
    unsigned int    compression;
    unsigned int    image_size;
    unsigned int    ppm_x;
    unsigned int    ppm_y;
    unsigned int    clr_total;
    unsigned int    clr_important;
}					t_img;

typedef	struct		s_sprite
{
	double	x;
	double	y;
}			t_sprite;

typedef struct		s_tex1
{
	int				width;
	int				height;
	unsigned int	*tab;
}			t_tex1;

typedef struct		s_tex_sprite
{
	int				width;
	int				height;
	unsigned int	*tab;
}			t_tex_sprite;

typedef struct	s_param
{
	void		*mlx;
	void		*win;
	double		posX;
	double		posY;
	double		dirX;
	double		dirY;
	double		planeX;
	double		planeY;
	double		cameraX;
	double		rayDirX;
	double		rayDirY;
	int			mapX;
	int			mapY;
	double		winX;
	double		winY;
	double		sideDistX;
	double		sideDistY;
	double		deltaDistX;
	double		deltaDistY;
	double		wallDist;
	int			stepX;
	int			stepY;
	int			hit;
	int			side;
	int			lineHeight;
	int			drawStart;
	int			drawEnd;
	int			color; // A VOIR SI NECESSAIRE A LA FIN
	void		*img; // POUR OPTI
	char		*imgadr; // POUR OPTI
	int			imgbpp;
	int			imglenght;
	int			endian;
	int			tab[7];
	char		*fn_tex1;
	char		*fn_tex_sprite;
	t_tex1		*tex1;
	t_tex_sprite	*tex_sprite;
	t_sprite	*tab_sprite;
	int		nb_sprite;
	double		*tab_dist_wall;
	int		*sprite_order;
	double		*sprite_distance;
	
}				t_param;

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

/// A MODIFIER AVEC PARSEUR DU .CUB
void	find_pos(t_param *param)
{
	param->posX = 15;
	param->posY = 12;
	param->dirX = -1;
	param->dirY = 0;
	param->planeX = 0;
	param->planeY = 0.66;
	param->winX = 800;
	param->winY = 600;
}
/// A MODIFIER AVEC PARSEUR DU .CUB

void	ft_sort_sprites(t_param *param)
{
	int		i;
	double	tmp_dist;
	int		tmp_order;

	i = 0;
	if (param->nb_sprite >= 2)
	{
		while (i < param->nb_sprite - 1)
		{
			if (param->sprite_distance[i] < param->sprite_distance[i + 1])
			{
				tmp_dist = param->sprite_distance[i];
				param->sprite_distance[i] = param->sprite_distance[i + 1];
				param->sprite_distance[i + 1] = tmp_dist;
				tmp_order = param->sprite_order[i];
				param->sprite_order[i] = param->sprite_order[i + 1];
				param->sprite_order[i + 1] = tmp_order;
				i = -1;
			}
			i++;
		}
	}
}

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
		param->sprite_distance[i] = (param->posX - param->tab_sprite[i].x) *
		(param->posX - param->tab_sprite[i].x) + (param->posY - param->tab_sprite[i].y) *
		(param->posY - param->tab_sprite[i].y);
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
		if (draw_endX >= param-> winX)
			draw_endX = param->winX;
		x = draw_startX;
		while (x < draw_endX)
		{
			texX = ((x - (-sprite_width / 2 + sprite_screenX)) *
			param->tex_sprite->width / sprite_width);
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
						*(unsigned int *)adr =
						param->tex_sprite->tab[param->tex_sprite->width * texY + texX];
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
			if (worldMap[param->mapX][param->mapY] > 0)
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
		texX = wallX * param->tex1->width;
		if (param->side == 0 && param->rayDirX > 0)
			texX = param->tex1->width - texX - 1;
		if (param->side == 1 && param->rayDirY < 0)
			texX = param->tex1->width - texX - 1;
		step = 1.0 * param->tex1->height / param->lineHeight;
		texPos = (param->drawStart - param->winY / 2 + param->lineHeight / 2) * step;
		xfloorcell = 0;
		while (xfloorcell < param->drawStart)
		{
			adr = param->imgadr + (xfloorcell * param->imglenght + x * (param->imgbpp / 8));
			*(unsigned int *)adr = 0x5AFDFF;
			xfloorcell++;
		}
		while (param->drawStart < param->drawEnd)
		{
			texY = texPos;
			if (texY >= param->tex1->height)
				texY = param->tex1->height - 1;
			texPos = texPos + step;
			adr = param->imgadr + (param->drawStart * param->imglenght + x * (param->imgbpp / 8));
			*(unsigned int *)adr = param->tex1->tab[param->tex1->width * texY + texX];
			param->drawStart++;
		}
		xfloorcell = param->drawEnd;
		while (xfloorcell < param->winY)
		{
			adr = param->imgadr + (xfloorcell * param->imglenght + x * (param->imgbpp / 8));
			*(unsigned int *)adr = 0x01D364;
			xfloorcell++;
		}
		param->tab_dist_wall[x] = param->wallDist;
		x++;
	}
	ft_spritecasting(param);
}

double	ft_max(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}

double	ft_min(double a, double b)
{
	if (a < b)
		return (a);
	return (b);
}

int	ft_checkcollision(t_param *param, double Speed, double rectX, double rectY)
{
	double	deltaX;
	double	deltaY;
	double	radius;
	
	radius = 0.1;
	deltaX = param->posX + param->dirX * Speed -
	ft_max(rectX, ft_min(param->posX + param->dirX * Speed, rectX + 1));
	deltaY = param->posY + param->dirY * Speed -
	ft_max(rectY, ft_min(param->posY + param->dirY * Speed, rectY + 1));
	if (deltaX * deltaX + deltaY * deltaY < radius * radius)
		return (1);
	return (0);
}

int	ft_bodycollision(t_param *param, double Speed)
{	
	double	rectX;
	double	rectY;

	rectX = floor(param->posX) - 1;
	rectY = floor(param->posY) - 1;
	if (worldMap[(int)rectX][(int)rectY] != 0)
	{
		if (ft_checkcollision(param, Speed, rectX, rectY) == 1)
			return (1);
	}
	rectX = floor(param->posX);
	if (worldMap[(int)rectX][(int)rectY] != 0)
	{
		if (ft_checkcollision(param, Speed, rectX, rectY) == 1)
			return (1);
	}
	rectX = floor(param->posX) + 1;
	if (worldMap[(int)rectX][(int)rectY] != 0)
	{
		if (ft_checkcollision(param, Speed, rectX, rectY) == 1)
			return (1);
	}
	rectX = floor(param->posX) - 1;
	rectY = floor(param->posY);
	if (worldMap[(int)rectX][(int)rectY] != 0)
	{
		if (ft_checkcollision(param, Speed, rectX, rectY) == 1)
			return (1);
	}
	rectX = floor(param->posX) + 1;
	if (worldMap[(int)rectX][(int)rectY] != 0)
	{
		if (ft_checkcollision(param, Speed, rectX, rectY) == 1)
			return (1);
	}
	rectX = floor(param->posX) - 1;
	rectY = floor(param->posY) + 1;
	if (worldMap[(int)rectX][(int)rectY] != 0)
	{
		if (ft_checkcollision(param, Speed, rectX, rectY) == 1)
			return (1);
	}
	rectX = floor(param->posX);
	if (worldMap[(int)rectX][(int)rectY] != 0)
	{
		if (ft_checkcollision(param, Speed, rectX, rectY) == 1)
			return (1);
	}
	rectX = floor(param->posX) + 1;
	if (worldMap[(int)rectX][(int)rectY] != 0)
	{
		if (ft_checkcollision(param, Speed, rectX, rectY) == 1)
			return (1);
	}
	return (0);
}

int	ft_loop(t_param *param)
{
	double	oldDirX;
	double	oldDirY;
	double	oldPlaneX;
	double	Speed;
	double	rotSpeed;

	Speed = 0.025;
	rotSpeed = 0.025;
	if (param->tab[6] == 1)
		Speed = 0.05;
	if (param->tab[0] == 1)
	{
		if (worldMap[(int)(param->posX + param->dirX * Speed)]
		[(int)(param->posY + param->dirY * Speed)] == 0 && ft_bodycollision(param, Speed) == 0)
		{	
			param->posX += param->dirX * Speed;
			param->posY += param->dirY * Speed;
		}
	}
	if (param->tab[1] == 1)
	{
		oldDirX = param->dirX;
		oldDirY = param->dirY;
		param->dirX = - param->dirX;
		param->dirY = - param->dirY;
		if (worldMap[(int)(param->posX + param->dirX * Speed)]
		[(int)(param->posY + param->dirY * Speed)] == 0 && ft_bodycollision(param, Speed) == 0)
		{
			param->posX += param->dirX * Speed;
			param->posY += param->dirY * Speed;
		}
		param->dirX = oldDirX;
		param->dirY = oldDirY;
	}
	if (param->tab[2] == 1)
	{
		oldDirX = param->dirX;
		oldDirY = param->dirY;
		param->dirX = param->dirX * cos(M_PI/2) - param->dirY * sin(M_PI/2);
		param->dirY = oldDirX * sin(M_PI/2) + param->dirY * cos(M_PI/2);
		if(worldMap[(int)(param->posX + param->dirX * Speed)]
		[(int)(param->posY + param->dirY * Speed)] == 0 && ft_bodycollision(param, Speed) == 0) 
		{
			param->posX += param->dirX * Speed;
			param->posY += param->dirY * Speed;
		}
		param->dirX = oldDirX;
		param->dirY = oldDirY;
	}
	if (param->tab[3] == 1)
	{
		oldDirX = param->dirX;
		oldDirY = param->dirY;
		param->dirX = param->dirX * cos(-M_PI/2) - param->dirY * sin(-M_PI/2);
		param->dirY = oldDirX * sin(-M_PI/2) + param->dirY * cos(-M_PI/2);
		if(worldMap[(int)(param->posX + param->dirX * Speed)]
		[(int)(param->posY + param->dirY * Speed)] == 0 && ft_bodycollision(param, Speed) == 0) 
		{
			param->posX += param->dirX * Speed;
			param->posY += param->dirY * Speed;
		}
		param->dirX = oldDirX;
		param->dirY = oldDirY;
	}
	if (param->tab[4] == 1)
	{
		oldDirX = param->dirX;
		param->dirX = param->dirX * cos(-rotSpeed) - param->dirY * sin(-rotSpeed);
		param->dirY = oldDirX * sin(-rotSpeed) + param->dirY * cos(-rotSpeed);
		oldPlaneX = param->planeX;
		param->planeX = param->planeX * cos(-rotSpeed) - param->planeY * sin(-rotSpeed);
		param->planeY = oldPlaneX * sin(-rotSpeed) + param->planeY * cos(-rotSpeed);
	}
	if (param->tab[5] == 1)
	{
		oldDirX = param->dirX;
		param->dirX = param->dirX * cos(rotSpeed) - param->dirY * sin(rotSpeed);
		param->dirY = oldDirX * sin(rotSpeed) + param->dirY * cos(rotSpeed);
		oldPlaneX = param->planeX;
		param->planeX = param->planeX * cos(rotSpeed) - param->planeY * sin(rotSpeed);
		param->planeY = oldPlaneX * sin(rotSpeed) + param->planeY * cos(rotSpeed);
	}
	ft_raycasting(param);
	mlx_put_image_to_window(param->mlx, param->win, param->img, 0, 0);
	return (0);
}

int	ft_exit(t_param *param)
{
	// FONCTION POUR FREE TOUS LES MALLOC AINSI QUE L IMAGE
	(void)param;
	printf("Program successfully exited");
	exit(1);
}

int	ft_keypress(int key, t_param *param)
{
	if /*(key == 13)*/ (key == 122)
		param->tab[0] = 1;
	if /*(key == 1)*/ (key == 115)
		param->tab[1] = 1;
	if /*(key == 0)*/ (key == 113)
		param->tab[2] = 1;
	if /*(key == 2)*/ (key == 100)
		param->tab[3] = 1;
	if /*(key == 124)*/ (key == 65363)
		param->tab[4] = 1;
	if /*(key == 123)*/ (key == 65361)
		param->tab[5] = 1;
	if /*(key == 257)*/ (key == 65505)
		param->tab[6] = 1;
	if /*(key == 257)*/ (key == 65307)
		ft_exit(param);
	return (0);
}

void	*ft_set_tex_sprite(t_param *param)
{
	char	*adr;
	void	*ret;
	int		x;
	int		y;
	int		bpp;
	int		length;
	int		endian;

	y = 0;
	param->tex_sprite = malloc(sizeof(t_tex_sprite) * 1);
	param->fn_tex_sprite = "./textures/sprite_chaton.xpm"; // A MODIFIER AVEC LE PARSING
	ret = mlx_xpm_file_to_image(param->mlx, param->fn_tex_sprite, &param->tex_sprite->width,
	&param->tex_sprite->height);
	if (ret == NULL)
		return (ret);
	adr = mlx_get_data_addr(ret, &bpp, &length, &endian);
	param->tex_sprite->tab = malloc(sizeof(unsigned int) *
	(param->tex_sprite->height * param->tex_sprite->width));
	if (param->tex_sprite->tab == NULL)
		return (NULL);
	while (y < param->tex_sprite->height)
	{
		x = 0;
		while (x < param->tex_sprite->width)
		{
			param->tex_sprite->tab[y * param->tex_sprite->width + x] =
			*(unsigned int *)(adr + y * length + x * bpp / 8);
			x++;
		}
		y++;
	}
	mlx_destroy_image(param->mlx, ret);
	return (ret);
}

void	*ft_set_tex(t_param *param)
{
	char	*adr;
	void	*ret;
	int		x;
	int		y;
	int		bpp;
	int		length;
	int		endian;

	y = 0;
	param->tex1 = malloc(sizeof(t_tex1) * 1);
	param->fn_tex1 = "./textures/chaton2.xpm"; // A MODIFIER AVEC LE PARSING
	ret = mlx_xpm_file_to_image(param->mlx, param->fn_tex1, &param->tex1->width, &param->tex1->height);
	if (ret == NULL)
		return (ret);
	adr = mlx_get_data_addr(ret, &bpp, &length, &endian);
	param->tex1->tab = malloc(sizeof(unsigned int) * (param->tex1->height * param->tex1->width));
	if (param->tex1->tab == NULL)
	{
		ret = NULL;
		return (ret);
	}
	while (y < param->tex1->height)
	{
		x = 0;
		while (x < param->tex1->width)
		{
			param->tex1->tab[y * param->tex1->width + x] = *(unsigned int *)(adr + y * length + x * bpp / 8);
			x++;
		}
		y++;
	}
	mlx_destroy_image(param->mlx, ret);
	return (ret);
}

int ft_keyrelease(int key, t_param *param)
{
	if /*(key == 13)*/ (key == 122)
		param->tab[0] = 0;
	if /*(key == 1)*/ (key == 115)
		param->tab[1] = 0;
	if /*(key == 0)*/ (key == 113)
		param->tab[2] = 0;
	if /*(key == 2)*/ (key == 100)
		param->tab[3] = 0;
	if /*(key == 124)*/ (key == 65363)
		param->tab[4] = 0;
	if /*(key == 123)*/ (key == 65361)
		param->tab[5] = 0;
	if /*(key == 257)*/ (key == 65505)
		param->tab[6] = 0;
	return (0);
}

void	*ft_set_sprite(t_param *param)
{
	void	*ret;

	ret = ft_set_tex_sprite(param);
	if (ret == NULL)
		return (ret);
	param->nb_sprite = 3; // A MODIFIER AVEC PARSING
	param->tab_sprite = malloc(sizeof(t_sprite) * param->nb_sprite);
	if (param->tab_sprite == NULL)
		return (NULL);
	param->tab_sprite[0].x = 6; // A MODIFIER AVEC PARSING
	param->tab_sprite[0].y = 8; // A MODIFIER AVEC PARSING
	param->tab_sprite[1].x = 6; // A MODIFIER AVEC PARSING
	param->tab_sprite[1].y = 9; // A MODIFIER AVEC PARSING
	param->tab_sprite[2].x = 7; // A MODIFIER AVEC PARSING
	param->tab_sprite[2].y = 8.5; // A MODIFIER AVEC PARSING
	param->sprite_order = malloc(sizeof(int) * param->nb_sprite);
	if (param->sprite_order == NULL)
		return (NULL);
	param->sprite_distance = malloc(sizeof(double) * param->nb_sprite);
	if (param->sprite_order == NULL)
		return (NULL);
	return (ret);
}

void	ft_define_ptr(t_param *param, t_img *ptr)
{
    ptr->file_size = param->winX * param->winY * 4 + 54;
    ptr->reserved1 = 0;
    ptr->reserved2 = 0;
    ptr->offset_bits = 54;
    ptr->size_header = 40;
    ptr->width = param->winX;
    ptr->height = param->winY;
    ptr->planes = 1;
    ptr->bbp = 32;
    ptr->compression = 0;
    ptr->image_size = 0;
    ptr->ppm_x = 0;
    ptr->ppm_y = 0;
    ptr->clr_total = 0;
    ptr->clr_important = 0;
}

int	ft_tab_in_img(t_param *param, int fd)
{
	int	i;
	int	x;
	int	y;
	unsigned int	*tab;

	tab = malloc(sizeof(int) * (param->winY * param->winX));
	if (tab == NULL)
		return (-1);
	y = param->winY - 1;
	i = 0;
	while (i < (param->winX * param->winY))
	{
		x = 0;
		while (x++ < param->winX)
			tab[i++] = *(unsigned int *)(param->imgadr + y * param->imglenght + x * param->imgbpp / 8);
		y--;
	}
	if (write(fd, tab, param->winX * param->winY * 4) == -1)
	{
		free(tab);
		return (-1);
	}
	free(tab);
	return (1);
}

int	ft_create_img(t_param *param)
{
	int	fd;
	int	ret;
	t_img	*ptr;

	ptr = malloc(sizeof(t_img) * 1);
	if (ptr == NULL)
		return (-1);
	ft_define_ptr(param, ptr);
	fd = open("img_cub3d.bmp", O_CREAT | O_RDWR | O_APPEND, S_IRWXU);
	if (fd == -1)
	{
		free(ptr);
		return (-1);
	}
	if (write(fd, "BM", 2) == -1 || write(fd, ptr, 52) == -1)
	{
		close(fd);
		free(ptr);
		return (-1);
	}
	ret = ft_tab_in_img(param, fd);
	close(fd);
	free(ptr);
	return (ret);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return(0);
	while (str[i] != '\0')
		i++;
	return(i);
}

int	ft_check_arg(char *str)
{
	char cmp[] = "--save";
	int	i;

	i = 0;
	if (ft_strlen(str) != 6)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] != cmp[i])
			return (0);
		i++;
	}
	return (1);
}

int	ft_return(int nb)
{
	if (nb == 1)
		write(1, "Error : failed to create an image\n", 34);
	if (nb == 2)
		write(1, "Error : invalid arguments\n", 26);
	if (nb == 3)
		write(1, "Error : invalid .cub filename or couldn't open the file\n", 56);
	if (nb == 4)
		write(1, "Error : impossible to read .cub file, program stopped\n", 54);
	if (nb == 5)
		write(1, "Error : incorrect .cub file\n", 28);
	if (nb == 6)
		write(1, "Error : information unknown or in double in .cub file\n", 54);
	if (nb == 7)
		write(1, "Error : resolution information incorrect\n", 41);
	if (nb == 8)
		write(1, "Error : north texture information incorrect\n", 44);
	if (nb == 9)
		write(1, "Error : south texture information incorrect\n", 44);
	if (nb == 10)
		write(1, "Error : west texture information incorrect\n", 43);
	if (nb == 11)
		write(1, "Error : east texture information incorrect\n", 43);
	if (nb == 12)
		write(1, "Error : sprite texture information incorrect\n", 45);
	if (nb == 13)
		write(1, "Error : floor color information incorrect\n", 42);
	if (nb == 14)
		write(1, "Error : cell color information incorrect\n", 41);
	return (-1);
}

int main(int argc, char **argv)
{
	t_param	*param;
	void 	*ret;
	int		ret2;

	if (argc == 1 || (argc == 2 && ft_check_arg(argv[1]) == 1))
	{
		param = malloc(sizeof(t_param) * 1);
		/*ret2 = ft_parsing(param, argv[1]);
		if (ret2 == -1)
		{
			free(param);
			return (-1);
		}*/
		find_pos(param);
		param->mlx = mlx_init();
		param->tab_dist_wall = malloc(sizeof(double) * param->winX);
		ret = ft_set_tex(param);
		if (ret == NULL)
			return(write(1, "An error has occurred\n", 22));
		ret = ft_set_sprite(param);
		if (ret == NULL)
			return(write(1, "An error has occurred\n", 22));
		param->img = mlx_new_image(param->mlx, param->winX, param->winY);
		param->imgadr = mlx_get_data_addr(param->img, &param->imgbpp, &param->imglenght, &param->endian);
		if (argc == 1)
		{
			param->win = mlx_new_window(param->mlx, param->winX, param->winY, "Nico nico nicoco"); // CHANGER LES X/Y ET NOM
			mlx_hook(param->win, 2, 1L<<0, ft_keypress, param);
			mlx_hook(param->win, 3, 1L<<1, ft_keyrelease, param);
			mlx_hook(param->win, 17, 1L<<19, ft_exit, param); // EVENT MASK A VOIR
			mlx_loop_hook(param->mlx, ft_loop, param);
			mlx_loop(param->mlx);
		}
		else
		{
			ft_raycasting(param);
			ret2 = ft_create_img(param);
			if (ret2 == -1)
				return(ft_return(1));
		}
	}
	else
		return(ft_return(2)); // A MODIFIER
	return (1);
}
