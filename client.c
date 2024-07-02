/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aohssine <aohssine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 11:42:29 by aohssine          #+#    #+#             */
/*   Updated: 2024/07/01 10:24:51 by aohssine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	space_sign(const char *s, int *sign)
{
	int	i;

	i = 0;
	while (s[i] && (s[i] == ' ' || (s[i] < 14 && s[i] > 8)))
		i++;
	if (s[i] && (s[i] == '-' || s[i] == '+'))
	{
		if (s[i] == '-')
			*sign *= (-1);
		i++;
	}
	return (i);
}

int	ft_atoi(const char *str)
{
	int					i;
	int					sign;
	unsigned long long	result;
	unsigned long long	temp;

	result = 0;
	sign = 1;
	i = space_sign(str, &sign);
	while (str[i] <= '9' && str[i] >= '0')
	{
		temp = result;
		result = result * 10 + str[i] - 48;
		if (temp != result / 10 && sign == -1)
			return (0);
		else if (temp != result / 10 && sign == 1)
			return (-1);
		i++;
	}
	return ((int)result * sign);
}

int	check_pid(char *c_pid)
{
	int	i;

	i = -1;
	if (c_pid[0] && c_pid[0] == '-')
		return (-1);
	while (c_pid[++i])
	{
		if (c_pid[i] < '0' || c_pid[i] > '9')
			return (-1);
	}
	return (0);
}

int	convert_char(char *pid, char *msg)
{
	int	counter;
	int	count_bit;

	counter = 0;
	while (msg[counter] != '\0')
	{
		count_bit = 7;
		while (count_bit >= 0)
		{
			if (1 & (msg[counter] >> count_bit))
			{
				kill(ft_atoi(pid), SIGUSR2);
				usleep(400);
			}
			else
			{
				kill(ft_atoi(pid), SIGUSR1);
				usleep(400);
			}
			count_bit--;
		}
		counter++;
	}
	return (0);
}

int	main(int ac, char *av[])
{
	if (ac == 3)
	{
		if (check_pid(av[1]) == -1)
			return (0);
		convert_char(av[1], av[2]);
	}
	return (0);
}
