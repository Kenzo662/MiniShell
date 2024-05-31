#include "../include/minishell.h"

int    ft_builtins_exec(t_tokens token, char ***env)
{
    char    buf[4096];

    if (!token.args[0] || !token.args[0][0])
        return (0);
    if (ft_strcmp(token.args[0], "cd") == 0)
        return (ft_cd(token.args), 0);
    else if (ft_strcmp(token.args[0], "echo") == 0)
        return (ft_echo(token), 0);
    else if (ft_strcmp(token.args[0], "pwd") == 0)
        return (printf("%s\n", getcwd(buf, 4096)), 0);
    else if (ft_strcmp(token.args[0], "env") == 0)
        return (ft_printtabtab(*env), 0);
    else if (ft_strcmp(token.args[0], "exit") == 0)
        return (2);
    else
        return (ft_exec(token.args[0], token.args, *env), 0);
    return (1);
}

char    **ft_create_env(char **envp)
{
    char    **env;
    int     i;

    i = 0;
    env = NULL;
    while (envp[i])
        i++;
    env = ft_calloc(i + 1, sizeof(char *));
    i = -1;
    while (envp[++i])
        env[i] = ft_strdup(envp[i]);
    env[i] = NULL;
    return (env);
}

char    **ft_tab_cat(char **tb, int pos)
{
    char    **newenv;
    int     i;
    int     j;
    int     len;

    i = 0;
    while (tb[i])
        i++;
    len = i;
    newenv = ft_calloc(i, sizeof(char *));
    i = 0;
    j = 0;
    while (i < len)
    {
        if (i != pos)
        {
            newenv[j] = ft_strdup(tb[i]);
            j++;
        }
        i++;
    }
    ft_freetabtab(tb);
    return (newenv);
}

char    **ft_export_exec(char **args, char **env)
{
    int i;

    i = 0;
    if (!args[1])
        env = ft_export(NULL, env);
    while (args[++i])
        env = ft_export(args[i], env);
    return (env);
}