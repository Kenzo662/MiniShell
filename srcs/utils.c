#include "../include/minishell.h"

char	*ft_realloc(char *str)
{
	char	*newstr;
	int		i;

	i = 0;
	if (!str)
		return (ft_calloc((2), sizeof(char)));
	newstr = (ft_calloc((ft_strlen((char *)str) + 2), sizeof(char)));
	while (str[i])
	{
		newstr[i] = str[i];
		i++;
	}
	free(str);
	str = NULL;
	return (newstr);
}

char	**ft_tb_realloc(char **tb)
{
	char	**newtb;
	int		i;

	i = 0;
	if (!tb)
		return (ft_calloc((2), sizeof(char *)));
	while (tb[i])
	{
		i++;
	}
	newtb = ft_calloc(sizeof(char *), i + 2);
	i = 0;
	while (tb[i])
	{
		if (tb[i][0])
			newtb[i] = ft_strdup(tb[i]);
		else
			newtb[i] = ft_calloc(sizeof(char), 1);
		i++;
	}
	newtb[i] = NULL;
	ft_freetabtab(tb);
	tb = NULL;
	return (newtb);
}

void	*ft_freetabtab(char **tb)
{
	int	i;

	i = 0;
	if (!tb)
		return (NULL);
	while (tb[i])
	{
		free(tb[i]);
		i++;
	}
	if (tb[i])
		free(tb[i]);
	if (tb)
		free(tb);
	return (NULL);
}

void	ft_printtabtab(char **tb)
{
	int	i;

	i = 0;
	while (tb[i])
	{
		printf("[%s]\n", tb[i]);
		i++;
	}
}

void	ft_print_tokens(t_tokens *tokens)
{
	int	i;

	i = 0;
	ft_printf("[//////////////////////////]\n");
	while (tokens[i].token)
	{
		ft_printf("[TOKEN]\n%s\n[ARGS]\n", (tokens[i]).token);
		ft_printtabtab((tokens[i]).args);
		ft_printf("[//////////////////////////]\n");
		i++;
	}
}
