#include "libft.h"

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