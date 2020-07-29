/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 14:05:06 by ade-garr          #+#    #+#             */
/*   Updated: 2020/06/22 16:53:14 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mlx.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

int	main()
{
	int	fd;

	fd = open("test", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	write(fd, "12", 2);
	close(fd);
	fd = open("test", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	write(fd, "2", 1);
	close(fd);
	return (0);	
}
