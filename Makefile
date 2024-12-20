# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ctremino <ctremino@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/20 17:21:36 by ctremino          #+#    #+#              #
#    Updated: 2024/12/20 17:49:20 by ctremino         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAG = -Werror -Wall -Wextra
LIBFT = ./libft/libft.a
CFILE_CLIENT = client.c
CFILE_SERVER = server.c
OFILE_CLIENT = client.o
OFILE_SERVER = server.o
CLIENT = client
SERVER = server


all: $(LIBFT) $(CLIENT) $(SERVER)


$(LIBFT):
	$(MAKE) -C ./libft


$(CLIENT): $(OFILE_CLIENT)
	gcc $(FLAG) -o $(CLIENT) $^ $(LIBFT)

$(SERVER): $(OFILE_SERVER)
	gcc $(FLAG) -o $(SERVER) $^ $(LIBFT)


%.o : %.c
	gcc $(FLAG) -c $< -o $@


clean:
	$(MAKE) clean -C ./libft
	rm -rf $(OFILE_CLIENT) $(OFILE_SERVER)

fclean: clean
	$(MAKE) fclean -C ./libft
	rm -f $(CLIENT) $(SERVER)


re: fclean all

.PHONY: all clean fclean re
