/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aohssine <aohssine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 11:42:26 by aohssine          #+#    #+#             */
/*   Updated: 2024/07/01 09:46:46 by aohssine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	put_nbr(int nbr)
{
	char	digits[12];
	int		counter;

	counter = -1;
	if (nbr == 0)
		write(1, &"0", 1);
	while (nbr)
	{
		digits[++counter] = nbr % 10 + 48;
		nbr = nbr / 10;
	}
	digits[++counter] = '\0';
	while (counter > -1)
		write(1, &digits[counter--], 1);
	write(1, &"\n", 1);
	return ;
}

void	print_char(int sig, siginfo_t *info, void *context)
{
	static int				bit_counter = 0;
	static unsigned char	byte = 0;
	static int				c_pid = 0;

	(void)context;
	if (c_pid != info->si_pid)
	{
		byte = 0;
		bit_counter = 0;
	}
	c_pid = info->si_pid;
	byte = byte << 1;
	if (sig == SIGUSR2)
		byte = byte | 1;
	bit_counter++;
	if (bit_counter == 8)
	{
		write(1, &byte, 1);
		byte = 0;
		bit_counter = 0;
	}
}

int	main(void)
{
	int					pid;
	struct sigaction	sa;

	sa.sa_sigaction = &print_char;
	pid = getpid();
	put_nbr(pid);
	while (1)
	{
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
	}
	return (0);
}
