/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenz <kenz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:26:30 by evella            #+#    #+#             */
/*   Updated: 2024/06/20 16:47:07 by kenz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static	int    ft_check_if_exportable(char *var_to_create)
{
    int    i;

    i = 1;
    while (var_to_create[i] != '=')
    {
        if (ft_isalnum(var_to_create[i]) == 0)
            return (1);
        i++;
    }
    return (0);
}
char    **ft_export(char *var_to_create, char **var_tab, unsigned int *rexit)
{
    int    i;
    int    pos;

    var_tab = ft_tb_realloc(var_tab);
    i = 0;
    if (!var_to_create)
        return (ft_bubble_export(var_tab), var_tab);
    if (ft_isalpha(var_to_create[0]) == 0 || ft_check_if_exportable(var_to_create) == 1)
        return (printf("bash: export: « %s » : not a valid identifier\n",
                var_to_create), *rexit = 1, var_tab);
    if (ft_strchr(var_to_create, '=') == NULL || ft_strcmp(var_to_create,
            "=") == 0)
        return (var_tab);
    if (ft_check_var(var_to_create, var_tab) != 0)
    {
        pos = ft_check_var(var_to_create, var_tab);
        free(var_tab[pos]);
        var_tab[pos] = ft_strdup(var_to_create);
        return (var_tab);
    }
    while (var_tab[i])
        i++;
    var_tab[i] = ft_strdup(var_to_create);
    return (var_tab);
}

int	ft_check_var(char *var, char **var_tab)
{
	int		i;
	char	**tmp;
	char	**tmp2;

	i = 0;
	tmp = ft_split(var, '=');
	while (var_tab[i])
	{
		tmp2 = ft_split(var_tab[i], '=');
		if (ft_strcmp(tmp[0], tmp2[0]) == 0)
			return (ft_freetabtab(tmp), ft_freetabtab(tmp2), i);
		ft_freetabtab(tmp2);
		i++;
	}
	ft_freetabtab(tmp);
	tmp = NULL;
	tmp2 = NULL;
	return (0);
}

void	ft_bubble_export(char **var_tab)
{
	int		i;
	int		j;
	int		len;
	char	**export_env;

	i = 0;
	j = 0;
	len = 0;
	export_env = ft_create_env(var_tab);
	while (var_tab[len])
		len++;
	i = 0;
	while (i < len - 1)
	{
		j = 0;
		while (j < len - 1)
		{
			if (export_env[j][0] > export_env[j + 1][0])
				ft_swap_str(export_env, j);
			j++;
		}
		i++;
	}
	ft_display_export(export_env);
	ft_freetabtab(export_env);
}

void	ft_swap_str(char **var_tab, int j)
{
	char	*tmp;

	tmp = var_tab[j];
	var_tab[j] = var_tab[j + 1];
	var_tab[j + 1] = tmp;
}

void	ft_display_export(char **export_tab)
{
	int	i;
	int	j;
	int	count;

	i = -1;
	count = 0;
	while (export_tab[++i])
	{
		count = 0;
		j = -1;
		printf("declare -x ");
		while (export_tab[i][++j])
		{
			if (j > 1)
			{
				if (export_tab[i][j - 1] == '=' && count == 0)
				{
					printf("\"");
					count = 1;
				}
			}
			printf("%c", export_tab[i][j]);
		}
		printf("\"\n");
	}
}
