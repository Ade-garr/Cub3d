/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 15:30:02 by ade-garr          #+#    #+#             */
/*   Updated: 2020/06/17 14:27:21 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_nb(char const *s, char c)
{
	int	a;
	int	i;
	int	j;

	i = 0;
	a = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			a++;
			j = i;
			while (s[j] && s[j] != c)
				j++;
			i = j - 1;
		}
		i++;
	}
	return (a);
}

char		**ft_free(char ***s1)
{
	size_t	i;

	i = 0;
	while ((*s1)[i] != NULL)
	{
		free((*s1)[i]);
		(*s1)[i] = NULL;
		i++;
	}
	free(*s1);
	*s1 = NULL;
	return (NULL);
}

char			**ft_split(char const *s, char c)
{
	char	**s1;
	int		i;
	int		j;
	int		a;

	i = 0;
	a = 0;
	if (!s || !(s1 = malloc(sizeof(char *) * (ft_nb(s, c) + 1))))
		return (NULL);
	while (s[i])
	{
		if (s[i] != c)
		{
			j = i;
			while (s[j] && s[j] != c)
				j++;
			if (!(s1[a] = ft_substr(s, i, (j - i))))
				return (ft_free(&s1));
			a++;
			i = j - 1;
		}
		i++;
	}
	s1[a] = 0;
	return (s1);
}
