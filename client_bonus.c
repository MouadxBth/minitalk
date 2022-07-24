/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouthai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 14:25:09 by mbouthai          #+#    #+#             */
/*   Updated: 2022/07/24 14:25:11 by mbouthai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	message_status(int sig)
{
	ft_printf("Recieved signal with the ID: %i\n", sig);
}

void	send_byte(int byte, int pid)
{
	int	shift;

	shift = 0;
	while (shift < 8)
	{
		if (byte & (128 >> shift))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		shift++;
		usleep(500);
	}
}

void	send_buffer(int pid, char *buffer)
{
	int	index;

	if (!buffer)
		return ;
	index = -1;
	while (buffer[++index])
		send_byte(buffer[index], pid);
	if (!buffer[index])
		send_byte(buffer[index], pid);
}

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		ft_printf("Error! 2 arguments are required!\n[PID] [MESSAGE]\n");
		return (-1);
	}
	signal(SIGUSR1, message_status);
	send_buffer(ft_atoi(argv[1]), argv[2]);
	return (0);
}
