/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctremino <ctremino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 18:36:13 by ctremino          #+#    #+#             */
/*   Updated: 2024/11/12 13:43:38 by ctremino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"


void    receive_bit(int signal)
{
    static unsigned char char_in_process = 0;
    static int bit_count = 0;
    
    if (signal == SIGUSR1)
        char_in_process = char_in_process << 1; // añade bit 0
    else if (signal == SIGUSR2)
        char_in_process = char_in_process << 1 | 1; // añade bit 1

    bit_count++;

    if (bit_count == 8) // si completa 8 bits imprime carácter y reinicia
    {
        if (char_in_process == '\0')
            write(1, "\n",1);
        else
        {
        write(1, &char_in_process, 1);
        }
        char_in_process = 0; // reinicia el caracter
        bit_count = 0; // reinicia el contador
    } 
}

/*int main(void)
{
    ft_printf("PID del servidor: %d\n",getpid());
    signal(SIGUSR1, receive_bit); // asigna manejo señal 
    signal(SIGUSR2, receive_bit);
    
    while(1)
    {
        pause();
    }
    return(0);
}*/
int main(void) {
    char pid_str[20]; // buffer para el PID convertido a string

    // Convertir el PID del servidor a cadena
    itoa(getpid(), pid_str);

    // Escribir el mensaje en STDERR
    write(STDERR_FILENO, "PID del servidor: ", 18);
    write(STDERR_FILENO, pid_str, sizeof(pid_str)); // Escribe el PID
    write(STDERR_FILENO, "\n", 1);

    // Configurar las señales
    signal(SIGUSR1, receive_bit);
    signal(SIGUSR2, receive_bit);
    
    // Bucle infinito para esperar las señales
    while (1) {
        pause(); // Espera a recibir una señal
    }

    return 0;
}