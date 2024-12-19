/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctremino <ctremino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 18:36:13 by ctremino          #+#    #+#             */
/*   Updated: 2024/12/19 14:31:42 by ctremino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	handle_message(char current_char, char **message, int *length)
{
	char	*new_message;

	new_message = malloc(*length + 2);
	if (!new_message)
		exit(EXIT_FAILURE);
	if (*message)
		memcpy(new_message, *message, *length);
	new_message[*length] = current_char;
	new_message[++(*length)] = '\0';
	free(*message);
	*message = new_message;
}

static void	receive_message(int sig, siginfo_t *info, void *context)
{
	static int	bits_left = 8;
	static char	current_char = 0;
	static char	*message = NULL;
	static int	length = 0;

	(void)info;
	(void)context;
	if (sig == SIGUSR1)
		current_char |= (1 << --bits_left);
	else
		bits_left--;
	if (bits_left == 0)
	{
		if (current_char == '\0')
		{
			write(1, message, length);
			free(message);
			message = NULL;
			length = 0;
		}
		else
			handle_message(current_char, &message, &length);
		current_char = 0;
		bits_left = 8;
	}
}

static void	initsig(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = receive_message;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		ft_putstr_fd("Error configuring SIGUSR1\n", 1);
		exit(EXIT_FAILURE);
	}
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_putstr_fd("Error configuring SIGUSR2\n", 1);
		exit(EXIT_FAILURE);
	}
}

int	main(void)
{
	pid_t	process_pid;

	process_pid = getpid();
	if (process_pid <= 0)
	{
		ft_putstr_fd("Error: Invalid PID\n", 1);
		return (1);
	}
	initsig();
	write(1, "PID: ", 5);
	ft_putnbr_fd(process_pid, 1);
	write(1, "\n", 1);
	while (1)
		pause();
	return (0);
}
