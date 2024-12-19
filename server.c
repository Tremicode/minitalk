/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctremino <ctremino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 18:36:13 by ctremino          #+#    #+#             */
/*   Updated: 2024/12/19 12:45:48 by ctremino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	receive_message(int sig, siginfo_t *info, void *context)
{
	static int bits_left = 8;     // Contador de bits restantes
	static char current_char = 0; // Carácter en construcción
	(void)info;    // No usamos este parámetro
	(void)context; // No usamos este parámetro
	// Si recibimos SIGUSR1, encendemos el bit correspondiente
	if (sig == SIGUSR1)
		current_char |= (1 << --bits_left);
	else
		bits_left--;
	// Cuando completamos los 8 bits, imprimimos el carácter
	if (bits_left == 0)
	{
		ft_putchar_fd(current_char, 1);
		bits_left = 8;    // Reiniciamos contador de bits
		current_char = 0; // Reiniciamos el carácter
	}
}
static void	initsig(void)
{
	struct sigaction	sa;

	// Configuramos la función que manejará las señales (receive_message)
	sa.sa_sigaction = receive_message;
	// Indicamos que queremos usar información adicional sobre la señal
	sa.sa_flags = SA_SIGINFO;
	// Limpiamos el conjunto de señales para no bloquear ninguna durante el manejo
	sigemptyset(&sa.sa_mask);
	// Registramos el manejador de señales para SIGUSR1
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		ft_putstr_fd("Error configuring SIGUSR1\n", 1);
		exit(EXIT_FAILURE);
	}
	// Registramos el manejador de señales para SIGUSR2
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
		ft_putstr_fd("wrong PID please try again! \n", 1);
		return (1);
	}
	initsig();
	write(1, "PID: ", 5);
	ft_putnbr_fd(process_pid, 1); // Imprime el valor del PID
	write(1, "\n", 1);
	while (1)
		pause();
	return (0);
}
