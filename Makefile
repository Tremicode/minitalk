# Variables
NAME_CLIENT = client
NAME_SERVER = server
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Directorio de cabeceras para el .h
HEADER_DIR = ./includes

# Archivos fuente
SRC_CLIENT = client.c
SRC_SERVER = server.c

# Archivos objeto
OBJ_CLIENT = $(SRC_CLIENT:.c=.o)
OBJ_SERVER = $(SRC_SERVER:.c=.o)

# Directorio de cabeceras para la compilacion
CFLAGS += -I $(HEADER_DIR)

# Compilación del cliente
$(NAME_CLIENT): $(OBJ_CLIENT)
	$(CC) $(CFLAGS) -o $(NAME_CLIENT) $(OBJ_CLIENT)

# Compilación del servidor
$(NAME_SERVER): $(OBJ_SERVER)
	$(CC) $(CFLAGS) -o $(NAME_SERVER) $(OBJ_SERVER)

# Compilación completa
all: $(NAME_CLIENT) $(NAME_SERVER)

# Limpia archivos objeto
clean:
	@rm -f $(OBJ_CLIENT) $(OBJ_SERVER)

# Limpia archivos objeto y ejecutables
fclean: clean
	@rm -f $(NAME_CLIENT) $(NAME_SERVER)

# Reconstrucción completa
re: fclean all

# Reglas de archivos
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean fclean re
