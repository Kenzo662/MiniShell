#include "../include/minishell.h"

int ft_check_available(char *str)
{
    int i;
    int j;

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

void ft_add_last_str(arg_state *strstate, arg_state *state, t_index *index, t_parsend *pstr)
{
    if (*strstate == FSPACE)
        ft_change_agstate_2(ft_find_cstate(pstr->str[index->i], pstr->str[index->i + 1]), strstate);
    if ((*state == SEARCH) && (*strstate == DQUOTE || *strstate == QUOTE ))
    {
       *state = *strstate;
        ft_change_agstate_2(ft_find_cstate(pstr->str[index->i], pstr->str[index->i + 1]), strstate);
        if (pstr->str[++index->i])
            ft_change_agstate_2(ft_find_cstate(pstr->str[index->i], pstr->str[index->i + 1]), strstate);
    }
    if ((*state == DQUOTE && pstr->str[index->i] == '\"') || (*state == QUOTE && pstr->str[index->i] == '\''))
    {
       *state = SEARCH;
        ft_change_agstate_2(ft_find_cstate(pstr->str[index->i], pstr->str[index->i + 1]), strstate);
        if (pstr->str[++index->i])
            ft_change_agstate_2(ft_find_cstate(pstr->str[index->i], pstr->str[index->i + 1]), strstate);
    }
    else if (pstr->str[index->i])
    {
        pstr->newstr = ft_realloc(pstr->newstr);
        pstr->newstr[index->j] = pstr->str[index->i];
        ft_change_agstate_2(ft_find_cstate(pstr->str[index->i], pstr->str[index->i + 1]), strstate);
        index->j++;
        index->i++;
    }
}
char *ft_parsing_end(char *str)
{
    arg_state   strstate;
    arg_state   state;
    t_parsend   pstr;
    t_index     index;


    index.i = 0;
    index.j = 0;
    state = SEARCH;
    strstate = SEARCH;
    pstr.newstr = NULL;
    pstr.str = str;
    if (str[index.i])
         ft_change_agstate_2(ft_find_cstate(str[0], str[1]), &strstate);
    while(str[index.i])
        ft_add_last_str(&strstate, &state, &index, &pstr);
    if(!pstr.newstr)
        return(free(str), ft_calloc(sizeof(char), 1));
    //else if (!ft_check_available(pstr.newstr)) !!NE PAS SUPPRIMER!!
        //return(free(str), free(pstr.newstr), ft_calloc(sizeof(char), 1));
    free(str);
    return (pstr.newstr);
}

void   ft_new_state(arg_state *strstate, char c)
{

    if(*strstate == SEARCH && c == '\'')
        *strstate = QUOTE;
    else if(*strstate == SEARCH && c == '\"')
        *strstate = DQUOTE;
    else if(*strstate == QUOTE && c == '\'')
        *strstate = SEARCH;
    else if(*strstate == DQUOTE && c == '\"')
        *strstate = SEARCH;
}

static void ft_save_state(t_tokens *tokens, int x)
{
    int i;
    int j;
    int k;
    int l;
    arg_state   strstate;
    arg_state   *tmpstate;

    i = 0;
    l = 0;
    k = 0;
    strstate = SEARCH;
    tokens[x].strstate = NULL;
    tmpstate = NULL;
    while(tokens[x].args && tokens[x].args[i])
    {
        j = 0;
        while(tokens[x].args[i][j])
        {
            ft_new_state(&strstate, tokens[x].args[i][j]);
            tmpstate = tokens[x].strstate;
            tokens[x].strstate = ft_calloc(sizeof(arg_state), k + 2);
            tokens[x].strstate[k] = strstate;
            while(tmpstate && tmpstate[l])
            {
                tokens[x].strstate[l] = tmpstate[l];
                l++;
            }
            l = 0;
            if (tmpstate)
                free(tmpstate);
            k++;
            j++;
        }
        i++;
    }
}

void    ft_last_parsing(t_tokens *tokens)
{
    int i;
    int j;
    char *tmp;
    char *tokentmp;

    i = 0;
    j = 0;
    tmp = NULL;
    tokentmp = NULL;
    ft_save_state(tokens, j);
    while (tokens[j].token)
    {    
        while(tokens[j].args[i])
        {
            tmp = ft_strjoin(tokentmp, tokens[j].args[i]);
            if (tokentmp)
                free(tokentmp);
            if (tokens[j].args[i + 1])
                tokentmp = ft_strjoin(tmp, " ");
            else
                tokentmp = ft_strdup(tmp);
            free(tmp);
            tokens[j].args[i] = ft_parsing_end(tokens[j].args[i]);
            i++;
        }
        i = 0;
        free(tokens[j].token);
        tokens[j].token = ft_strdup(tokentmp);
        free(tokentmp);
        tokentmp = NULL;
        j++;
    }
    
}
