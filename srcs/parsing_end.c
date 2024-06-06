#include "../include/minishell.h"

int	ft_check_available(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!str || !str[i])
		return (j);
	while (str[i])
	{
		if (str[i] != '\n')
			j = 1;
		i++;
	}
	return (j);
}

void	ft_add_last_str(arg_state *strstate, arg_state *state, t_index *index,
		t_parsend *pstr)
{
	if (*strstate == FSPACE)
		ft_change_agstate_2(ft_find_cstate(pstr->str[index->i],
				pstr->str[index->i + 1]), strstate);
	if ((*state == SEARCH) && (*strstate == DQUOTE || *strstate == QUOTE))
	{
		*state = *strstate;
		ft_change_agstate_2(ft_find_cstate(pstr->str[index->i],
				pstr->str[index->i + 1]), strstate);
		if (pstr->str[++index->i])
			ft_change_agstate_2(ft_find_cstate(pstr->str[index->i],
					pstr->str[index->i + 1]), strstate);
	}
	if ((*state == DQUOTE && pstr->str[index->i] == '\"') || (*state == QUOTE
			&& pstr->str[index->i] == '\''))
	{
		*state = SEARCH;
		ft_change_agstate_2(ft_find_cstate(pstr->str[index->i],
				pstr->str[index->i + 1]), strstate);
		if (pstr->str[++index->i])
			ft_change_agstate_2(ft_find_cstate(pstr->str[index->i],
					pstr->str[index->i + 1]), strstate);
	}
	else if (pstr->str[index->i])
	{
		pstr->newstr = ft_realloc(pstr->newstr);
		pstr->newstr[index->j] = pstr->str[index->i];
		ft_change_agstate_2(ft_find_cstate(pstr->str[index->i],
				pstr->str[index->i + 1]), strstate);
		index->j++;
		index->i++;
	}
}
char	*ft_parsing_end(char *str)
{
	arg_state	strstate;
	arg_state	state;
	t_parsend	pstr;
	t_index		index;

	index.i = 0;
	index.j = 0;
	state = SEARCH;
	strstate = SEARCH;
	pstr.newstr = NULL;
	pstr.str = str;
	if (str[index.i])
		ft_change_agstate_2(ft_find_cstate(str[0], str[1]), &strstate);
	while (str[index.i])
		ft_add_last_str(&strstate, &state, &index, &pstr);
	if (!pstr.newstr)
		return (free(str), ft_calloc(sizeof(char), 1));
	free(str);
	return (pstr.newstr);
}
