#include "../include/minishell.h"

void    ft_cd(char **args)
{
    char    *path;
    char    buff[4096];

    path = getcwd(buff, 4096);
    chdir(ft_cutdir(path, args[1]));
}

void     ft_echo(t_tokens token)
{
    int i;

    i = 1;
    if (ft_strcmp(token.args[1], "-n") == 0)
        i++;
    while (token.args[i])
    {
        
        printf("%s", token.args[i]);
        i++;
        if (token.args[i] != NULL)
            printf(" ");
    }
    if (ft_strcmp(token.args[1], "-n") != 0)
        printf("\n");
}

char   **ft_unset(char *varname, char **env)
{
    int pos;

    pos = ft_check_var(varname, env);
    if (pos != 0)
        env = ft_tab_cat(env, pos);
    return (env);
}