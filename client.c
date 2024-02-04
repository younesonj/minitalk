/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: younajja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 05:10:45 by younajja          #+#    #+#             */
/*   Updated: 2024/02/04 09:28:18 by younajja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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
	if (ac != 3)
	{
		ft_printf("PLease enter : ./client [server-pid] [message]\n");
		return (-1);
	}
	if (str_is_digit(av[1]) == 0)
		return (-1);
	ft_send(ft_atoi(av[1]), av[2]);
	return (0);
}
