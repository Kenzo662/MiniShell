/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evella <enzovella6603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:26:48 by evella            #+#    #+#             */
/*   Updated: 2024/06/10 15:23:17 by evella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_realloc(char *str)
{
	char	*newstr;
	int		i;

	i = 0;
	if (!str)
		return (ft_calloc((2), sizeof(char)));
	newstr = (ft_calloc((ft_strlen((char *)str) + 2), sizeof(char)));
	while (str[i])
	{
		newstr[i] = str[i];
		i++;
	}
	free(str);
	str = NULL;
	return (newstr);
}

char	**ft_tb_realloc(char **tb)
{
	char	**newtb;
	int		i;

	i = 0;
	if (!tb)
		return (ft_calloc((2), sizeof(char *)));
	while (tb[i])
	{
		i++;
	}
	newtb = ft_calloc(sizeof(char *), i + 2);
	i = 0;
	while (tb[i])
	{
		if (tb[i][0])
			newtb[i] = ft_strdup(tb[i]);
		else
			newtb[i] = ft_calloc(sizeof(char), 1);
		i++;
	}
	newtb[i] = NULL;
	ft_freetabtab(tb);
	tb = NULL;
	return (newtb);
}

void	*ft_freetabtab(char **tb)
{
	int	i;

	i = 0;
	if (!tb)
		return (NULL);
	while (tb[i])
	{
		free(tb[i]);
		i++;
	}
	if (tb[i])
		free(tb[i]);
	if (tb)
		free(tb);
	return (NULL);
}

void	ft_printtabtab(char **tb)
{
	int	i;

	i = 0;
	while (tb[i])
	{
		printf("%s\n", tb[i]);
		i++;
	}
}

void	ft_clear(char **env)
{
	int		status;
	int		execr;
	int		i;
	char	**path;
	char	**cleararg;
	pid_t	pid;

	cleararg = (char **)malloc(sizeof(char *) * 2);
	cleararg[0] = ft_strdup("clear");
	cleararg[1] = NULL;
	i = -1;
	pid = fork();
	if (pid == 0)
	{
		path = ft_create_path(getenv("PATH"), "clear");
		execr = access(path[0], X_OK);
		while (execr == -1 && path[++i])
			execr = access(path[i], X_OK);
		execve("clear", cleararg, env);
	}
	else
		wait(&status);
	ft_freetabtab(cleararg);
}
