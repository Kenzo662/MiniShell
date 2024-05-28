#include "../include/minishell.h"


static e_flux ft_redirect_output(int *fd, char **args, int i)
{
    if (ft_strcmp(args[i], ">>") == 0)
    {
        *fd = open(args[i + 1], O_APPEND | O_WRONLY | O_CREAT, 0777);
        dup2(*fd, STDOUT_FILENO);
    }
    else if(args[i][0] == '>' && ft_strlen(args[i]) == 1)
    {
        *fd = open(args[i + 1], O_TRUNC | O_WRONLY | O_CREAT, 0777);
        dup2(*fd, STDOUT_FILENO);
    }
    return (OUT);
}

static e_flux    ft_redirect_input(int *fd, char **args, int i)
{
    if (ft_strcmp(args[i], "<<") == 0)
    {
        //AFAIRE//
    }
    else if(args[i][0] == '<' && ft_strlen(args[i]) == 1)
    {
        *fd = open(args[i + 1],  O_RDONLY);
        dup2(*fd, STDIN_FILENO);
    }
    return (IN);
}

void ft_change_flux(e_flux *brulux, int savein, int saveout)
{
    if (*brulux == IN || *brulux == INOUT)
        {dup2(savein, STDIN_FILENO);}
    if (*brulux == OUT || *brulux == INOUT)
        {dup2(saveout, STDOUT_FILENO);}
    *brulux = INIT;
}

static void    ft_redirect_flux(char **args, t_index *index, t_flux *flux, int state)
{
    if (state == 0)
    {     
        if (flux->actualflux == IN)
            flux->actualflux = INOUT;
        else 
            flux->actualflux = OUT;
        ft_redirect_output(&flux->actualfd , args, index->i);
    }
    else
    {
        if (flux->actualflux == OUT)
            flux->actualflux = INOUT;
        else
            flux->actualflux = IN;
        ft_redirect_input(&flux->actualfd , args, index->i);
    }
    index->k = 1;
}

char    **ft_checkredirect(char **args, t_flux *flux)
{
    t_index index;
    char    **newargs;

    newargs = NULL;
    flux->actualflux = INIT;
    index.j = 0;
    index.i = 0;
    index.k = 0;
    while (args[index.i])
    {
        if (ft_strcmp(args[index.i], ">>") == 0 || args[index.i][0] == '>')
            ft_redirect_flux(args, &index, flux, 0);
        else if(args[index.i][0] == '<' || ft_strcmp(args[index.i], "<<") == 0)
            ft_redirect_flux(args, &index, flux, 1);
        else if (flux->actualflux == INIT && index.k == 0)
        {
            newargs = ft_tb_realloc(newargs);
            newargs[index.j++] = ft_strdup(args[index.i]);
        }
        index.i++;
    }
    return (ft_freetabtab(args), newargs);
}
