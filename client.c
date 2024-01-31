#include <stdio.h>
#include <unistd.h>
#include <signal.h>

static int	ft_atoi(const char *str)
{
	int					i;
	int					sign;
	unsigned long int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result += str[i] - 48;
		i++;
	}
	return (result * sign);
}

void	ft_send(int pid, char *str)
{
	int	bit;
	int i = 0;

	while (str[i])
		i++;
	
	str[i] = '\n';
	str[i+1] = '\0';
	i = 0;
	while (str[i])
	{
		bit = 0;
		while (bit < 8)
		{
			
			if ((str[i] & (0x01 << bit)))
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			usleep(500);
			bit++;
		}
		i++;
	}

}

void	ft_error(void)
{
	printf("./client [server-pid] [message]\n");
	exit(0);
}

int	main(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac != 3)
		ft_error();
	ft_send(ft_atoi(av[1]), av[2]);
	return (0);
}
