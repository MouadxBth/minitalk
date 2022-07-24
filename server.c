/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouthai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 14:19:07 by mbouthai          #+#    #+#             */
/*   Updated: 2022/07/24 14:24:42 by mbouthai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_pid_current_sender = 0;

void	handler(int signum, siginfo_t *info, void *context)
{
	static char	character = 0xFF;
	static int	index;

	(void) context;
	if (g_pid_current_sender != info->si_pid)
	{
		g_pid_current_sender = info->si_pid;
		index = 0;
		character = 0xFF;
	}
	if (signum == SIGUSR1)
		character |= (0x80 >> index);
	else if (signum == SIGUSR2)
		character ^= (0x80 >> index);
	index++;
	if (index == 8)
	{
		index = 0;
		ft_putchar_fd(character, 1);
		character = 0xFF;
	}
}

int	main(void)
{
	int					pid;
	struct sigaction	action;
	sigset_t			mask;

	sigemptyset(&mask);
	sigaddset(&mask, SIGINT);
	sigaddset(&mask, SIGQUIT);
	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = handler;
	action.sa_mask = mask;
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	pid = getpid();
	ft_printf("Server enabled...\nPID: %i\n", pid);
	while (1)
		pause();
	return (0);
}
