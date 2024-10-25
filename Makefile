# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/23 15:54:50 by jveirman          #+#    #+#              #
#    Updated: 2024/10/25 15:47:24 by jveirman         ###   ########.fr        #
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
CFLAGS_DEV		=	-Wall -Wextra -Werror -fsanitize=address -g -I./includes -I ~/.brew/opt/readline/include
LDFLAGS			=	-L ~/.brew/opt/readline/lib -lreadline

RM				=	rm -rf

#-----------------				ASSETS				----------------#
LIBFT			=	./libft/libft.a

#-----------------				DEPENDENCIES		----------------#
MKFILES			=	art.mk
include				$(MKFILES)

#-----------------				DIRECTORIES			----------------#
BUILD_DIR		:=	./build
SRC_DIR			:=	./sources
SRC_DEV_DIR		:=	$(SRC_DIR)/dev_tool
SRC_EXEC_DIR	:=	$(SRC_DIR)/exec
SRC_EXPAND_DIR	:=	$(SRC_DIR)/expander
SRC_SHELL_DIR	:=	$(SRC_DIR)/shell
SRC_SIGNAL_DIR	:=	$(SRC_DIR)/signal
SRC_BUILT_DIR	:=	$(SRC_DIR)/built_in
SRC_TOKEN_DIR	:=	$(SRC_DIR)/token
SRC_PARSING_DIR	:=	$(SRC_DIR)/parsing
SRC_GNL_DIR		:=	get_next_line

#-----------------				SOURCES				----------------#
SRCS_DEV		=	$(SRC_DEV_DIR)/fake_array_from_parsing.c \
					$(SRC_DEV_DIR)/print_array_all_cmd.c \
					$(SRC_DEV_DIR)/command_call.c
SRCS_SHELL		=	$(SRC_SHELL_DIR)/main.c \
					$(SRC_SHELL_DIR)/prompt.c \
					$(SRC_SHELL_DIR)/exit.c \
					$(SRC_SHELL_DIR)/env_utils.c
SRCS_EXPAND		=	$(SRC_EXPAND_DIR)/expander.c
SRCS_EXEC		=	$(SRC_EXEC_DIR)/exec.c \
					$(SRC_EXEC_DIR)/exec_utils.c \
					$(SRC_EXEC_DIR)/fork.c \
					$(SRC_EXEC_DIR)/pipes.c \
					$(SRC_EXEC_DIR)/redirection.c \
					$(SRC_EXEC_DIR)/error.c \
					$(SRC_EXEC_DIR)/here_doc.c \
					$(SRC_EXEC_DIR)/here_doc_utils.c
SRCS_SIGNAL		=	$(SRC_SIGNAL_DIR)/listener.c
SRCS_BUILT		=	$(SRC_BUILT_DIR)/env.c \
					$(SRC_BUILT_DIR)/unset.c \
					$(SRC_BUILT_DIR)/utils.c \
					$(SRC_BUILT_DIR)/export.c \
					$(SRC_BUILT_DIR)/export_utils.c \
					$(SRC_BUILT_DIR)/pwd.c \
					$(SRC_BUILT_DIR)/chdir.c \
					$(SRC_BUILT_DIR)/exit.c \
					$(SRC_BUILT_DIR)/echo.c
SRCS_TOKEN		=	$(SRC_TOKEN_DIR)/tokenizer_utils.c \
					$(SRC_TOKEN_DIR)/tokenizer.c
SRCS_PARSING	=	$(SRC_PARSING_DIR)/cmd_array_builder.c \
					$(SRC_PARSING_DIR)/parsing.c \
					$(SRC_PARSING_DIR)/utils.c

#					$(SRC_PARSING_DIR)/check_operator.c \
					$(SRC_PARSING_DIR)/parse_command_2.c \
					$(SRC_PARSING_DIR)/parse_command.c \
					$(SRC_PARSING_DIR)/parse_red.c \
					$(SRC_PARSING_DIR)/check_quotes_op.c \
					$(SRC_PARSING_DIR)/check_quotes.c \
					$(SRC_PARSING_DIR)/set_cmd.c
SRCS_GNL		=	$(SRC_GNL_DIR)/get_next_line_utils.c \
					$(SRC_GNL_DIR)/get_next_line.c

#-----------------				OBJECTS				----------------#
OBJS_DEV		=	$(patsubst $(SRC_DEV_DIR)/%.c, $(BUILD_DIR)/dev_%.o, $(SRCS_DEV))
OBJS_EXEC		=	$(patsubst $(SRC_EXEC_DIR)/%.c, $(BUILD_DIR)/exec_%.o, $(SRCS_EXEC))
OBJS_EXPAND		=	$(patsubst $(SRC_EXPAND_DIR)/%.c, $(BUILD_DIR)/expand_%.o, $(SRCS_EXPAND))
OBJS_SHELL		=	$(patsubst $(SRC_SHELL_DIR)/%.c, $(BUILD_DIR)/shell_%.o, $(SRCS_SHELL))
OBJS_SIGNAL		=	$(patsubst $(SRC_SIGNAL_DIR)/%.c, $(BUILD_DIR)/signal_%.o, $(SRCS_SIGNAL))
OBJS_BUILT		=	$(patsubst $(SRC_BUILT_DIR)/%.c, $(BUILD_DIR)/built_in_%.o, $(SRCS_BUILT))
OBJS_TOKEN		=	$(patsubst $(SRC_TOKEN_DIR)/%.c, $(BUILD_DIR)/token_%.o, $(SRCS_TOKEN))
OBJS_PARSING	=	$(patsubst $(SRC_PARSING_DIR)/%.c, $(BUILD_DIR)/parsing_%.o, $(SRCS_PARSING))
OBJS_GNL	=		$(patsubst $(SRC_GNL_DIR)/%.c, $(BUILD_DIR)/get_next_line_%.o, $(SRCS_GNL))

#===================================================================#
#								TARGETS								#
#===================================================================#

.SILENT:
.PHONY: help all art create_dir re clean fclean how_to

all: create_dir	$(NAME)## Command to start all the compiling
	make art

#-----------------				COMPILE OBJECTS		----------------#
$(BUILD_DIR)/dev_%.o: $(SRC_DEV_DIR)/%.c
	$(CC) $(CFLAGS_DEV) -c $< -o $@

$(BUILD_DIR)/shell_%.o: $(SRC_SHELL_DIR)/%.c
	$(CC) $(CFLAGS_DEV) -c $< -o $@

$(BUILD_DIR)/exec_%.o: $(SRC_EXEC_DIR)/%.c
	$(CC) $(CFLAGS_DEV) -c $< -o $@

$(BUILD_DIR)/expand_%.o: $(SRC_EXPAND_DIR)/%.c
	$(CC) $(CFLAGS_DEV) -c $< -o $@

$(BUILD_DIR)/signal_%.o: $(SRC_SIGNAL_DIR)/%.c
	$(CC) $(CFLAGS_DEV) -c $< -o $@

$(BUILD_DIR)/built_in_%.o: $(SRC_BUILT_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/token_%.o: $(SRC_TOKEN_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/parsing_%.o: $(SRC_PARSING_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@


$(BUILD_DIR)/get_next_line_%.o: $(SRC_GNL_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

#-----------------			BUILD THE MINISHELL		----------------#
$(NAME): $(OBJS_DEV) $(OBJS_SHELL) $(OBJS_EXEC) $(OBJS_EXPAND) $(OBJS_SIGNAL) $(OBJS_BUILT) $(OBJS_TOKEN) $(OBJS_PARSING) $(OBJS_GNL)
	make all -C libft
	$(CC) $(CFLAGS_DEV) $(OBJS_DEV) $(OBJS_SHELL) $(OBJS_EXEC) $(OBJS_EXPAND) $(OBJS_SIGNAL) $(OBJS_BUILT) $(OBJS_TOKEN) $(OBJS_PARSING) $(OBJS_GNL) $(LIBFT) -o $@ $(LDFLAGS)

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
	echo $(ART_AFTER_COMPILE)

#-----------------				COMMANDS			----------------#
clean:	## Remove all the .o files from build directory (build include)
	$(RM) $(BUILD_DIR)
	make clean -C libft

fclean: clean ## Remove all .o files and the minishell binary
	$(RM) $(NAME)
	$(RM) $(LIBFT)

re: fclean all ## Clean everything and recompile the project

help:	## Show the commands
	@grep -E '^[a-zA-Z_-]+:.*?##' $(MAKEFILE_LIST) | \
	awk 'BEGIN {FS = ":.*?## "}; {split($$0, parts, ":"); sub(/^ */, "", parts[2]); printf "\033[32m%-20s\033[0m %s\n", parts[2], $$2}' | \
	sed -e 's/\[32m##/[33m/'

how_to: ## Command to help you to add update to the makefile
	echo "No information yet."
