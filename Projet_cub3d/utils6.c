/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 19:43:41 by ade-garr          #+#    #+#             */
/*   Updated: 2020/07/12 20:02:18 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_check_filename(char *str)
{
    int i;

    i = 0;
    if (str == NULL)
        return (0);
    while (str[i] != '\0')
        i++;
    if (ft_strlen(str) >= 4 && str[i - 1] == 'b' && str[i - 2] == 'u' && str[i - 3] == 'c' && str[i - 4] == '.')
        return (1);
    return (0);
}