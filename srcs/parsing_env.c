#include "../include/minishell.h"

char   *ft_get_var(char *str, int *i, int *j, char **env)
{
    char    *var;
    char    *tmp;

    var = NULL;
    while (str[*i] && ft_find_cstate(str[*i], str[(*i) + 1]) == SEARCH 
    && !( *j > 2 && str[*i] == '$') && str[*i] != '\n')
    {
        (*i)++;
        (*j)++;
    }
    tmp = ft_calloc(sizeof(char), (*j) + 1);
    ft_strncpy(tmp, &str[(*i + 1) - (*j)], (*j) - 1);
    var = ft_get_env(env, tmp);
    free(tmp);
    *j = 0;
    return (var);
}

static char    *ft_realloc_newstr(char *newstr, char *str, t_index *index)
{
    newstr = ft_realloc(newstr);
    newstr[index->k] = str[index->i];
    index->k++;
    index->i++;
    return (newstr);
}
void    ft_add_var(t_var *var, int *k)
{
    var->tmp = ft_strjoin(var->newstr, var->var);
    *k = ft_strlen(var->tmp);
    if (var->newstr)
        free(var->newstr);
    var->newstr= ft_strdup(var->tmp);
    if (var->tmp)
        free(var->tmp);
    var->tmp = NULL;
    if (var->var)
        free(var->var);
    var->var = NULL;
}

char    *ft_swap_var(char *str, char **env)
{
    t_var   var;
    t_index index;
    arg_state   strstate;

    index.i = 0;
    index.j = 0;
    index.k = 0;
    strstate = SEARCH;
    var.newstr = NULL;
    var.tmp = NULL;
    var.var = NULL;
    while (str[index.i])
    {
        ft_change_agstate_2(ft_find_cstate_2(str[index.i], str[index.i + 1]), &strstate);
        if (str[index.i] == '$' && strstate != QUOTE)
        {
            var.var = ft_get_var(str, &index.i, &index.j, env);
            if (var.var)
                ft_add_var(&var, &index.k);
        }
        else
            var.newstr = ft_realloc_newstr(var.newstr, str, &index);
    }
    free (str);
    return (var.newstr);
}

void    ft_vr(char **tb, char **env)
{
    int i;

    i = 0;
    while(tb[i])
    {
        tb[i] = ft_swap_var(tb[i], env);
        i++;
    }
}
