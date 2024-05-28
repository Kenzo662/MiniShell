#include "../include/minishell.h"

int main(int ac, char **av, char **envp)
{
    t_tokens    *tokens;
    t_index     index;
    char        **env;
    int         bexec;
    t_flux        brulux;

    brulux.actualfd = 0;
    brulux.saveout = dup(STDOUT_FILENO);
    brulux.savein = dup(STDIN_FILENO);
    (void)ac;
    (void)av;
    index.i = 0;
    bexec = 0;
    env = ft_create_env(envp);
    while (bexec != 2)
    {
        index.j = 0;
        tokens = ft_receive_uprompt(ft_print_prompt(), env);
        while(tokens[index.j].args)
        {
            tokens[index.j].args = ft_checkredirect(tokens[index.j].args, &brulux);
            if(ft_strcmp(tokens[index.j].args[0], "export") == 0)
                env = ft_export(tokens[index.j].args[1], env);
            else if (ft_strcmp(tokens[index.j].args[0], "unset") == 0)
                env = ft_unset(tokens[index.j].args[1], env);
            else
                bexec = ft_builtins_exec(tokens[index.j], env);
            ft_freetabtab(tokens[index.j].args);
            free(tokens->token);
            if (brulux.actualflux != INIT)
                ft_change_flux(&brulux.actualflux, brulux.savein, brulux.saveout);
            index.j++;
        }
        free(tokens);
    }
    ft_freetabtab(env);
    rl_clear_history();   
    return (0);
}


/* int main (void)
{
    int fd;

    fd = open("tester.txt", O_CREAT | O_WRONLY, 0777);
    printf("dup2 = %d\n" , dup2(fd, 1));

} */