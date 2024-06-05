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
        while(tokens[index.j].token)
        {
            if (tokens[index.j + 1].token)
            {
                pipe(tokens[index.j].pipefd);
                dup2(tokens[index.j].pipefd[1], STDOUT_FILENO);
                close(tokens[index.j].pipefd[1]);
            }
            else if (!tokens[index.j + 1].token && index.j > 0)
                dup2(brulux.saveout, STDOUT_FILENO);
            ft_prompt_exec(tokens, &index, env, &brulux);
            if (tokens[index.j + 1].token)
            {
                dup2(tokens[index.j].pipefd[0], STDIN_FILENO);
                close(tokens[index.j].pipefd[0]);
            }
            else if (!tokens[index.j + 1].token && index.j > 0)
                dup2(brulux.savein, STDIN_FILENO);
            index.j++;
        }
        free(tokens);
    } 
    ft_freetabtab(*env);
    free(env);
    rl_clear_history();
    return (index.k);
}
