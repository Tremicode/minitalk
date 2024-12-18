/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctremino <ctremino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:03:35 by ctremino          #+#    #+#             */
/*   Updated: 2024/12/18 21:56:45 by ctremino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_send_signal(pid_t pid, int sig)
{
	// (only SIGUSR1 y SIGUSR2)
	if (sig != SIGUSR1 && sig != SIGUSR2)
	{
		ft_putstr_fd("Error: wrong singnal!!. only SIGUSR1 and SIGUSR2 allowed.\n",
			1);
		exit(EXIT_FAILURE);
	}
	// Intentar enviar la señal al proceso
	if (kill(pid, sig) == -1)
	{
		ft_putstr_fd("Error al intentar enviar la señal.\n", 1);
		exit(EXIT_FAILURE);
	}
}
static void ft_send_message(pid_t pid, char *msg)
{
    unsigned char current_char; 
    int bit_index; // Índice de los bits dentro del carácter (de 7 a 0)

    
    while (*msg)
    {
        current_char = *msg; 
        bit_index = 7; // start bit más significativo (más a la izquierda)

        // Enviamos 1 bit a la vez, de izquierda a derecha
        while (bit_index >= 0)
        {
            // Comprobamos  el bit actual del carácter es 1 o 0
            if (current_char & (1 << bit_index))
                ft_send_signal(pid, SIGUSR1); // Si el bit es 1, SIGUSR1
            else
                ft_send_signal(pid, SIGUSR2); // Si el bit es 0,  SIGUSR2

            usleep(1000); 

            bit_index--; // (de izq a derecha)
        }

        msg++; 
    }
}



int	main(int argc, char **argv)
{
	pid_t	process_pid;

	
	if (argc != 3)
	{
		write(1, "Wrong number of arguments, try again!\n", 37);
		return (1);
	}
	// Convierte el PID de string a int usando atoi
	process_pid = atoi(argv[1]);
	// PID tiene que ser un valor positivo (no puede ser cero o negativo)
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
