#include "../include/minishell.h"

char    **ft_create_path(char *path, char *cmd)
{
    char    **tbpath;
    char    **tmppath;
    char    *tmp;
    int     i;
    int     j;

    tbpath = NULL;
    tmppath = ft_split(path, ':');
    i = 0;
    j = 1;
    tbpath = ft_tb_realloc(tbpath);
    tbpath[0] = ft_strdup(cmd);
    while (tmppath[i])
    {
        tbpath = ft_tb_realloc(tbpath);
        tmp = ft_strjoin(tmppath[i], "/");
        tbpath[j] = ft_strjoin(tmp, cmd);
        free(tmp);
        i++;
        j++;      
    }
    return (tbpath);
}

void ft_exec(char *cmd, char **arg, char **env)
{
    char    **path;
    pid_t   pid;
    int     execr;
    int     i;

    i = 0;
    execr = -1;
    path = ft_create_path(getenv("PATH"), cmd);
    pid = fork();
    if (pid == 0)
    {
        execr = execve(path[i], arg, env);
        while (execr == -1 && path[i])
        {
            execr = execve(path[i], arg, env);
            i++;
        }
        if (execr == -1)
            printf("Exec fail\n");
        else
            printf("EXEC OK\n");
        ft_freetabtab(path);
        ft_freetabtab(env);
        ft_freetabtab(arg);
        exit(0);
    }
    else
        ft_freetabtab(path);
    wait(&pid);
}
