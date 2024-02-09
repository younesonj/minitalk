/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younajja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 09:25:33 by younajja          #+#    #+#             */
/*   Updated: 2024/02/04 09:27:14 by younajja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	neg;
	int	res;

	res = 0;
	neg = 1;
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - 48);
		i++;
	}
	return (res * neg);
}

void	ft_send(int pid, char c)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if ((c & (1 << bit)) != 0)
		{
			if (kill(pid, SIGUSR1) == -1)
			{
				ft_printf("ERROR!\n");
				exit(1);
			}
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
			{
				ft_printf("ERROR!\n");
				exit(1);
			}
		}
		usleep(300);
		bit++;
	}
}

void	ft_confirmation(int sig)
{
	if (sig == SIGUSR1)
	{
		ft_printf(">>>>>>> The message was received successfully <<<<<<<<<\n");
		exit(0);
	}
	exit(1);
}

int	str_is_digit(char *str)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			j++;
		i++;
	}
	if (i == j)
		return (1);
	else
		return (0);
}

int	main(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac != 3)
	{
		ft_printf("PLease enter : ./client [server-pid] [message]\n");
		return (1);
	}
	if (str_is_digit(av[1]) == 0)
		return (1);
	signal(SIGUSR1, ft_confirmation);
	signal(SIGUSR2, ft_confirmation);
	while (av[2][i])
	{
		ft_send(ft_atoi(av[1]), av[2][i]);
		i++;
	}
	ft_send(ft_atoi(av[1]), '\0');
	while (1)
	{
		signal(SIGUSR1, ft_confirmation);
		signal(SIGUSR2, ft_confirmation);
	}
	return (0);
}
