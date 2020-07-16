/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 11:53:37 by ade-garr          #+#    #+#             */
/*   Updated: 2019/11/15 12:19:12 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	ln;
	char	*s2;

	i = start;
	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
	{
		if (!(s2 = malloc(sizeof(char) * 1)))
			return (NULL);
		s2[0] = '\0';
		return (s2);
	}
	while (s[i] && i - start < len)
		i++;
	ln = i - start;
	if (!(s2 = malloc(sizeof(char) * (ln + 1))))
		return (NULL);
	i = 0;
	while (s[start] && i < ln)
		s2[i++] = s[start++];
	s2[i] = '\0';
	return (s2);
}
