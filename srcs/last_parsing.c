/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evella <enzovella6603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:26:34 by evella            #+#    #+#             */
/*   Updated: 2024/06/18 17:25:51 by evella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_new_state(t_arg_state *strstate, char c)
{
	if (c == '<' || c == '>')
		*strstate = OP;
	if (c == '\'')
		*strstate = QUOTE;
	else if (c == '\"')
		*strstate = DQUOTE;
	else
		*strstate = SEARCH;
}

static void	ft_save_state_2(t_tokens *tokens, int x, t_index *index,
		t_arg_state *tmpstate)
{
	while (tmpstate && tmpstate[index->l])
	{
		tokens[x].strstate[index->l] = tmpstate[index->l];
		index->l++;
	}
	index->l = 0;
	if (tmpstate)
		free(tmpstate);
	index->k++;
	index->j++;
}

static void	ft_save_state(t_tokens *tokens, int x)
{
	t_index		index;
	t_arg_state	strstate;
	t_arg_state	*tmpstate;

	index.i = 0;
	index.l = 0;
	index.k = 0;
	strstate = SEARCH;
	tokens[x].strstate = NULL;
	tmpstate = NULL;
	while (tokens[x].args && tokens[x].args[index.i])
	{
		index.j = 0;
		ft_new_state(&strstate, tokens[x].args[index.i][index.j]);
		tmpstate = tokens[x].strstate;
		tokens[x].strstate = ft_calloc(sizeof(t_arg_state), index.k + 2);
		tokens[x].strstate[index.k] = strstate;
		ft_save_state_2(tokens, x, &index, tmpstate);
		index.i++;
	}
}

static void	ft_last_parsing_2(char **tokentmp, t_tokens *tokens, t_index *index)
{
	char	*tmp;

	tmp = NULL;
	while (tokens[index->j].args[index->i])
	{
		tmp = ft_strjoin(*tokentmp, tokens[index->j].args[index->i]);
		if (*tokentmp)
			free(*tokentmp);
		if (tokens[index->j].args[index->i + 1])
			*tokentmp = ft_strjoin(tmp, " ");
		else
			*tokentmp = ft_strdup(tmp);
		free(tmp);
		tokens[index->j].args[index->i] = ft_parsing_end
			(tokens[index->j].args[index->i], &tokens[index->j]);
		index->i++;
	}
}

void	ft_last_parsing(t_tokens *tokens)
{
	t_index	index;
	char	*tokentmp;

	index.i = 0;
	index.j = 0;
	tokentmp = NULL;
	while (tokens[index.j].token)
	{
		ft_save_state(tokens, index.j);
		ft_last_parsing_2(&tokentmp, tokens, &index);
		index.i = 0;
		free(tokens[index.j].token);
		tokens[index.j].token = ft_strdup(tokentmp);
		free(tokentmp);
		tokentmp = NULL;
		index.j++;
	}
}
