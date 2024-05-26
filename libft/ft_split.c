/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evella <evella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 23:16:25 by evella            #+#    #+#             */
/*   Updated: 2023/10/04 19:10:00 by evella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

static int	ft_countwords(char const *s, char c)
{
	int	words;
	int	i;

	i = 0;
	words = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == 0))
			words++;
		i++;
	}
	return (words);
}

static void	*ft_freetabtab(int k, char **tab)
{
	while (k > 0)
	{
		k--;
		free(tab[k]);
	}
	free (tab);
	return (NULL);
}

static char	**ft_mallocwords(char **tab, const char *s, char c)
{
	int	i;
	int	j;
	int	k;

	k = 0;
	j = 1;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == 0))
		{
			tab[k] = (char *)malloc(sizeof(char) * (j + 1));
			if (!tab[k])
				return (ft_freetabtab(k, tab));
			k++;
			j = 0;
		}
		if (s[i] != c && s[i] != c)
			j++;
		i++;
	}
	return (tab);
}

void	ft_addwords(char **tab, char const *s, char c)
{
	int		i;
	int		j;
	int		k;

	j = 0;
	k = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == 0))
		{
			tab[k][j] = s[i++];
			tab[k++][j + 1] = '\0';
			j = 0;
		}
		else if (s[i] == c)
			i++;
		else
			tab[k][j++] = s[i++];
	}
	tab[k] = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		countwords;

	countwords = ft_countwords(s, c);
	tab = (char **)malloc(sizeof(char *) * (countwords + 1));
	if (!tab || !ft_mallocwords(tab, s, c))
		return (NULL);
	ft_addwords(tab, s, c);
	return (tab);
}
