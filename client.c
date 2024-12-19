/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctremino <ctremino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:03:35 by ctremino          #+#    #+#             */
/*   Updated: 2024/12/19 13:56:36 by ctremino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_send_signal(pid_t pid, int sig)
{
	// Solo SIGUSR1 y SIGUSR2 están permitidos
	if (sig != SIGUSR1 && sig != SIGUSR2)
	{
		ft_putstr_fd("Error: wrong signal! Only SIGUSR1 and SIGUSR2 allowed.\n", 1);
		exit(EXIT_FAILURE);
	}
	// Intentar enviar la señal al proceso
	if (kill(pid, sig) == -1)
	{
		ft_putstr_fd("Error sending signal.\n", 1);
		exit(EXIT_FAILURE);
	}
}

static void	ft_send_message(pid_t pid, char *msg)
{
	unsigned char	current_char;
	int bit_index;

	// Mientras haya caracteres en el mensaje
	while (*msg)
	{
		current_char = *msg;
		bit_index = 7; // Iniciar desde el bit más significativo (izquierda)

		// Enviar los bits de 8 bits de un carácter
		while (bit_index >= 0)
		{
			// Si el bit está en 1, enviar SIGUSR1, si está en 0, SIGUSR2
			if (current_char & (1 << bit_index))
				ft_send_signal(pid, SIGUSR1);
			else
				ft_send_signal(pid, SIGUSR2);
			usleep(10000); // Aumentar el delay para asegurar que las señales se procesen correctamente
			bit_index--; // Mover al siguiente bit
		}
		msg++;
	}

	// Enviar un caracter '\0' al final del mensaje para indicar su final
	current_char = '\0';
	bit_index = 7;
	while (bit_index >= 0)
	{
		if (current_char & (1 << bit_index))
			ft_send_signal(pid, SIGUSR1);
		else
			ft_send_signal(pid, SIGUSR2);
		usleep(10000); // Mismo retraso para la señal de fin de mensaje
		bit_index--;
	}
}

int	main(int argc, char **argv)
{
	pid_t	process_pid;

	// Comprobar número correcto de argumentos
	if (argc != 3)
	{
		write(1, "Wrong number of arguments, try again! \n", 37);
		return (1);
	}

	// Convierte el PID de string a int usando atoi
	process_pid = atoi(argv[1]);
	// Comprobar si el PID es válido (debe ser positivo)
	if (process_pid <= 0)
	{
		write(1, "You are not getting a valid PID!\n", 32);
		return (1);
	}

	write(1, "PID: ", 5);
	ft_putnbr_fd(process_pid, 1); // Imprime el valor del PID
	write(1, "\n", 1);

	// Llama a la función send_msg para enviar el mensaje
	ft_send_message(process_pid, argv[2]);
	return (0);
}

