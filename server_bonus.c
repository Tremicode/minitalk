/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctremino <ctremino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 18:36:07 by ctremino          #+#    #+#             */
/*   Updated: 2024/12/18 19:23:21 by ctremino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	receive_message(int sig, siginfo_t *info, void *context)
{
	static int	n_bit = 7;            // Número de bits restantes por recibir
	static char	buffer_char = 0;      // Caracter temporal en construcción
	static pid_t	client_pid = 0;    // PID del cliente que envió la señal

	(void)context;

	// Obtener el PID del cliente que envía la señal
	if (!client_pid)
		client_pid = info->si_pid;

	// Construir el carácter bit por bit
	if (sig == SIGUSR1)
		buffer_char |= (1 << n_bit); // Si SIGUSR1, asigna 1 al bit actual
	n_bit--;

	// Si se completaron 8 bits, procesar el carácter completo
	if (n_bit < 0)
	{
		if (buffer_char == '\0') // Si el carácter recibido es nulo ('\0')
		{
			ft_putstr_fd("\nMessage received successfully!\n", 1);
			kill(client_pid, SIGUSR1); // Confirmar recepción al cliente
			client_pid = 0;           // Resetear el PID del cliente
		}
		else
		{
			ft_putchar_fd(buffer_char, 1); // Imprimir el carácter recibido
			kill(client_pid, SIGUSR1);     // Confirmar recepción al cliente
		}

		// Resetear el buffer para el siguiente carácter
		buffer_char = 0;
		n_bit = 7;
	}
}

int	main(void)
{
	struct sigaction	sa;

	// Configurar la acción del manejador de señales
	sa.sa_sigaction = receive_message;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);

	// Registrar los manejadores de SIGUSR1 y SIGUSR2
	if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_putstr_fd("Error setting up signal handlers.\n", 1);
		return (1);
	}

	// Mostrar el PID del servidor
	ft_putstr_fd("Server PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putstr_fd("\n", 1);

	// Mantener el servidor corriendo
	while (1)
		pause();

	return (0);
}
