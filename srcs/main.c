#include "../include/minishell.h"

int g_exit;

int main(int ac, char **av, char **envp)
{
    t_tokens    *tokens;
    t_index     index;
    char        ***env;
    char        *cleararg[] = {"clear", NULL};
    t_flux      brulux;

    brulux.actualfd = 0;
    brulux.saveout = dup(STDOUT_FILENO);
    brulux.savein = dup(STDIN_FILENO);
    (void)ac;
    (void)av;
    index.i = 0;
    index.k = -1;
    env = ft_calloc(sizeof(char **), 1);
    *env = ft_create_env(envp);
    ft_exec("clear", cleararg, *env);
    while (index.k < 0)
    {
        index.j = 0;
        tokens = ft_receive_uprompt(ft_print_prompt(), *env);
        while(tokens[index.j].args)
            ft_prompt_exec(tokens, &index, env, &brulux);
        free(tokens);
    } 
    ft_freetabtab(*env);
    free(env);
    rl_clear_history();
    return (0);
}
