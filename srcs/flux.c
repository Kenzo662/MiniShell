/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flux.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evella <enzovella6603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:26:32 by evella            #+#    #+#             */
/*   Updated: 2024/06/18 17:13:31 by evella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_eflux	ft_redirect_output(int *fd, char **args, int i)
{
	if (ft_strcmp(args[i], ">>") == 0)
	{
		*fd = open(args[i + 1], O_APPEND | O_WRONLY | O_CREAT, 0777);
		dup2(*fd, STDOUT_FILENO);
	}
	else if (args[i][0] == '>' && ft_strlen(args[i]) == 1)
	{
		*fd = open(args[i + 1], O_TRUNC | O_WRONLY | O_CREAT, 0777);
		dup2(*fd, STDOUT_FILENO);
	}
	return (OUT);
}

static t_eflux	ft_redirect_input(t_flux *flux, char **args, int i)
{
	if (ft_strcmp(args[i], "<<") == 0)
		ft_heredock(args[i + 1], flux);
	else if (args[i][0] == '<' && ft_strlen(args[i]) == 1)
	{
		flux->actualfd = open(args[i + 1], O_RDONLY);
		dup2(flux->actualfd, STDIN_FILENO);
	}
	return (IN);
}

static t_eflux	ft_redirect_flux(char **args, t_index *index, t_flux *flux,
		char c)
{
	if (ft_strlen(args[index->i]) > 2 || !args[index->i + 1] || index->i == 0)
		return (ERRQ);
	if (c == '>')
	{
		if (flux->actualflux == IN)
			flux->actualflux = INOUT;
		else if (flux->actualflux != INOUT)
			flux->actualflux = OUT;
		ft_redirect_output(&flux->actualfd, args, index->i);
	}
	else
	{
		if (flux->actualflux == OUT)
			flux->actualflux = INOUT;
		else if (flux->actualflux != INOUT)
			flux->actualflux = IN;
		if (flux->actualfd == -1)
			return (ERR);
		ft_redirect_input(flux, args, index->i);
	}
	return (IN);
	index->k = 1;
}

static char	**ft_end_redirec(char	**newargs, t_tokens *tokens
		, int j, t_index *index)
{
	newargs = ft_tb_realloc(newargs);
	if (tokens[j].args[index->i][0])
		newargs[index->j] = ft_strdup(tokens[j].args[index->i]);
	else
		newargs[index->j] = ft_calloc(sizeof(char), 1);
	index->j++;
	return (newargs);
}

char	**ft_checkredirect(t_tokens *tokens, t_flux *flux, int j)
{
	t_index	index;
	char	**newargs;
	t_eflux	af;

	newargs = NULL;
	flux->actualflux = INIT;
	index.j = 0;
	index.i = 0;
	index.k = 0;
	while (tokens[j].args[index.i])
	{
		if ((tokens[j].args[index.i][0] == '>'
			|| tokens[j].args[index.i][0] == '<') 
			&& (tokens[j].strstate[index.i] != QUOTE 
			&& tokens[j].strstate[index.i] != DQUOTE))
		{
			af = ft_redirect_flux(tokens[j].args, &index, flux,
					tokens[j].args[index.i][0]);
			if (af == ERR || af == ERRQ)
				return (ft_write_err(flux->saveout, tokens[j].args[index.i],
						af), ft_err(tokens, newargs, j), NULL);
		}
		else if (flux->actualflux == INIT && index.k == 0)
			newargs = ft_end_redirec(newargs, tokens, j, &index);
		index.i++;
	}
	return (ft_freetabtab(tokens[j].args), newargs);
}
