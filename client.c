/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctremino <ctremino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 19:09:56 by ctremino          #+#    #+#             */
/*   Updated: 2024/11/12 13:49:29 by ctremino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

#include <string.h>  // Asegúrate de incluir esta cabecera


void    send_bit (int pid, char bit)
{

    if(bit == '0')
    {
        kill(pid, SIGUSR1); 
    }
    else 
    {
        kill(pid, SIGUSR2);
    }



}

void    send_character (int pid, char c)
{
    int i = 7; // bit mas significativo 

    while (i >= 0)
    {
        char bit = ( c >> i) & 1; // obtener bit
        
        if (bit)
            send_bit(pid, '1'); /*send_bit(pid, bit ? '1' : '0'); // enviar bit */
        else
            send_bit(pid, '0');
        usleep(100); // retraso para asegurar recepcion
        i --;
    }
    
}

void    send_string(int pid, const char *str)
{
    int index = 0;

    while(str[index] != '\0')
    {
        send_character(pid, str[index]);
        index ++;
    }
    if (str[index] == '\0')
        send_character(pid, str[index]);
}

int main (int argc, char **argv)
{
   int main(int argc, char **argv) {
    if (argc != 3) { 
        ft_printf("Uso: %s <PID_SERVIDOR> <mensaje>\n", argv[0]);
        return 1;
    }
    // Aquí continuarías con el resto de tu programa
    return 0;
}
     
    
    int server_pid = atoi(argv[1]);
    const char *message = argv[2];

    send_string(server_pid, message);
    send_bit(server_pid, '\0'); // enviar un carácter especial para indicar el final*/

    return 0;
}








/*#include "minitalk.c"


In the "client.c"  check list

file, you will...


Write a program (main) in which the client takes two parameters/arguments


The PID of the server to which it wants to send the message


A message


Encrypt the message (I did the encryption via bits)


Send the message to the server (via its PID)


Create a stop condition so that the server knows when it has finished receiving the message*/

