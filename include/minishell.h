#ifndef MINISHELL_H
# define  MINISHELL_H

#include "../libft/libft.h"
#include <stdio.h>  // Pour printf
#include <stdlib.h> // Pour malloc, free, getenv
#include <unistd.h> // Pour close, read, write, chdir, getcwd, access, dup, dup2, fork, execve, pipe, isatty, ttyname, ttyslot
#include <string.h> // Pour l'utilisation de certaines fonctions de manipulation de chaînes si nécessaire
#include <sys/stat.h> // Pour stat, lstat, fstat
#include <fcntl.h>    // Pour open
#include <dirent.h>   // Pour opendir, readdir, closedir
#include <errno.h>  // Pour errno utilisé avec perror et strerror
#include <signal.h> // Pour signal, sigaction, sigemptyset, sigaddset, kill
#include <readline/readline.h> // Pour readline, add_history
#include <readline/history.h>  // Pour rl_clear_history, et autres fonctions de gestion de l'historique de Readline
#include <termios.h>  // Pour tcsetattr, tcgetattr
#include <sys/ioctl.h> // Pour ioctl
#include <term.h>     // Pour tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
#include <sys/types.h>
#include <sys/wait.h>

# define DEF             "\001\e\033[0m\002"
# define RED             "\001\e\033[0;31m\002"
# define GREEN             "\001\e\033[0;32m\002"
# define YELLOW         "\001\e\033[0;33m\002"
# define BLUE             "\001\e\033[0;34m\002"
# define PURPLE         "\001\e\033[0;35m\002"
# define CYAN             "\001\e\033[0;36m\002"
# define WHITE             "\001\e\033[0;37m\002"
# define BOLD_RED         "\001\e\033[1;31m\002"
# define BOLD_GREEN     "\001\e\033[1;32m\002"
# define BOLD_YELLOW     "\001\e\033[1;33m\002"
# define BOLD_BLUE         "\001\e\033[1;34m\002"
# define BOLD_PURPLE     "\001\e\033[1;35m\002"
# define BOLD_CYAN         "\001\e\033[1;36m\002"
# define BOLD_WHITE     "\001\e\033[1;37m\002"
# define BOLD_BLACK     "\001\e\033[1;30m\002"
# define COLOR            "\001\e\033[38;2;255;153;153m\002"
# define BG_GREEN        "\001\e\033[48;2;0;200;0m\002"
# define BG_RED            "\001\e\033[48;2;200;70;0m\002"
# define FG_GREEN        "\001\e\033[38;2;0;200;0m\002"
# define FG_RED            "\001\e\033[38;2;200;70;0m\002"

extern int g_exit;

typedef enum    arg_state
{
    FSPACE,
    QUOTE,
    DQUOTE,
    DSPACE,
    SEARCH,
    OP,
}               arg_state;

typedef enum    e_flux
{
    IN,
    OUT,
    ERR,
    INIT,
    INOUT,
    ERRQ,
}               e_flux;

typedef struct  s_flux
{
    int savein;
    int saveout;
    int actualfd;
    e_flux    actualflux;
}               t_flux;

typedef struct  s_arg
{
    char        **args;
    char        *arg;
    int         strstate;
    arg_state   agstate;
}               t_arg;

typedef struct  s_index
{
    int i;
    int j;
    int k;
    int l;
}               t_index;

typedef struct  s_tokens
{
    char        *token;
    char        **args;
    arg_state   *strstate;
    int         nbtokens;
    int         pipefd[2];
}               t_tokens;

typedef struct s_var
{
    char    *newstr;
    char    *var;
    char    *tmp;
}               t_var;

typedef struct s_parsend
{
    char    *newstr;
    char    *str;
}               t_parsend;


// BUILTINS

void        ft_cd(char **args);
void        ft_echo(t_tokens token);
char        **ft_unset(char *varname, char **env);
char        **ft_export(char *var_to_create, char **var_tab);
long long    ft_exit(char **args);

// BUILTINS.UTILS

void    ft_check_env(char *str);
char    *ft_cutdir(char *path , char *arg);
char    *ft_get_env(char **env, char *var_name);

// BUILTINS.EXEC

char    **ft_create_env(char **envp);
char    **ft_tab_cat(char **tb, int pos);
int     ft_builtins_exec(t_tokens token, char ***env);

// EXPORT.C

void    ft_bubble_export(char **var_tab);
void    ft_swap_str(char **var_tab, int j);
void    ft_display_export(char **export_tab);
int     ft_check_var(char *var, char **var_tab);

// PARSING.UTILS

int     ft_change_agstate(arg_state cstate, arg_state *agstate, int j);
int     ft_find_arg(char *str, t_arg *arg, t_index *index);
int     ft_find_arg_2(char *str, t_arg *arg, t_index *index);
void    ft_joinarg(t_arg *arg, char *str, t_index *index);
void    ft_new_arg(t_arg *arg, t_index *index);
char    *ft_gnl(char *str);
char    *ft_join_space(char *s1, char *s2);
arg_state ft_find_cstate(char c, char next);

// PARSING.ENV

void    ft_vr(char **tb, char **env);
void    ft_last_parsing(t_tokens *tokens);
char    *ft_parsing_end( char *str);

// PARSING

char        *ft_print_prompt();
char        **ft_tokeniser(char *uprompt, char **env);
char        **ft_sort_uprompt(char *str);
char        **ft_sort_uprompt_2(char *str);
char        **ft_sort_token(char **tb);
t_tokens    *ft_receive_uprompt(char *uprompt, char **env);

// UTILS

void    ft_print_tokens(t_tokens *tokens);
void	ft_printtabtab(char **tb);
void	*ft_freetabtab(char **tb);
char	*ft_realloc(char *str);
char	**ft_tb_realloc(char **tb);

// EXEC

char    **ft_create_path(char *path, char *cmd);
void    ft_exec(char *cmd, char **arg, char **env);
void    ft_prompt_exec(t_tokens *tokens, t_index *index, char ***env, t_flux *brulux);
char    **ft_export_exec(char **args, char **env);

// FLUX

char    **ft_checkredirect(t_tokens *tokens, t_flux *flux, int j);
void    ft_change_flux(e_flux *brulux, int savein, int saveout);
arg_state ft_find_cstate_2(char c, char next);
int ft_change_agstate_2(arg_state cstate, arg_state *agstate);

#endif