#include "../include/minishell.h"

int main(int ac, char **av, char **envp)
{
    t_tokens    *tokens;
    t_index     index;
    char        **env;

    (void)ac;
    (void)av;
    index.i = 0;
    env = ft_create_env(envp);
    while (index.i++ != 10)
    {
        index.j = 0;
        tokens = ft_receive_uprompt(ft_print_prompt(), env);
        while(tokens[index.j].args)
        {
            if(ft_strcmp(tokens[index.j].args[0], "export") == 0)
                env = ft_create_var(tokens[index.j].args[1], env);
            else if (ft_strcmp(tokens[index.j].args[0], "unset") == 0)
                env = ft_unset(tokens[index.j].args[1], env);
            else
                ft_builtins_exec(tokens[index.j], env);
            ft_freetabtab(tokens[index.j].args);
            index.j++;
        }
        free(tokens);
    }
    ft_freetabtab(env);
    rl_clear_history();
    return (0);
} 