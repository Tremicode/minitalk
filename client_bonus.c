/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctremino <ctremino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 18:36:01 by ctremino          #+#    #+#             */
/*   Updated: 2024/12/18 19:22:58 by ctremino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minitalk.h"

#include "minitalk.h"

// Función para enviar señales al proceso del servidor
static void	ft_send_signal(pid_t pid, int sig)
{
	if (sig != SIGUSR1 && sig != SIGUSR2)
	{
		ft_putstr_fd("Error: wrong signal! Only SIGUSR1 and SIGUSR2 allowed.\n", 1);
		exit(EXIT_FAILURE);
	}
	if (kill(pid, sig) == -1)
	{
		ft_putstr_fd("Error sending signal.\n", 1);
		exit(EXIT_FAILURE);
	}
}

// Función para enviar el mensaje byte por byte al servidor
static void	ft_send_message(pid_t pid, char *msg)
{
	unsigned char	current_char;
	int				bit_index;

	while (*msg) // Iterar sobre cada carácter del mensaje
	{
		current_char = *msg;
		bit_index = 7; // Inicia desde el bit más significativo

		while (bit_index >= 0)
		{
			// Envía SIGUSR1 si el bit actual es 1, SIGUSR2 si es 0
			if (current_char & (1 << bit_index))
				ft_send_signal(pid, SIGUSR1);
			else
				ft_send_signal(pid, SIGUSR2);

			usleep(100); // Pequeña pausa entre señales para evitar conflictos
			bit_index--;
		}
		msg++;
	}

	// Enviar un carácter nulo ('\0') al final del mensaje para indicar el final
	bit_index = 7;
	while (bit_index >= 0)
	{
		ft_send_signal(pid, SIGUSR2); // Enviar bits de un carácter nulo
		usleep(100);
		bit_index--;
	}
}

int	main(int argc, char **argv)
{
	pid_t	server_pid;

	if (argc != 3)
	{
		ft_putstr_fd("Usage: ./client <server_pid> <message>\n", 1);
		return (1);
	}

	server_pid = atoi(argv[1]);
	if (server_pid <= 0)
	{
		ft_putstr_fd("Invalid PID.\n", 1);
		return (1);
	}

	ft_send_message(server_pid, argv[2]);
	ft_putstr_fd("Message sent successfully!\n", 1);
	return (0);
}



