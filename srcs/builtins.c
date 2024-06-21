/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenz <kenz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:26:25 by evella            #+#    #+#             */
/*   Updated: 2024/06/20 16:46:44 by kenz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_cd(char **args, int saveout, unsigned int *rexit)
{
	char	*path;
	char	buff[4096];
	char	*cutdir;

	if (args[1] && args[2])
	{
		write(saveout, "bash: cd: too many arguments\n", 29);
		*rexit = 1;
		return;
	}
	path = getcwd(buff, 4096);
	cutdir = ft_cutdir(path, args[1]);
	if (chdir(cutdir) == 0 || ft_strcmp(path, args[1]) == 0)
		*rexit = 0;
	else
		*rexit = 1;
	free(cutdir);
}
static int	ft_find_option(char *arg)
{
	int	i;
	
	i = 2;
	if (arg[0] == '-' && arg[1] == 'n')
	{
		while (arg[i])
		{
			if (arg[i] != 'n')
				return (1);
			i++;
		}
		return (0);
	}
	else
		return (1);
}

void    ft_echo(t_tokens token, unsigned int *rexit)
{
    int    i;
    int    j;

    i = 1;
    j = 0;
    while (token.args[i])
    {
        if (ft_find_option(token.args[i]) == 0 && j == 0)
            i++;
        else if (ft_find_option(token.args[i]) == 1 || (ft_find_option(token.args[i]) == 0 && j > 0))
        {
            printf("%s", token.args[i]);
            j++;
            i++;
        }
        if (token.args[i] != NULL && ft_find_option(token.args[i - 1]) == 1)
            printf(" ");
    }
    if (token.args[1])
	{
        if (ft_find_option(token.args[1]) == 1)
            printf("\n");
	}
	*rexit = 0;
}

char	**ft_unset(char *varname, char **env, unsigned int *rexit)
{
	int	pos;

	if (!varname)
		return (*rexit = 0, env);
	pos = ft_check_var(varname, env);
	if (pos != 0)
		env = ft_tab_cat(env, pos);
	return (*rexit = 0 , env);
}
