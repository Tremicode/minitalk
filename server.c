/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctremino <ctremino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 18:36:13 by ctremino          #+#    #+#             */
/*   Updated: 2024/12/19 00:00:33 by ctremino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	receive_message(int sig, siginfo_t *info, void *contest)
{
	static int	n_bit = 8;
	static char	buffer_char;

	n_bit--;
	(void)contest;
	(void)info;
	if (sig == SIGUSR1)
		buffer_char |= (1 << n_bit);
	if (n_bit == 0)
	{
		ft_putchar_fd(buffer_char, 1);
		buffer_char = 0;
		n_bit = 8;
	}
}

static void	initsig(void)
{
	struct sigaction	start_signal;

	// Init la estructura sigaction
	start_signal.sa_sigaction = receive_message;
	// Establecemos la función que manejará las señales
	start_signal.sa_flags = SA_SIGINFO;
	// Indicamos que queremos información adicional sobre la señal
	// Limpiamos la máscara de señales (no bloquea ninguna señal por defecto)
	sigemptyset(&start_signal.sa_mask);
	// Agregamos SIGUSR1 y SIGUSR2 a la máscara de señales
	// Esto bloqueará esas señales mientras se esté manejando cualquier otra
	sigaddset(&start_signal.sa_mask, SIGUSR1);
	sigaddset(&start_signal.sa_mask, SIGUSR2);
	// Registramos el manejador para SIGUSR1
	if (sigaction(SIGUSR1, &start_signal, NULL) == -1)
	{
		ft_putstr_fd("Error: Unable to handle SIGUSR1\n", 1);
		exit(EXIT_FAILURE);
	}
	// Registramos el manejador para SIGUSR2
	if (sigaction(SIGUSR2, &start_signal, NULL) == -1)
	{
		ft_putstr_fd("Error: Unable to handle SIGUSR2\n", 1);
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




