CC 		= 	gcc
CFLAGS	= 	-Wall -Wextra -Werror
NAME 	= 	libft.a
SRCS	= 	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
			ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c \
			ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c \
			ft_calloc.c ft_strdup.c ft_toupper.c ft_tolower.c \
			ft_strchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c \
			ft_atoi.c ft_atol.c ft_strrchr.c ft_substr.c ft_split.c\
			ft_strjoin.c ft_strtrim.c ft_itoa.c \
			ft_strmapi.c ft_striteri.c ft_putchar_fd.c \
			ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
			ft_strnstr.c ft_strcmp.c \
			ft_lstnew_bonus.c ft_lstadd_front_bonus.c \
			ft_lstsize_bonus.c ft_lstlast_bonus.c \
			ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
			ft_lstclear_bonus.c ft_lstiter_bonus.c \
			ft_lstmap_bonus.c \
			ft_putstr.c ft_lstdisplay.c ft_lstfree.c \
			ft_arrayprint.c ft_arrayndup.c ft_arraysize.c ft_arrayfree.c \
			ft_arrayfind.c ft_arraypop.c ft_arraypush.c ft_arrayshift.c \
			ft_arrayunshift.c ft_isspace.c

OBJS 	= 	${SRCS:.c=.o}
RM 		= 	rm -f
AR 		= 	ar rcs

RED		=	\033[0;31m
SUCCESS	=	\033[30;42;1m
END		=	\033[0m

TOT 	:= $(words $(SRCS))
C_FILE	:= 0

# define progress_bar_libft
# 	@$(eval C_FILE=$(shell echo $$(($(C_FILE) + 1))))
# 	@printf "\rLibft[%-$(TOT)s]" $$(for i in $$(seq 1 $(C_FILE)); do printf "#"; done)
# 	@if [ $(C_FILE) -eq $(TOT) ]; then echo "Finish\n"; fi
# endef

.PHONY 	:	all clean fclean re loading

%.o: %.c
	@printf "Generating libft objects:\t%-33.33s\r" $@
	@${CC} ${CFLAGS} -c $< -o $@

# .c.o	:
# 			@${CC} ${CFLAGS} -c $< -o $@
# 			$(call progress_bar_libft)

all 	:	${NAME}

${NAME} :	${OBJS}
			@${AR}	${NAME} ${OBJS}


clean 	:
			@${RM} 	${OBJS} ${OBJSB}
fclean 	: 	clean
			@${RM} ${NAME} ${bonus}
re		: 	fclean all
