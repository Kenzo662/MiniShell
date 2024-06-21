/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenz <kenz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:26:18 by evella            #+#    #+#             */
/*   Updated: 2024/06/20 16:46:50 by kenz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

unsigned int	ft_builtins_exec(t_tokens token, char ***env, unsigned int *rexit, int saveout)
{
	char	buf[4096];

	if (!token.args[0] || !token.args[0][0])
		return (-1);
	if (ft_strcmp(token.args[0], "cd") == 0)
		return (ft_cd(token.args, saveout, rexit), -1);
	else if (ft_strcmp(token.args[0], "echo") == 0)
		return (ft_echo(token, rexit), -1);
	else if (ft_strcmp(token.args[0], "pwd") == 0)
		return (printf("%s\n", getcwd(buf, 4096)), *rexit = 0, -1);
	else if (ft_strcmp(token.args[0], "env") == 0)
		return (ft_printtabtab(*env), -1);
	else if (ft_strcmp(token.args[0], "exit") == 0)
		return (ft_exit(token.args, rexit));
	else
		return (ft_exec(token, *env, rexit, saveout), -1);
	return (-1);
}

char	**ft_create_env(char **envp)
{
	char	**env;
	int		i;

	i = 0;
	env = NULL;
	while (envp[i])
		i++;
	env = ft_calloc(i + 1, sizeof(char *));
	i = -1;
	while (envp[++i])
		env[i] = ft_strdup(envp[i]);
	env[i] = NULL;
	return (env);
}

char	**ft_tab_cat(char **tb, int pos)
{
	char	**newenv;
	int		i;
	int		j;
	int		len;

	i = 0;
	while (tb[i])
		i++;
	len = i;
	newenv = ft_calloc(i, sizeof(char *));
	i = 0;
	j = 0;
	while (i < len)
	{
		if (i != pos)
		{
			newenv[j] = ft_strdup(tb[i]);
			j++;
		}
		i++;
	}
	ft_freetabtab(tb);
	return (newenv);
}

char	**ft_export_exec(char **args, char **env, unsigned int *rexit)
{
	int	i;

	i = 0;
	if (!args[1])
		env = ft_export(NULL, env, rexit);
	while (args[++i])
		env = ft_export(args[i], env, rexit);
	return (env);
}
