/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evella <enzovella6603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:04:27 by evella            #+#    #+#             */
/*   Updated: 2024/06/10 14:42:19 by evella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**ft_tokeniser(char *uprompt, char **env, int *rexit)
{
	char	**tb;
	char	**tokens;

	tb = NULL;
	tb = ft_sort_uprompt(uprompt);
	ft_vr(tb, env, rexit);
	free(uprompt);
	tokens = ft_sort_token(tb);
	if (!tokens)
	{
		tokens = ft_calloc(sizeof(char *), 2);
		tokens[0] = ft_calloc(sizeof(char), 1);
		tokens[1] = NULL;
	}
	return (tokens);
}

char	**ft_sort_uprompt(char *str)
{
	t_index	index;
	t_arg	arg;
	char	*newstr;
	int		l;

	index.i = 0;
	index.j = 0;
	index.k = 0;
	l = 1;
	arg.agstate = SEARCH;
	arg.args = NULL;
	arg.arg = NULL;
	newstr = ft_strdup(str);
	while (l)
	{
		l = ft_find_arg(newstr, &arg, &index);
		if (l == 1)
			newstr = ft_gnl(newstr);
	}
	if (newstr)
		free(newstr);
	return (arg.args);
}

t_arg_state	ft_find_cstate_2(char c, char next)
{
	if ((c == 32 || c == 9) && (next != 32 && next != 9))
		return (FSPACE);
	else if (c == 0)
		return (FSPACE);
	else if (c == 39)
		return (QUOTE);
	else if (c == 34)
		return (DQUOTE);
	else if (c == 32 || c == 9)
		return (DSPACE);
	else
		return (SEARCH);
}

int	ft_change_agstate_2(t_arg_state cstate, t_arg_state *agstate)
{
	if (*agstate == SEARCH && cstate != DSPACE)
	{
		if (cstate == DQUOTE || cstate == QUOTE)
			*agstate = cstate;
		else
			*agstate = FSPACE;
		return (1);
	}
	else if (*agstate == SEARCH && cstate == DSPACE)
		return (0);
	else if ((cstate == FSPACE || cstate == DSPACE) && *agstate == FSPACE)
	{
		*agstate = SEARCH;
		return (3);
	}
	else if ((cstate == DQUOTE && *agstate == DQUOTE) || (cstate == QUOTE
			&& *agstate == QUOTE))
		*agstate = FSPACE;
	else if ((cstate == DQUOTE || cstate == QUOTE) && (*agstate != DQUOTE
			&& *agstate != QUOTE))
		*agstate = cstate;
	return (2);
}
