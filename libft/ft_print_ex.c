/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzovella <enzovella@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 03:08:57 by evella            #+#    #+#             */
/*   Updated: 2023/12/05 09:17:17 by enzovella        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_hexalen(unsigned int n)
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

static int	ft_putnbr_hexa_two(unsigned int n, int upper, int j)
{
	int		i;
	int		len;
	char	*res;

	i = -1;
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
	while (upper == 1 && res[++i])
		res[i] = ft_toupper(res[i]);
	ft_putstr(res);
	free (res);
	return (j);
}

int	ft_putnbr_hexa(unsigned int n, int upper, int format)
{
	int	j;

	j = 0;
	if (!n && format == 0)
	{
		ft_putstr("(nil)");
		return (5);
	}
	else if (!n && format == 1)
	{
		ft_putstr("0");
		return (1);
	}
	if (format == 0)
	{
		j = 2;
		ft_putstr("0x");
	}
	return (ft_putnbr_hexa_two(n, upper, j));
}

int	ft_intlenn(int n)
{
	int	len;

	len = 1;
	if (n < 0)
	{
		n = n * -1;
		len++;
	}
	while (n / 10 != 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}
