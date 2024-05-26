/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evella <evella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 21:57:57 by evella            #+#    #+#             */
/*   Updated: 2023/10/01 21:58:27 by evella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	if (!to_find[i])
		return (str);
	while (str[i])
	{
		while (str[i] == to_find[j])
		{
			i++;
			j++;
			if (!to_find[j])
				return (&str[i - j]);
		}
		j = 0;
		i++;
	}
	return (NULL);
}
