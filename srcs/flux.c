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
        dup2(savein, STDIN_FILENO);
    if (*brulux == OUT || *brulux == INOUT)
        dup2(saveout, STDOUT_FILENO);
    *brulux = INIT;
}

static e_flux   ft_redirect_flux(char **args, t_index *index, t_flux *flux, int state)
{
    if (state == 0)
    {
        if (flux->actualflux == IN)
            flux->actualflux = INOUT;
        else if (flux->actualflux != INOUT)
            flux->actualflux = OUT;
        ft_redirect_output(&flux->actualfd , args, index->i);
    }
    else
    {
        if (flux->actualflux == OUT)
            flux->actualflux = INOUT;
        else if (flux->actualflux != INOUT)
            flux->actualflux = IN;
        ft_redirect_input(&flux->actualfd , args, index->i);
        if (flux->actualfd == -1)
            return(ERR);
    }
    return(IN);
    index->k = 1;
}

void    ft_write_err(int saveout, char *str)
{
    write(saveout, "bash: ", ft_strlen("bash: "));
    write(saveout, str, ft_strlen(str));
    write(saveout, ": No such file or directory\n", ft_strlen(": No such file or directory\n"));
}

/* char    **ft_checkredirect(char **args, t_flux *flux)
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
        {
            if (ft_redirect_flux(args, &index, flux, 1) == ERR)
                return (ft_write_err(flux->saveout, args[index.i + 1]), ft_freetabtab(args), ft_freetabtab(newargs), NULL);
        }
        else if (flux->actualflux == INIT && index.k == 0)
        {
            newargs = ft_tb_realloc(newargs);
            if (args[index.i][0])
                newargs[index.j++] = ft_strdup(args[index.i]);
            else
                newargs[index.j++] = ft_calloc(sizeof(char), 1);
        }
        index.i++;
    }
    return (ft_freetabtab(args), newargs);
} */

char    **ft_checkredirect(t_tokens *tokens, t_flux *flux)
{
    t_index index;
    char    **newargs;

    newargs = NULL;
    flux->actualflux = INIT;
    index.j = 0;
    index.i = 0;
    index.k = 0;
    while (tokens->args[index.i])
    {
        if (ft_strcmp(tokens->args[index.i], ">>") == 0 || tokens->args[index.i][0] == '>')
            ft_redirect_flux(tokens->args, &index, flux, 0);
        else if(tokens->args[index.i][0] == '<' || ft_strcmp(tokens->args[index.i], "<<") == 0)
        {
            if (ft_redirect_flux(tokens->args, &index, flux, 1) == ERR)
                return (ft_write_err(flux->saveout, tokens->args[index.i + 1]), ft_freetabtab(tokens->args), ft_freetabtab(newargs), NULL);
        }
        else if (flux->actualflux == INIT && index.k == 0)
        {
            newargs = ft_tb_realloc(newargs);
            if (tokens->args[index.i][0])
                newargs[index.j++] = ft_strdup(tokens->args[index.i]);
            else
                newargs[index.j++] = ft_calloc(sizeof(char), 1);
        }
        index.i++;
    }
    return (ft_freetabtab(tokens->args), newargs);
}
