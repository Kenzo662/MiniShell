#include "../include/minishell.h"

long long	ft_atoll(const char *str)
{
	int	i;
	long long   moins;
	long long	res;

	res = 0;
	moins = 1;
	i = 0;
	while ((str[i] < 14 && str[i] > 8) || str[i] == 32)
		i++;
	if (str[i] == '-')
	{
		moins = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (res * moins);
		else
			res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * moins);
}

int     ft_check_args_exit(char *arg)
{
    int i;

    i = 0;
    while (arg[i])
    {
        if (ft_isalpha(arg[i]) == 1)
            return (1);
        i++;
    }
    return (0);
}
long long    ft_exit(char **args)
{
    long long n;

    n = 0;
    if (!args[1])
        return (2);
    if (args[1] && !args[2])
    {
        if (ft_check_args_exit(args[1]) == 1)
            return (printf("exit: %s: numeric argument required\n", args[1]), 2); 
        else
        {
            n = ft_atoll(args[1]);
            n %= 256;
        }
    }
    else if (args[2])
    {
        printf("exit\nbash: exit: too many arguments\n");
        g_exit = 1;
        return (-1);
    }
    return (n);
}
