/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 13:56:30 by ade-garr          #+#    #+#             */
/*   Updated: 2020/06/12 15:51:39 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_exit(int nb)
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
	if (nb == 15)
		write(1, "Error : resolution <= 0\n", 24);
	if (nb == 16)
		write(1, "Error : incorrect map\n", 22);
	exit(1);
}

int main(int ac, char **argv)
{
    t_param	*param;
    int i;
    
    (void)ac;
    i = 0;
    param = malloc(sizeof(t_param) * 1);
	param->mlx = mlx_init();
    ft_parsing(param, argv[1]);
    printf("R = %f %f\n", param->winX, param->winY);
    printf("%s\n", param->fn_texN);
    printf("%s\n", param->fn_texS);
    printf("%s\n", param->fn_texE);
    printf("%s\n", param->fn_texW);
    printf("%s\n", param->fn_tex_sprite);
    printf("color floor = %d,%d,%d\n", param->floorR, param->floorG, param->floorB);
    printf("color cell = %d,%d,%d\n", param->cellR, param->cellG, param->cellB);
    while (i < param->mapHeight)
    {
        printf("%s\n", param->worldMap[i]);
        i++;
    }
    return (1);
}

