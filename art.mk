# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    art.mk                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/09 21:41:24 by jveirman          #+#    #+#              #
#    Updated: 2024/11/14 14:49:33 by jveirman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

E		=	\033[0;31m
M		=	\033[0;91m
I		=	\033[0;37m
N		=	\033[0m
T		=	\033[0;37m
G		=	\033[2m
B		=	\033[100m
GR		=	\033[32m


GIT_DATE := $(shell git log -1 --pretty=format:%cd --date=short)

GIT_TOTAL:= $(shell git rev-list --count HEAD)

FORMATTED_GIT_TOTAL := $(shell \
    message="  $(GIT_TOTAL) updates"; \
    total_length=60; \
    message_length=$$(echo "$$message" | wc -c); \
    padding_length=$$((total_length - message_length)); \
    padding=$$(printf '%*s' $$padding_length ''); \
    printf '%s%s' "$$message" "$$padding" \
)

GIT_LOG = $(shell git log -1 --pretty=format:%s)

FORMATTED_LOG := $(shell \
    message="$(GIT_LOG)"; \
    total_length=57; \
    message_length=$$(echo "$$message" | wc -c); \
    padding_length=$$((total_length - message_length)); \
    if [ $$message_length -gt $$total_length ]; then \
        message=$$(echo "$$message" | cut -c1-53)"..."; \
        padding_length=0; \
    fi; \
    padding=$$(printf '%*s' $$padding_length ''); \
    printf '%s%s' "$$message" "$$padding" \
)

ART_AFTER_COMPILE := "\n\
$(E)▄▄█$(M)█$(I)█$(M)███$(E)██$(T)                                           ▄██            ▄█▄ █▄   $(E)▄▄$(M)███$(I)█$(M)█$(E)███$(N)\n\
$(E)██▄$(M)█$(I)▄$(M)▄▄█$(E)█▄$(T)         ▄█████████▄ ▄██▄█████▄ ▄██▄██▀██ ▄█████▄ ▄█▀███ ▄██ ██▀   $(E)██$(M)▄█▄$(I)▄$(M)▄$(E)██▄$(N)\n\
$(E)█▄▄$(M)▄$(I)▄$(M)███$(E)▄▄$(T)        ▄██▀▄██▀▄██▀▄█▀▄██▀▄██▀▄█▀ ▀▀█▄▄ ▄██▀▄██▀▄██▀▀▀ ▄██ ██▀    $(E)█▄$(M)▄▄▄$(I)█$(M)█$(E)█▄▄$(N)\n\
$(E)▄▄█$(M)█$(I)█$(M)██▄$(E)▄▄$(T)       ▄██▀▄██▀▄██▀▄█▀▄██▀▄██▀▄█▀▄██▄██▀▄██▀▄██▀▄██▄▄█▀▄██ ██▀     $(E)▄▄$(M)███$(I)█$(M)█$(E)▄▄▄$(N)\n\
$(E)▄▄█$(M)█$(I)█$(M)▄▄▄$(E)▄▄$(T)      ███ ▄────────────────────────────────────────────▄  ██▀      $(E)▄▄$(M)███$(I)▄$(M)▄$(E)▄▄▄$(N)\n\
$(E)▄▄▄$(M)▄$(I)█$(M)█▄█$(E)▄▄$(T)     ██▀  █                ┓ ┏  ┓                      █ ██▀       $(E)▄▄$(M)▄▄█$(I)█$(M)▄$(E)█▄▄$(N)\n\
$(E)███$(M)█$(I)█$(M)▀▀▀$(E)▀▀$(T)   ▄──────▀                ┃┃┃┏┓┃┏┏┓┏┳┓┏┓              ▀───────▄   $(E)██$(M)███$(I)▀$(M)▀$(E)▀▀▀$(N)\n\
$(E)  ▄$(M)█$(I)█$(M)█▀▀$(E)▀▀$(T)   █                       ┗┻┛┗ ┗┗┗┛┛┗┗┗                       █   $(E)  $(M)▄██$(I)█$(M)▀$(E)▀▀▀$(N)\n\
$(E)███$(M)█$(I)▄$(M)███$(E)█▀$(T)   █$(B) > Author                                                  $(T)█   $(E)██$(M)██▄$(I)█$(M)█$(E)██▀$(N)\n\
$(E)▀▀▀$(M)█$(I)█$(M)█▀▀$(E)▀▀$(T)   █  @jveirman                                                █   $(E)▀▀$(M)▀██$(I)█$(M)▀$(E)▀▀▀$(N)\n\
$(E)███$(M)█$(I)█$(M)▄▄▄$(E)▄▄$(T)   █                                                           █   $(E)██$(M)███$(I)▄$(M)▄$(E)▄▄▄$(N)\n\
$(E)▀▀▀$(M)▀$(I)█$(M)█▀▀$(E)▀▀$(T)   █$(B) > Last Commit                                             $(T)█   $(E)▀▀$(M)▀▀█$(I)█$(M)▀$(E)▀▀▀$(N)\n\
$(E)███$(M)▄$(I)█$(M)███$(E)██$(T)   █  $(FORMATTED_LOG) █   $(E)██$(M)█▄█$(I)█$(M)█$(E)███$(N)\n\
$(E)██▄$(M)█$(I)▄$(M)▄▄▄$(E)▄▄$(T)   █   $(G)└── $(GIT_DATE)$(T)                                          █   $(E)██$(M)▄█▄$(I)▄$(M)▄$(E)▄▄▄$(N)\n\
$(E)▄▄█$(M)█$(I)█$(M)█▄▄$(E)▄▄$(T)   █                                                           █   $(E)▄▄$(M)███$(I)█$(M)▄$(E)▄▄▄$(N)\n\
$(E)███$(M)█$(I)▄$(M)█▄█$(E)▄█$(T)   █$(B) > Total Commit                                            $(T)█   $(E)██$(M)██▄$(I)█$(M)▄$(E)█▄█$(N)\n\
$(E) ▄ $(M)▄$(I) $(M)▄▄█$(E)██$(T)   █$(FORMATTED_GIT_TOTAL)█   $(E) ▄$(M) ▄ $(I)▄$(M)▄$(E)███$(N)\n\
$(E)███$(M)█$(I)█$(M)██▀$(E)▀▀$(T)   █                                                           █   $(E)██$(M)███$(I)█$(M)█$(E)▀▀▀$(N)\n\
$(E)▄▄▄$(M)▄$(I)█$(M)███$(E)▄▄$(T)   █$(B) > How to run minishell                                    $(T)█   $(E)▄▄$(M)▄▄█$(I)█$(M)█$(E)█▄▄$(N)\n\
$(E)   $(M)▄$(I)▄$(M)███$(E)▀█$(T)   █  Normal mode                                              █   $(E)  $(M) ▄▄$(I)█$(M)█$(E)█▀█$(N)\n\
$(E)███$(M)█$(I)█$(M)▀▀█$(E)██$(T)   █   └── $(GR)./minishell$(T)                                         █   $(E)██$(M)███$(I)▀$(M)▀$(E)███$(N)\n\
$(E)▄▄█$(M)█$(I)█$(M)███$(E)██$(T)   █                                                           █   $(E)▄▄$(M)███$(I)█$(M)█$(E)███$(N)\n\
$(E)██▄$(M)█$(I)▄$(M)▄▄█$(E)█▄$(T)   █  Dev mode                                                 █   $(E)██$(M)▄█▄$(I)▄$(M)▄$(E)██▄$(N)\n\
$(E)█▄▄$(M)▄$(I)▄$(M)███$(E)▄▄$(T)   █   └── $(GR)$$ make dev$(T) OR $(GR)$$ make redev$(T)                          █   $(E)█▄$(M)▄▄▄$(I)█$(M)█$(E)█▄▄$(N)\n\
$(E)▄▄█$(M)█$(I)█$(M)██▄$(E)▄▄$(T)   █                                                           █   $(E)▄▄$(M)███$(I)█$(M)█$(E)▄▄▄$(N)\n\
$(E)▄▄█$(M)█$(I)█$(M)▄▄▄$(E)▄▄$(T)   █                                                           █   $(E)▄▄$(M)███$(I)▄$(M)▄$(E)▄▄▄$(N)\n\
$(E)▄▄▄$(M)▄$(I)█$(M)█▄█$(E)▄▄$(T)   ▀───────────────────────────────────────────────────────────▀   $(E)▄▄$(M)▄▄█$(I)█$(M)▄$(E)█▄▄$(N)"

FULL_LINE = \
    " \033[0;31m▄▄█\033[0;91m█\033[0;37m█\033[0;91m███\033[0;31m██\033[0m                                                                   \033[0;31m▄▄\033[0;91m███\033[0;37m█\033[0;91m█\033[0;31m███\033[0m\r" \
    " \033[0;31m██▄\033[0;91m█\033[0;37m▄\033[0;91m▄▄█\033[0;31m█▄\033[0m                                                                   \033[0;31m██\033[0;91m▄█▄\033[0;37m▄\033[0;91m▄\033[0;31m██▄\033[0m\r" \
    " \033[0;31m█▄▄\033[0;91m▄\033[0;37m▄\033[0;91m███\033[0;31m▄▄\033[0m                                                                   \033[0;31m█▄\033[0;91m▄▄▄\033[0;37m█\033[0;91m█\033[0;31m█▄▄\033[0m\r" \
    " \033[0;31m▄▄█\033[0;91m█\033[0;37m█\033[0;91m██▄\033[0;31m▄▄\033[0m                                                                   \033[0;31m▄▄\033[0;91m███\033[0;37m█\033[0;91m█\033[0;31m▄▄▄\033[0m\r" \
    " \033[0;31m▄▄█\033[0;91m█\033[0;37m█\033[0;91m▄▄▄\033[0;31m▄▄\033[0m                                                                   \033[0;31m▄▄\033[0;91m███\033[0;37m▄\033[0;91m▄\033[0;31m▄▄▄\033[0m\r" \
    " \033[0;31m▄▄▄\033[0;91m▄\033[0;37m█\033[0;91m█▄█\033[0;31m▄▄\033[0m                                                                   \033[0;31m▄▄\033[0;91m▄▄█\033[0;37m█\033[0;91m▄\033[0;31m█▄▄\033[0m\r" \
    " \033[0;31m███\033[0;91m█\033[0;37m█\033[0;91m▀▀▀\033[0;31m▀▀\033[0m                                                                   \033[0;31m██\033[0;91m███\033[0;37m▀\033[0;91m▀\033[0;31m▀▀▀\033[0m\r" \
    " \033[0;31m  ▄\033[0;91m█\033[0;37m█\033[0;91m█▀▀\033[0;31m▀▀\033[0m                                                                   \033[0;31m  \033[0;91m▄██\033[0;37m█\033[0;91m▀\033[0;31m▀▀▀\033[0m\r" \
    " \033[0;31m███\033[0;91m█\033[0;37m▄\033[0;91m███\033[0;31m█▀\033[0m                                                                   \033[0;31m██\033[0;91m██▄\033[0;37m█\033[0;91m█\033[0;31m██▀\033[0m\r" \
    " \033[0;31m▀▀▀\033[0;91m█\033[0;37m█\033[0;91m█▀▀\033[0;31m▀▀\033[0m                                                                   \033[0;31m▀▀\033[0;91m▀██\033[0;37m█\033[0;91m▀\033[0;31m▀▀▀\033[0m\r" \
    " \033[0;31m███\033[0;91m█\033[0;37m█\033[0;91m▄▄▄\033[0;31m▄▄\033[0m                                                                   \033[0;31m██\033[0;91m███\033[0;37m▄\033[0;91m▄\033[0;31m▄▄▄\033[0m\r" \
    " \033[0;31m▀▀▀\033[0;91m▀\033[0;37m█\033[0;91m█▀▀\033[0;31m▀▀\033[0m                                                                   \033[0;31m▀▀\033[0;91m▀▀█\033[0;37m█\033[0;91m▀\033[0;31m▀▀▀\033[0m\r" \
    " \033[0;31m███\033[0;91m▄\033[0;37m█\033[0;91m███\033[0;31m██\033[0m                                                                   \033[0;31m██\033[0;91m█▄█\033[0;37m█\033[0;91m█\033[0;31m███\033[0m\r" \
    " \033[0;31m██▄\033[0;91m█\033[0;37m▄\033[0;91m▄▄▄\033[0;31m▄▄\033[0m                                                                   \033[0;31m██\033[0;91m▄█▄\033[0;37m▄\033[0;91m▄\033[0;31m▄▄▄\033[0m\r" \
    " \033[0;31m▄▄█\033[0;91m█\033[0;37m█\033[0;91m█▄▄\033[0;31m▄▄\033[0m                                                                   \033[0;31m▄▄\033[0;91m███\033[0;37m█\033[0;91m▄\033[0;31m▄▄▄\033[0m\r" \
    " \033[0;31m███\033[0;91m█\033[0;37m▄\033[0;91m█▄█\033[0;31m▄█\033[0m                                                                   \033[0;31m██\033[0;91m██▄\033[0;37m█\033[0;91m▄\033[0;31m█▄█\033[0m\r" \
    " \033[0;31m ▄ \033[0;91m▄\033[0;37m \033[0;91m▄▄█\033[0;31m██\033[0m                                                                   \033[0;31m ▄\033[0;91m ▄ \033[0;37m▄\033[0;91m▄\033[0;31m███\033[0m\r" \
    " \033[0;31m███\033[0;91m█\033[0;37m█\033[0;91m██▀\033[0;31m▀▀\033[0m                                                                   \033[0;31m██\033[0;91m███\033[0;37m█\033[0;91m█\033[0;31m▀▀▀\033[0m\r" \
    " \033[0;31m▄▄▄\033[0;91m▄\033[0;37m█\033[0;91m███\033[0;31m▄▄\033[0m                                                                   \033[0;31m▄▄\033[0;91m▄▄█\033[0;37m█\033[0;91m█\033[0;31m█▄▄\033[0m\r" \
    " \033[0;31m   \033[0;91m▄\033[0;37m▄\033[0;91m███\033[0;31m▀█\033[0m                                                                   \033[0;31m  \033[0;91m ▄▄\033[0;37m█\033[0;91m█\033[0;31m█▀█\033[0m\r" \
    " \033[0;31m███\033[0;91m█\033[0;37m█\033[0;91m▀▀█\033[0;31m██\033[0m                                                                   \033[0;31m██\033[0;91m███\033[0;37m▀\033[0;91m▀\033[0;31m███\033[0m\r" \
    " \033[0;31m▄▄█\033[0;91m█\033[0;37m█\033[0;91m███\033[0;31m██\033[0m                                                                   \033[0;31m▄▄\033[0;91m███\033[0;37m█\033[0;91m█\033[0;31m███\033[0m\r" \
    " \033[0;31m██▄\033[0;91m█\033[0;37m▄\033[0;91m▄▄█\033[0;31m█▄\033[0m                                                                   \033[0;31m██\033[0;91m▄█▄\033[0;37m▄\033[0;91m▄\033[0;31m██▄\033[0m\r" \
    " \033[0;31m█▄▄\033[0;91m▄\033[0;37m▄\033[0;91m███\033[0;31m▄▄\033[0m                                                                   \033[0;31m█▄\033[0;91m▄▄▄\033[0;37m█\033[0;91m█\033[0;31m█▄▄\033[0m\r" \
    " \033[0;31m▄▄█\033[0;91m█\033[0;37m█\033[0;91m██▄\033[0;31m▄▄\033[0m                                                                   \033[0;31m▄▄\033[0;91m███\033[0;37m█\033[0;91m█\033[0;31m▄▄▄\033[0m\r" \
    " \033[0;31m▄▄█\033[0;91m█\033[0;37m█\033[0;91m▄▄▄\033[0;31m▄▄\033[0m                                                                   \033[0;31m▄▄\033[0;91m███\033[0;37m▄\033[0;91m▄\033[0;31m▄▄▄\033[0m\r" \
    " \033[0;31m▄▄▄\033[0;91m▄\033[0;37m█\033[0;91m█▄█\033[0;31m▄▄\033[0m                                                                   \033[0;31m▄▄\033[0;91m▄▄█\033[0;37m█\033[0;91m▄\033[0;31m█▄▄\033[0m\r"
