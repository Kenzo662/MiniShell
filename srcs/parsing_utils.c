/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evella <enzovella6603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:26:41 by evella            #+#    #+#             */
/*   Updated: 2024/06/10 15:43:34 by evella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_arg_state	ft_find_cstate(char c, char next)
{
	if (c == '|' || c == '>' || (c == '>' && next == '>') || c == '<'
		|| (c == '<' && next == '<'))
		return (OP);
	if ((c == 32 || c == '\n' || c == '\t')
		&& (next != 32 && next != '\n' && next != '\t'))
		return (FSPACE);
	else if (c == 0)
		return (FSPACE);
	else if (c == 39)
		return (QUOTE);
	else if (c == 34)
		return (DQUOTE);
	else if (c == 32 || c == '\n')
		return (DSPACE);
	else
		return (SEARCH);
}

int	ft_change_agstate(t_arg_state cs, t_arg_state *ags, int j)
{
	if ((*ags == SEARCH && cs != DSPACE) || (*ags == FSPACE && cs == OP))
	{
		if (*ags == FSPACE && cs == OP && j > 0)
			return (*ags = SEARCH, 3);
		if (cs == DQUOTE || cs == QUOTE)
			*ags = cs;
		else if (cs == OP)
			*ags = OP;
		else
			*ags = FSPACE;
		return (1);
	}
	else if (*ags == SEARCH && cs == DSPACE)
		return (0);
	else if (((cs == FSPACE || cs == DSPACE || cs == OP)
			&& *ags == FSPACE) || (cs != OP && *ags == OP))
		return (*ags = SEARCH, 3);
	else if ((cs == DQUOTE && *ags == DQUOTE) || (cs == QUOTE
			&& *ags == QUOTE))
		*ags = FSPACE;
	else if ((cs == DQUOTE || cs == QUOTE) && (*ags != DQUOTE
			&& *ags != QUOTE))
		*ags = cs;
	return (2);
}

void	ft_new_arg(t_arg *arg, t_index *index)
{
	(*arg).args = ft_tb_realloc((*arg).args);
	(*arg).args[(*index).k] = ft_strdup((*arg).arg);
	(*index).k++;
	(*index).i--;
	(*index).j = 0;
	free((*arg).arg);
	(*arg).arg = NULL;
}

void	ft_joinarg(t_arg *arg, char *str, t_index *index)
{
	(*arg).arg = ft_realloc((*arg).arg);
	(*arg).arg[(*index).j] = str[(*index).i];
	(*index).j++;
}

char	*ft_join_space(char *s1, char *s2)
{
	char	*newstr;
	char	sp[2];

	sp[0] = ' ';
	sp[1] = '\0';
	if (!s1)
		return (ft_strdup(s2));
	newstr = ft_strjoin(s1, sp);
	if (s1)
		free(s1);
	s1 = newstr;
	newstr = ft_strjoin(newstr, s2);
	if (s1)
		free(s1);
	return (newstr);
}
