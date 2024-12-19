/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctremino <ctremino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:03:35 by ctremino          #+#    #+#             */
/*   Updated: 2024/12/19 14:37:22 by ctremino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_send_signal(pid_t pid, int sig)
{
	
	if (sig != SIGUSR1 && sig != SIGUSR2)
	{
		ft_putstr_fd("Error: wrong signal! Only SIGUSR1 and SIGUSR2 allowed.\n",
			1);
		exit(EXIT_FAILURE);
	}
	
	if (kill(pid, sig) == -1)
	{
		ft_putstr_fd("Error sending signal.\n", 1);
		exit(EXIT_FAILURE);
	}
}

static void	ft_send_message(pid_t pid, char *msg)
{
	unsigned char	current_char;
	int				bit_index;

	while (*msg)
	{
		current_char = *msg;
		bit_index = 7; 
		while (bit_index >= 0)
		{
			
			if (current_char & (1 << bit_index))
				ft_send_signal(pid, SIGUSR1);
			else
				ft_send_signal(pid, SIGUSR2);
			usleep(10000);	
			bit_index--;
		}
		msg++;
	}
	current_char = '\0';
	bit_index = 7;
	while (bit_index >= 0)
	{
		if (current_char & (1 << bit_index))
			ft_send_signal(pid, SIGUSR1);
		else
			ft_send_signal(pid, SIGUSR2);
		usleep(10000);
		bit_index--;
	}
}

int	main(int argc, char **argv)
{
	pid_t	process_pid;

	if (argc != 3)
	{
		write(1, "Wrong number of arguments, try again! \n", 37);
		return (1);
	}
	process_pid = atoi(argv[1]);
	if (process_pid <= 0)
	{
		write(1, "You are not getting a valid PID!\n", 32);
		return (1);
	}
	write(1, "PID: ", 5);
	ft_putnbr_fd(process_pid, 1);
	write(1, "\n", 1);
	ft_send_message(process_pid, argv[2]);
	return (0);
}
