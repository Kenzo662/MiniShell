/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evella <enzovella6603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:26:22 by evella            #+#    #+#             */
/*   Updated: 2024/06/07 12:31:14 by evella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_check_env(char *str)
{
	str = ft_strtrim(str, "${}");
	str = getenv(str);
	if (!str)
	{
		printf("\n");
		return ;
	}
	printf("%s", str);
}

char	*ft_cutdir(char *path, char *arg)
{
	int		i;
	char	*newpath;
	char	*tmp;

	i = 0;
	tmp = NULL;
	if (!arg || ft_strcmp(arg, "~") == 0)
	{
		i = 6;
		while (path[i + 1] != '/')
			i++;
		newpath = ft_calloc(sizeof(char), i + 2);
		ft_strncpy(newpath, path, i + 1);
	}
	else
	{
		tmp = ft_strjoin(path, "/");
		newpath = ft_strjoin(tmp, arg);
		free(tmp);
	}
	return (newpath);
}

void	ft_cut_get_env(char **value_var, char **var_tab, int *j)
{
	char	*tmp;

	*value_var = ft_strdup(var_tab[1]);
	if (var_tab[2])
	{
		while (var_tab[*j])
		{
			tmp = ft_strjoin(*value_var, "=");
			if (*value_var)
				free(*value_var);
			*value_var = ft_strjoin(tmp, var_tab[*j]);
			(*j)++;
			free(tmp);
		}
	}
}

char	*ft_get_env(char **env, char *var_name)
{
	char	*value_var;
	char	**var_tab;
	int		i;
	int		j;

	i = 0;
	j = 2;
	value_var = NULL;
	var_tab = NULL;
	while (env[i])
	{
		var_tab = ft_split(env[i], '=');
		if (ft_strcmp(var_name, var_tab[0]) == 0)
		{
			ft_cut_get_env(&value_var, var_tab, &j);
			return (ft_freetabtab(var_tab), value_var);
		}
		ft_freetabtab(var_tab);
		i++;
	}
	var_tab = NULL;
	return (value_var);
}
