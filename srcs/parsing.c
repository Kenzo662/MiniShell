#include "../include/minishell.h"

char	*ft_print_prompt(void)
{
	char	buff[4096];
	char	*prompt;
	char	*uprompt;
	char	*tmp;
	int		i;

	prompt = ft_strjoin(getcwd(buff, 4096), DEF " > " DEF);
	i = 6;
	while (prompt[i] && prompt[i] != '/')
		i++;
	tmp = ft_strdup(&prompt[i]);
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
	exit(0);
}
char	**ft_tokeniser(char *uprompt, char **env)
{
	char	**tb;
	char	**tokens;

	tb = NULL;
	tb = ft_sort_uprompt(uprompt);
	ft_vr(tb, env);
	free(uprompt);
	tokens = ft_sort_token(tb);
	return (tokens);
}

t_tokens	*ft_receive_uprompt(char *uprompt, char **env)
{
	t_tokens	*tokens;
	char		**tmpt;
	int			i;

	i = 0;
	tmpt = ft_tokeniser(uprompt, env);
	while (tmpt[i])
		i++;
	tokens = ft_calloc(sizeof(*tokens), i + 1);
	tokens[0].nbtokens = i;
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
