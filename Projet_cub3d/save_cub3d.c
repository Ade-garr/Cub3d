/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 18:44:08 by ade-garr          #+#    #+#             */
/*   Updated: 2020/02/28 11:00:54 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define screenWidth 640
#define screenHeight 480
#define mapWidth 24
#define mapHeight 24

#include "mlx.h"
#include <math.h>

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
	param->winX = 400;
	param->winY = 300;
}
/// A MODIFIER AVEC PARSEUR DU .CUB

void	ft_raycasting(t_param *param)
{
	int	x;

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
		param->lineHeight = param->winY / param->wallDist; // CHANGER LE winY pour voir l impact
		param->drawStart = -param->lineHeight / 2 + param->winY / 2;
		if (param->drawStart < 0)
			param->drawStart = 0;
		param->drawEnd = param->lineHeight / 2 + param->winY / 2;
		if (param->drawEnd >= param->winY)
			param->drawEnd = param->winY - 1;
		if (worldMap[param->mapX][param->mapY] == 1)
			param->color = 0xD3013A;
		else if (worldMap[param->mapX][param->mapY] == 2)
			param->color = 0x01D364;
		else if (worldMap[param->mapX][param->mapY] == 3)
			param->color = 0x17009B;
		else if (worldMap[param->mapX][param->mapY] == 4)
			param->color = 0xFFFFFF;
		else if (worldMap[param->mapX][param->mapY] == 5)
			param->color = 0xFFEF4D;
		if (param->side == 1)
			param->color = param->color / 2;
		while (param->drawStart <= param->drawEnd)
		{
			mlx_pixel_put(param->mlx, param->win, x, param->drawStart, param->color);
			param->drawStart++;
		}
		x++;
	}
}

int	ft_keypress(int key, t_param *param) // A MODIFIER POUR LE MOVESPEED + MURS
{
	double	oldDirX;
	double	oldDirY;
	double	oldPlaneX;

	if (key == 13)
	{
		if(worldMap[(int)(param->posX + param->dirX * 0.2)][(int)(param->posY)] == 0) 
			param->posX += param->dirX * 0.2;
		if(worldMap[(int)(param->posX)][(int)(param->posY + param->dirY * 0.2)] == 0)
			param->posY += param->dirY * 0.2;
		mlx_clear_window(param->mlx, param->win);
		ft_raycasting(param);
	}
	if (key == 1)
	{
		if(worldMap[(int)(param->posX - param->dirX * 0.2)][(int)(param->posY)] == 0) 
			param->posX -= param->dirX * 0.2;
		if(worldMap[(int)(param->posX)][(int)(param->posY - param->dirY * 0.2)] == 0)
			param->posY -= param->dirY * 0.2;
		mlx_clear_window(param->mlx, param->win);
		ft_raycasting(param);
	}
	if (key == 0)
	{
		oldDirX = param->dirX;
		oldDirY = param->dirY;
		param->dirX = param->dirX * cos(M_PI/2) - param->dirY * sin(M_PI/2);
		param->dirY = oldDirX * sin(M_PI/2) + param->dirY * cos(M_PI/2);
		if(worldMap[(int)(param->posX + param->dirX * 0.2)][(int)(param->posY)] == 0) 
			param->posX += param->dirX * 0.2;
		if(worldMap[(int)(param->posX)][(int)(param->posY + param->dirY * 0.2)] == 0)
			param->posY += param->dirY * 0.2;
		param->dirX = oldDirX;
		param->dirY = oldDirY;
		mlx_clear_window(param->mlx, param->win);
		ft_raycasting(param);
	}
	if (key == 2)
	{
		oldDirX = param->dirX;
		oldDirY = param->dirY;
		param->dirX = param->dirX * cos(-M_PI/2) - param->dirY * sin(-M_PI/2);
		param->dirY = oldDirX * sin(-M_PI/2) + param->dirY * cos(-M_PI/2);
		if(worldMap[(int)(param->posX + param->dirX * 0.2)][(int)(param->posY)] == 0) 
			param->posX += param->dirX * 0.2;
		if(worldMap[(int)(param->posX)][(int)(param->posY + param->dirY * 0.2)] == 0)
			param->posY += param->dirY * 0.2;
		param->dirX = oldDirX;
		param->dirY = oldDirY;
		mlx_clear_window(param->mlx, param->win);
		ft_raycasting(param);
	}
	if (key == 124)
	{
		oldDirX = param->dirX;
		param->dirX = param->dirX * cos(-0.2) - param->dirY * sin(-0.2);
		param->dirY = oldDirX * sin(-0.2) + param->dirY * cos(-0.2);
		oldPlaneX = param->planeX;
		param->planeX = param->planeX * cos(-0.2) - param->planeY * sin(-0.2);
		param->planeY = oldPlaneX * sin(-0.2) + param->planeY * cos(-0.2);
		mlx_clear_window(param->mlx, param->win);
		ft_raycasting(param);
	}
	if (key == 123)
	{
		oldDirX = param->dirX;
		param->dirX = param->dirX * cos(0.2) - param->dirY * sin(0.2);
		param->dirY = oldDirX * sin(0.2) + param->dirY * cos(0.2);
		oldPlaneX = param->planeX;
		param->planeX = param->planeX * cos(0.2) - param->planeY * sin(0.2);
		param->planeY = oldPlaneX * sin(0.2) + param->planeY * cos(0.2);
		mlx_clear_window(param->mlx, param->win);
		ft_raycasting(param);
}
	return (0);
}

int main()
{
	t_param	param;

	find_pos(&param);
	param.mlx = mlx_init();
	param.win = mlx_new_window(param.mlx, param.winX, param.winY, "Nico nico nicoco"); // CHANGER LES X/Y ET NOM
	ft_raycasting(&param);
	mlx_hook(param.win, 2, 1L<<0, ft_keypress, &param);
	mlx_loop(param.mlx);
	return (0);
}
