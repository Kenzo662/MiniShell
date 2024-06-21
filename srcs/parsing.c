/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evella <enzovella6603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:26:46 by evella            #+#    #+#             */
/*   Updated: 2024/06/10 14:35:05 by evella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_print_prompt(void)
{
	char	buff[4096];
	char	*prompt;
	char	*uprompt;
	char	*tmp;

	prompt = ft_strjoin(getcwd(buff, 4096), DEF " > " DEF);
	tmp = ft_strdup(ft_strchr(prompt + 6, '/'));
	free(prompt);
	prompt = ft_strjoin(BOLD_GREEN "︻╦╤─~" BOLD_BLUE, tmp);
	free(tmp);
	tmp = ft_strdup(prompt);
	free(prompt);
	if (ft_strcmp(tmp, BOLD_GREEN "︻╦╤─~" BOLD_BLUE) == 0)
		prompt = ft_strjoin(tmp, DEF " > ");
	else
		prompt = ft_strdup(tmp);
	free(tmp);
	uprompt = readline(prompt);
	add_history(uprompt);
	free(prompt);
	if (uprompt)
		return (uprompt);
	printf("exit\n");
	return (NULL);
}

char	**ft_sort_uprompt_2(char *str)
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
		l = ft_find_arg_2(newstr, &arg, &index);
		if (l == 1)
			newstr = ft_gnl(newstr);
	}
	if (newstr)
		free(newstr);
	return (arg.args);
}

t_tokens	*ft_receive_uprompt(char *uprompt, char **env, int *rexit)
{
	t_tokens	*tokens;
	char		**tmpt;
	int			i;

	if (!uprompt)
		return (NULL);
	i = 0;
	tmpt = ft_tokeniser(uprompt, env, rexit);
	while (tmpt[i])
		i++;
	tokens = ft_calloc(sizeof(*tokens), i + 1);
	tokens[0].nbtokens = i;
	tokens[0].rexit = *rexit;
	i = 0;
	while (tmpt[i])
	{
		tokens[i].token = ft_strdup(tmpt[i]);
		tokens[i].args = ft_sort_uprompt_2(tmpt[i]);
		i++;
	}
	ft_last_parsing(tokens);
	ft_freetabtab(tmpt);
	return (tokens);
}

int ft_check_ok(char *str)
{
	if (ft_strcmp(str, "<<") == 0 || ft_strcmp(str, "<") == 0 
		|| ft_strcmp(str, ">") == 0 || ft_strcmp(str, ">>") == 0)
			return (1);
	return(0);
}

char	**ft_sort_token(char **tb)
{
	int		i;
	int		j;
	char	**tokens;
	char	*tmp;

	i = 0;
	j = 0;
	tokens = NULL;
	tokens = ft_tb_realloc(tokens);
	while (tb[i])
	{
		tmp = ft_strtrim(tb[i], " \n");
		if (tmp[0] == '|' && ft_strlen(tmp) == 1)
		{
			if (i == 0 || !tb[i + 1] || ft_check_ok(tb[i + 1]) || ft_check_ok(tb[i - 1]))
				return (printf("usage pipe : [cmd] | [cmd] ...\n"), ft_freetabtab(tokens),
					free(tmp), ft_freetabtab(tb), NULL);
			tokens = ft_tb_realloc(tokens);
			j++;
			i++;
		}
		tokens[j] = ft_join_space(tokens[j], tb[i]);
		free(tmp);
		i++;
	}
	ft_freetabtab(tb);
	return (tokens);
}
