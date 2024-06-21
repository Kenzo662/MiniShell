/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evella <enzovella6603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:26:29 by evella            #+#    #+#             */
/*   Updated: 2024/06/20 14:00:40 by evella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_check_args_exit(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (ft_isalpha(arg[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}

unsigned long long	ft_exit(char **args, unsigned int *rexit)
{
	unsigned long long	n;

	n = 0;
	if (!args[1])
		return (printf("exit\n"), 0);
	if (args[1] && !args[2])
	{
		if (ft_check_args_exit(args[1]) == 1)
			return (printf("exit\nbash: exit: %s: numeric argument required\n", args[1]),
				*rexit = 2, 2);
		else
		{
			n = ft_atoll(args[1]);
			n %= 256;
		}
	}
	else if (args[2])
	{
		printf("exit\nbash: exit: too many arguments\n");
		*rexit = 1;
		return (-1);
	}
	printf("exit\n");
	*rexit = n;
	return (n);
}
