# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/23 15:54:50 by jveirman          #+#    #+#              #
#    Updated: 2024/06/07 15:58:53 by jveirman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#===================================================================#
#								SETTINGS							#
#===================================================================#

NAME			=	minishell

#-----------------				COMPILING			----------------#
CC				=	cc
OUT				=	-o $(NAME)
CFLAGS			=	-Wall -Wextra -Werror -I./includes -I ~/.brew/opt/readline/include
CFLAGS_DEV		=	-Wall -Wextra -Werror -I./includes -I ~/.brew/opt/readline/include -fsanitize=address -g
LDFLAGS			=	-L ~/.brew/opt/readline/lib -lreadline

RM				=	rm -rf

#-----------------				ASSETS				----------------#
LIBFT			=	./libft/libft.a

#-----------------				DIRECTORIES			----------------#
BUILD_DIR		:=	./build
SRC_DIR			:=	./sources
SRC_DEV_DIR			:=	$(SRC_DIR)/dev_tool
SRC_EXEC_DIR	:=	$(SRC_DIR)/exec
SRC_SHELL_DIR	:=	$(SRC_DIR)/shell
SRC_SIGNAL_DIR	:=	$(SRC_DIR)/signal
SRC_BUILT_DIR	:=	$(SRC_DIR)/built_in

#-----------------				SOURCES				----------------#
SRCS_DEV		=	$(SRC_DEV_DIR)/fake_array_from_parsing.c \
					$(SRC_DEV_DIR)/command_call.c 
SRCS_SHELL		=	$(SRC_SHELL_DIR)/main.c \
					$(SRC_SHELL_DIR)/prompt.c \
					$(SRC_SHELL_DIR)/exit.c \
					$(SRC_SHELL_DIR)/env_utils.c
SRCS_EXEC		=	$(SRC_EXEC_DIR)/exec.c \
					$(SRC_EXEC_DIR)/fork.c \
					$(SRC_EXEC_DIR)/pipes.c \
					$(SRC_EXEC_DIR)/redirection.c \
					$(SRC_EXEC_DIR)/error.c
SRCS_SIGNAL		=	$(SRC_SIGNAL_DIR)/listener.c
SRCS_BUILT		=	$(SRC_BUILT_DIR)/env.c \
					$(SRC_BUILT_DIR)/unset.c \
					$(SRC_BUILT_DIR)/utils.c \
					$(SRC_BUILT_DIR)/export.c \
					$(SRC_BUILT_DIR)/export_utils.c \
					$(SRC_BUILT_DIR)/pwd.c \
					$(SRC_BUILT_DIR)/chdir.c 

#-----------------				OBJECTS				----------------#
# OBJS_FRONTEND	=	$(SRCS_FRONTEND:%.c=$(BUILD_DIR)/%.o)
# OBJS_EXEC	=	$(SRCS_EXEC:%.c=$(BUILD_DIR)/%.o)
OBJS_DEV		=	$(patsubst $(SRC_DEV_DIR)/%.c, $(BUILD_DIR)/dev_%.o, $(SRCS_DEV))
OBJS_EXEC	=	$(patsubst $(SRC_EXEC_DIR)/%.c, $(BUILD_DIR)/exec_%.o, $(SRCS_EXEC))
OBJS_SHELL	=	$(patsubst $(SRC_SHELL_DIR)/%.c, $(BUILD_DIR)/shell_%.o, $(SRCS_SHELL))
OBJS_SIGNAL	=	$(patsubst $(SRC_SIGNAL_DIR)/%.c, $(BUILD_DIR)/signal_%.o, $(SRCS_SIGNAL))
OBJS_BUILT	=	$(patsubst $(SRC_BUILT_DIR)/%.c, $(BUILD_DIR)/built_in_%.o, $(SRCS_BUILT))

#===================================================================#
#								TARGETS								#
#===================================================================#

.SILENT: 
.PHONY: help all art create_dir re clean fclean how_to

all: create_dir	$(NAME)## Command to start all the compiling
	make art

#-----------------				COMPILE OBJECTS		----------------#
$(BUILD_DIR)/dev_%.o: $(SRC_DEV_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/shell_%.o: $(SRC_SHELL_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/exec_%.o: $(SRC_EXEC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/signal_%.o: $(SRC_SIGNAL_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/built_in_%.o: $(SRC_BUILT_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

#-----------------			BUILD THE MINISHELL		----------------#
$(NAME): $(OBJS_DEV) $(OBJS_SHELL) $(OBJS_EXEC) $(OBJS_SIGNAL) $(OBJS_BUILT)
	make all -C libft
	$(CC) $(CFLAGS_DEV) $(OBJS_SHELL) $(OBJS_EXEC) $(OBJS_DEV) $(OBJS_SIGNAL) $(OBJS_BUILT) $(LIBFT) -o $@ $(LDFLAGS) -g

#-----------------				SETUP DIR			----------------#
create_dir:	## Build the directory that will gather .o files
	if [ -d $(BUILD_DIR) ]; then \
		echo "Build folder already exists"; \
	else \
		mkdir -p $(BUILD_DIR); \
		echo "Build folder has been created"; \
	fi

#-----------------				ART/LOADING			----------------#
art:	## ASCII art for minishell
	echo "--MINISHELL--"

#-----------------				COMMANDS			----------------#
clean:	## Remove all the .o files from build directory (build include)
	$(RM) $(BUILD_DIR)
	make clean -C libft

fclean: clean ## Remove all .o files and the minishell binary
	$(RM) $(NAME)
	$(RM) $(LIBFT)

re: fclean all ## Clean everything and recompile the project
	
help:	## Show the commands
	grep -E '(^[a-zA-Z_-]+:.*?##.*$$)|(^##)' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[32m%-10s\033[0m %s\n", $$1, $$2}' | sed -e 's/\[32m##/[33m/'

how_to: ## Command to help you to add update to the makefile
	echo "No information yet."
