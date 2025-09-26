# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgrandia <mgrandia@student.42barcelon      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/06 16:16:34 by mgrandia          #+#    #+#              #
#    Updated: 2025/09/21 15:49:23 by mgrandia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ─────────────────────────────────────────────────────────────
# CONFIGURACIÓN GENERAL
# ─────────────────────────────────────────────────────────────
NAME = philo 
CC = cc
AR = ar rcs
RM = rm -f
FLAGS = -Wall -Wextra -Werror -g #-fsanitize=address
# ─────────────────────────────────────────────────────────────
# COLORESSSSSS
# ─────────────────────────────────────────────────────────────
GREEN = \033[38;5;114m   
SLATE = \033[38;5;145m 
TEAL = \033[38;5;123m 
RED = \033[0;31m
RESET = \033[0m

# ─────────────────────────────────────────────────────────────
# DIRECTORIOS
# ─────────────────────────────────────────────────────────────
DIR_INC = includes/ 
DIR_OBJS = objs/
DIR_SRC = srcs/

# ─────────────────────────────────────────────────────────────
# ARCHIVOS
# ─────────────────────────────────────────────────────────────
SRC = main.c philo_utils.c initialization.c util_atoi.c\
	monitor.c eat.c

OBJS = $(addprefix $(DIR_OBJS), $(SRC:%.c=%.o))
DEP_FILES = $(OBJS:%.o=%.d)

# ─────────────────────────────────────────────────────────────
# REGLAS
# ─────────────────────────────────────────────────────────────

.PHONY: all clean fclean re

# ALL: primero construir 
all: $(NAME)

# Compilar philo, que depende de objetos 
$(NAME): $(DIR_OBJS) $(OBJS)
	@$(CC) $(FLAGS) $(OBJS) -lreadline -o $(NAME)
	@echo
	@echo "$(GREEN)✅ Ejecutable $(NAME) creado correctamente!$(RESET)"
	@echo

# Crear carpeta objs si no existe
$(DIR_OBJS):
	@echo "$(SLATE)🛠️  Creando carpeta de objetos...$(RESET)"
	@mkdir -p $(DIR_OBJS)

# Compilar los archivos .c en .o con generación de dependencias .d
$(DIR_OBJS)%.o: $(DIR_SRC)%.c Makefile includes/philo.h | $(DIR_OBJS)
	@echo "$(SLATE)⚙️  Compilando $< ...$(RESET)"
	@$(CC) $(FLAGS) -MD -I$(DIR_INC) -c $< -o $@

# Limpiar objetos
clean:
	@echo "$(SLATE)🧹 Limpiando objetos de philo...$(RESET)"
	@$(RM) -r $(DIR_OBJS)
	@echo "$(SLATE)✅ Objetos limpiados.$(RESET)"

# Limpiar todo incluyendo ejecutable y librería
fclean: clean
	@echo "$(SLATE)🗑️  Limpiando ejecutable...$(RESET)"
	@$(RM) $(NAME)
	@echo "$(SLATE)✅ Limpieza total completada.$(RESET)"

# Recompilación completa
re: fclean all
	@echo "$(SLATE)🎉 Recompilación completa!$(RESET)"

# Incluir dependencias automáticas
-include $(DEP_FILES)

