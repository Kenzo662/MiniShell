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
        if (str[i] != '\'' && str[i] != '\"')
            j =1;
        i++;
    }
    return (j);
}
char *ft_parsing_end(char *str)
{
    arg_state   strstate;
    arg_state   state;
    char        *newstr;
    int         i;
    int         j;
    

    i = 0;
    j = 0;
    state = SEARCH;
    strstate = SEARCH;
    newstr = NULL;
    if (!ft_check_available(str))
        return (ft_calloc(sizeof(char), 1));
    if (str[i])
         ft_change_agstate(ft_find_cstate(str[0], str[1]), &strstate);
    while(str[i])
    {
        if (strstate == FSPACE)
            ft_change_agstate(ft_find_cstate(str[i], str[i + 1]), &strstate);
        if ((state == SEARCH) && (strstate == DQUOTE || strstate == QUOTE ))
        {
            state = strstate;
            i++;
            ft_change_agstate(ft_find_cstate(str[i], str[i + 1]), &strstate);
        }
        if ((state == DQUOTE && str[i] == '\"') || (state == QUOTE && str[i] == '\''))
        {
            state = SEARCH;
            i++;
            ft_change_agstate(ft_find_cstate(str[i], str[i + 1]), &strstate);
        }
        else
        {
            if (str[i])
            {   
                newstr = ft_realloc(newstr);
                newstr[j] = str[i];
            }
            ft_change_agstate(ft_find_cstate(str[i], str[i + 1]), &strstate);
            j++;
            i++;
        }
    }
    free(str);
    return (newstr);
}

char    **ft_last_parsing(char **tb)
{
    int i;

    i = 0;    
    while(tb[i])
    {
        tb[i] = ft_parsing_end(tb[i]);
        i++;
    }
    return (tb);
}