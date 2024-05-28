#include "../include/minishell.h"

char    **ft_export(char *var_to_create, char **var_tab)
{
    int     i;
    int     pos;

    var_tab = ft_tb_realloc(var_tab);
    i = 0;
    if (!var_to_create)
        return(ft_bubble_export(var_tab), var_tab);
    if (ft_strchr(var_to_create, '=') == NULL)
        return (var_tab);
    if (ft_check_var(var_to_create, var_tab) != 0)
    {
        pos = ft_check_var(var_to_create, var_tab);
        free(var_tab[pos]);
        var_tab[pos] = ft_strdup(var_to_create);
        return (var_tab);
    }
    while(var_tab[i])
        i++;
    var_tab[i] = ft_strdup(var_to_create);
    return(var_tab);
}

int     ft_check_var(char *var, char **var_tab)
{
    int i;
    char    **tmp;
    char    **tmp2;
    
    i = 0;
    tmp = ft_split(var, '=');
    while(var_tab[i])
    {
        tmp2 = ft_split(var_tab[i], '=');
        if (ft_strcmp(tmp[0], tmp2[0]) == 0)
            return (ft_freetabtab(tmp), ft_freetabtab(tmp2), i);
        ft_freetabtab(tmp2);
        i++;
    }
    ft_freetabtab(tmp);
    tmp = NULL;
    tmp2 = NULL;
    return (0);
}

void    ft_bubble_export(char **var_tab)
{
    int i;
    int j;
    int len;
    char    **export_env;

    i = 0;
    j = 0;
    len = 0;
    export_env = ft_create_env(var_tab);
    while (var_tab[len])
        len++;
    i = 0;
    while (i < len - 1)
    {
        j = 0;
        while (j < len - 1)
        {
            if (export_env[j][0] > export_env[j + 1][0])
                ft_swap_str(export_env, j);
            j++;
        }
        i++;
    }
    ft_display_export(export_env);
    ft_freetabtab(export_env);
}

void    ft_swap_str(char **var_tab, int j)
{
    char *tmp;

    tmp = var_tab[j];
    var_tab[j] = var_tab[j + 1];
    var_tab[j + 1] = tmp;
}

void    ft_display_export(char **export_tab)
{
    int i;

    i = -1;
    while (export_tab[++i])
        printf("declare -x %s\n", export_tab[i]);
}