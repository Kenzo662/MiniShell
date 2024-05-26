/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzovella <enzovella@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 03:13:35 by evella            #+#    #+#             */
/*   Updated: 2023/12/05 09:14:23 by enzovella        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr(const char *s)
{
	int	i;

	i = 0;
	if (!s)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
	return (i);
}

int	ft_putchar(const char c)
{
	write(1, &c, 1);
	return (1);
}

static unsigned int	ft_uintlen(unsigned int n)
{
	int	len;

	len = 1;
	while (n / 10 != 0)
	{
		len = len * 10;
		n = n / 10;
	}
	return (len);
}

int	ft_putnbru(unsigned int n)
{
	unsigned int	len;
	char			res;
	int				j;

	j = 0;
	len = ft_uintlen(n);
	while (len >= 1)
	{
		res = n / len + '0';
		write (1, &res, 1);
		n = n % len;
		len = len / 10;
		j++;
	}
	return (j);
}
