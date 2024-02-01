/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younajja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 05:10:45 by younajja          #+#    #+#             */
/*   Updated: 2024/01/31 05:14:12 by younajja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

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

void	ft_send(int pid, char *str)
{
	int	bit;
	int	i;

	i = 0;
	while (str[i])
		i++;
	str[i] = '\n';
	str[i + 1] = '\0';
	i = 0;
	while (str[i] != '\0')
	{
		bit = 0;
		while (bit < 8)
		{
			if ((str[i] & (1 << bit)) != 0)
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
	ft_printf("./client [server-pid] [message]\n");
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
