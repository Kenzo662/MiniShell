/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evella <enzovella6603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:26:39 by evella            #+#    #+#             */
/*   Updated: 2024/06/19 16:07:54 by evella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_get_var(char *str, t_index *index, char **env, int *rexit)
{
	char	*var;
	char	*tmp;

	var = NULL;
	while (str[index->i] && ft_find_cstate
		(str[index->i], str[(index->i) + 1]) == SEARCH
		&& !(index->j >= 2 && str[index->i] == '$')
		&& str[index->i] != '\n' && str[index->i] != '=')
	{
		(index->i)++;
		(index->j)++;
		if (str[index->i - 1] == '?')
			break;
	}
	tmp = ft_calloc(sizeof(char), (index->j) + 1);
	ft_strncpy(tmp, &str[(index->i + 1) - (index->j)], (index->j) - 1);
	if (tmp[0] == '?' && !tmp[1])
		var = ft_itoa(*rexit);
	else
		var = ft_get_env(env, tmp);
	free(tmp);
	index->j = 0;
	return (var);
}

static char	*ft_realloc_newstr(char *newstr, char *str, t_index *index)
{
	newstr = ft_realloc(newstr);
	newstr[index->k] = str[index->i];
	index->k++;
	index->i++;
	return (newstr);
}

void	ft_add_var(t_var *var, int *k)
{
	var->tmp = ft_strjoin(var->newstr, var->var);
	*k = ft_strlen(var->tmp);
	if (var->newstr)
		free(var->newstr);
	var->newstr = ft_strdup(var->tmp);
	if (var->tmp)
		free(var->tmp);
	var->tmp = NULL;
	if (var->var)
		free(var->var);
	var->var = NULL;
}

char	*ft_swap_var(char *str, char **env, int *rexit)
{
	t_var		var;
	t_index		index;
	t_arg_state	strstate;

	index.i = 0;
	index.j = 0;
	index.k = 0;
	strstate = SEARCH;
	var.newstr = NULL;
	var.tmp = NULL;
	var.var = NULL;
	while (str[index.i])
	{
		ft_change_agstate_2(ft_find_cstate_2(str[index.i], str[index.i + 1]),
			&strstate);
		if (str[index.i] == '$' && strstate != QUOTE 
			&& str[index.i + 1] && str[index.i + 1] != '\"' 
			&& str[index.i + 1] != '\'' && str[index.i + 1] != ' ')
		{
			var.var = ft_get_var(str, &index, env, rexit);
			if (var.var)
				ft_add_var(&var, &index.k);
		}
		else
			var.newstr = ft_realloc_newstr(var.newstr, str, &index);
	}
	return (free(str), var.newstr);
}

void	ft_vr(char **tb, char **env, int *rexit)
{
	int	i;

	i = 0;
	while (tb[i])
	{
		tb[i] = ft_swap_var(tb[i], env, rexit);
		if (!tb[i])
			tb[i] = ft_calloc(sizeof(char), 1);
		i++;
	}
}
