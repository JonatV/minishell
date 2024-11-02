NAME		=	minishell
CC			=	gcc
RM			=	rm -rf
OUT			=	-o $(NAME)
CFLAGS		=	-Wall -Wextra -Werror -g -fsanitize=address 
LIBFT		=	./libft/libft.a
HEADER		=	./includes/minishell.h

ifeq ($(shell uname), Linux)
else
	CFLAGS	+=	-I ~/.brew/opt/readline/include
	LDFLAGS	=	-L ~/.brew/opt/readline/lib
endif

BUILT_IN	=	chdir echo env exit export_utils export pwd unset utils

DEV_TOOL	=	fake_array_from_parsing print_array_all_cmd

EXEC		=	error exec_utils exec fork here_doc_utils here_doc pipes redirection

EXPANDER	=	expander

PARSING		=	cmd_array_builder parsing utils parse_token_redirection parse_token_word

MINISHELL	=	env_utils exit main prompt check_cmd_line_structure init_shell free_helper

SIGNAL		=	listener

TOKEN		=	tokenizer_utils tokenizer

SRCS		=	$(addsuffix .c, $(addprefix sources/built_in/, $(BUILT_IN))) \
				$(addsuffix .c, $(addprefix sources/dev_tool/, $(DEV_TOOL))) \
				$(addsuffix .c, $(addprefix sources/exec/, $(EXEC))) \
				$(addsuffix .c, $(addprefix sources/expander/, $(EXPANDER))) \
				$(addsuffix .c, $(addprefix sources/parsing/, $(PARSING))) \
				$(addsuffix .c, $(addprefix sources/shell/, $(MINISHELL))) \
				$(addsuffix .c, $(addprefix sources/signal/, $(SIGNAL))) \
				$(addsuffix .c, $(addprefix sources/token/, $(TOKEN)))

OBJS		=	$(SRCS:c=o)

#-----------------				DEPENDENCIES		----------------#
MKFILES			=	art.mk
include				$(MKFILES)

#===================================================================#
#								TARGETS								#
#===================================================================#

.SILENT:
.PHONY: help all art re clean fclean check-os dev redev run

all: check-os $(NAME)## Command to start all the compiling
	clear
	make art

dev: check-os $(NAME) job_s_done run## Command to start all the compiling with art skip

$(NAME): $(OBJS)
	echo
	make --no-print-directory all -C libft
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) -lreadline -lncurses $(LDFLAGS)

job_s_done:
		echo "\n\033[0;32mDone !\033[0m"

%.o: %.c
	printf "Generating minishell objects:\t %-33.33s\r" $@
	${CC} ${CFLAGS} -c $< -o $@

clean:
	make --no-print-directory clean -C libft
	printf "Libft simple clean: \033[0;32m✅\033[0m\n"
	$(RM) $(OBJS)
	printf "Minishell simple clean: \033[0;32m✅\033[0m\n"
	echo "\033[0m"

fclean:
	make --no-print-directory fclean -C libft/
	printf "Libft full clean: \033[0;32m✅\033[0m\n"
	$(RM) $(OBJS)
	$(RM) $(NAME)
	printf "Minishell full clean: \033[0;32m✅\033[0m"
	echo

re: fclean all

redev: fclean dev

run:
	./minishell

art: loading	## ASCII art for minishell
	clear
	echo $(ART_AFTER_COMPILE)

loading:
	@ current_index=0; \
	main_index=0; \
	echo; \
    for current_line in $(FULL_LINE); do \
        for line in $(FULL_LINE); do \
                printf "$$line"; \
                sleep 0.01; \
                current_index=$$((current_index + 1)); \
                if [ $$current_index -eq 10 ]; then \
                    break; \
                fi; \
        done; \
        current_index=0; \
        printf "$$current_line"; \
		main_index=$$((main_index + 1)); \
		if [ $$main_index != 27 ]; then \
			printf "\n"; \
		fi; \
	done

check-os:
	echo "OS detected: $(shell uname)"
