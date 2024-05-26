/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evella <evella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 00:07:21 by evella            #+#    #+#             */
/*   Updated: 2023/10/03 13:05:54 by evella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_charverif(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	ft_setendstart(int *i, int *j, char const *s1, char const *set)
{
	int	k;
	int	l;

	k = 0;
	l = ft_strlen((char *) s1);
	while (s1[k] && ft_charverif(s1[k], set))
		k++;
	while (s1[l - 1] && ft_charverif(s1[l - 1], set))
		l--;
	*i = k;
	*j = l;
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		i;
	int		j;
	int		k;

	k = 0;
	i = 0;
	ft_setendstart(&i, &j, s1, set);
	if (i >= j)
	{
		str = (char *)malloc(sizeof(char));
		if (!str)
			return (NULL);
		str[0] = '\0';
		return (str);
	}
	str = (char *)malloc(sizeof(char) * (j - i + 1));
	if (!str)
		return (NULL);
	while (i < j)
	{
		str[k++] = s1[i++];
	}
	str[k] = '\0';
	return (str);
}
