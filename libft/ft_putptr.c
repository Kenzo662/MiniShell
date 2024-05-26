/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzovella <enzovella@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 19:42:52 by evella            #+#    #+#             */
/*   Updated: 2023/12/05 09:13:13 by enzovella        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_hexalen(unsigned long int n)
{
	int	len;

	len = 0;
	while (n / 16 != 0)
	{
		len++;
		n = n / 16;
	}
	return (len);
}

static int	ft_putptr_two(unsigned long int n, int j)
{
	int		len;
	char	*res;

	len = ft_hexalen(n);
	res = (char *)ft_calloc(sizeof(char), (len + 2));
	if (!res)
	{
		return (0);
	}
	while (n != 0)
	{
		res[len--] = "0123456789abcdef"[n % 16];
		n = n / 16;
		j++;
	}
	ft_putstr(res);
	free (res);
	return (j);
}

int	ft_putptr(unsigned long int n)
{
	int	j;

	j = 0;
	if (!n)
	{
		ft_putstr("(nil)");
		return (5);
	}
	j = 2;
	ft_putstr("0x");
	return (ft_putptr_two(n, j));
}
