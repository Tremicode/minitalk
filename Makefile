# Flags y nombres
FLAG = -Werror -Wall -Wextra
LIBFT = ./libft/libft.a
CFILE_CLIENT = client.c
CFILE_SERVER = server.c
CFILE_C_BONUS = client_bonus.c
CFILE_S_BONUS = server_bonus.c
OFILE_CLIENT = client.o
OFILE_SERVER = server.o
OFILE_C_BONUS = client_bonus.o
OFILE_S_BONUS = server_bonus.o
CLIENT = client
SERVER = server
CLIENT_BONUS = client_bonus
SERVER_BONUS = server_bonus

# Objetivo principal
all: $(LIBFT) $(CLIENT) $(SERVER)

# Compilación de la librería libft
$(LIBFT):
	$(MAKE) -C ./libft

# Compilación del cliente y servidor
$(CLIENT): $(OFILE_CLIENT)
	gcc $(FLAG) -o $(CLIENT) $^ $(LIBFT)

$(SERVER): $(OFILE_SERVER)
	gcc $(FLAG) -o $(SERVER) $^ $(LIBFT)

# Regla general para generar archivos .o
%.o : %.c
	gcc $(FLAG) -c $< -o $@

# Objetivo para bonus
bonus: $(LIBFT) $(CLIENT_BONUS) $(SERVER_BONUS)

# Compilación del cliente_bonus
$(CLIENT_BONUS): $(OFILE_C_BONUS)
	gcc $(FLAG) -o $(CLIENT_BONUS) $^ $(LIBFT)

# Compilación del servidor_bonus
$(SERVER_BONUS): $(OFILE_S_BONUS)
	gcc $(FLAG) -o $(SERVER_BONUS) $^ $(LIBFT)

# Limpieza de archivos objeto y binarios
clean:
	$(MAKE) clean -C ./libft
	rm -rf $(OFILE_CLIENT) $(OFILE_SERVER) $(OFILE_C_BONUS) $(OFILE_S_BONUS)

fclean: clean
	$(MAKE) fclean -C ./libft
	rm -f $(CLIENT) $(SERVER) $(CLIENT_BONUS) $(SERVER_BONUS)

# Regenerar todo
re: fclean all

.PHONY: all clean fclean re bonus
