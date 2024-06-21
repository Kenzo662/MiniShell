/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flux2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evella <enzovella6603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:33:16 by evella            #+#    #+#             */
/*   Updated: 2024/06/07 13:09:53 by evella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_write_heredock(char *str, char *heredoc, int pipefd[2])
{
	free(str);
	write(pipefd[1], heredoc, ft_strlen(heredoc));
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
}

void	ft_heredock(char *end, t_flux *flux)
{
	int		pipefd[2];
	char	*str;
	char	*tmp;
	char	*heredoc;

	pipe(pipefd);
	tmp = NULL;
	heredoc = NULL;
	write(flux->saveout, "> ", 2);
	str = get_next_line(flux->savein);
	while (!(ft_strncmp(str, end, ft_strlen(str) - 1) == 0 && ft_strlen(str)
			- 1 == ft_strlen(end)))
	{
		tmp = heredoc;
		heredoc = ft_strjoin(heredoc, str);
		if (str)
			free(str);
		write(flux->saveout, "> ", 2);
		str = get_next_line(flux->savein);
		if (tmp)
			free(tmp);
	}
	ft_write_heredock(str, heredoc, pipefd);
	free(heredoc);
}

void	ft_change_flux(t_eflux *brulux, int savein, int saveout)
{
	if (*brulux == IN || *brulux == INOUT)
		dup2(savein, STDIN_FILENO);
	if (*brulux == OUT || *brulux == INOUT)
		dup2(saveout, STDOUT_FILENO);
	*brulux = INIT;
}

void	ft_write_err(int saveout, char *str, t_eflux af)
{
	if (af == ERR)
	{
		write(saveout, "bash: ", ft_strlen("bash: "));
		write(saveout, str, ft_strlen(str));
		write(saveout, ": No such file or directory\n",
			ft_strlen(": No such file or directory\n"));
	}
	else
	{
		write(saveout, "bash: invalid redirection \'",
			ft_strlen("bash: invalid redirection \'"));
		write(saveout, &str[0], 1);
		if (str[1] == str[0])
			write(saveout, &str[1], 1);
		write(saveout, "\'\n", 2);
	}
}

void	ft_err(t_tokens *tokens, char **newargs, int j)
{
	ft_freetabtab(tokens[j].args);
	ft_freetabtab(newargs);
	free(tokens[j].strstate);
	free(tokens[j].token);
}
