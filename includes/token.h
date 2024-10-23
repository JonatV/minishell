/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 20:02:36 by hsorel            #+#    #+#             */
/*   Updated: 2024/10/23 15:28:49 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include <sys/ioctl.h>
# include <termios.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include "../libft/libft.h"

#define GREEN "\e[32m"
#define N "\e[0m"

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_HEREDOC,
	TOKEN_ENV_VAR,
	TOKEN_BIG_QUOTES,
	TOKEN_SMALL_QUOTES,
}	t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	struct s_token		*next;
}	t_token;

char			**g_env;

void		update_quote_status(char c, int *in_quote, char *quote_char);
void		add_word_token_if_valid(char **start, char **input,
				t_token **tokens);
void		display_tokens(t_token *token);

t_token		*new_token(t_token_type type, char *value);
void		add_token_to_list(t_token **tokens, t_token *new_token);
void		free_tokens(t_token *tokens);
void		handle_quotes(char **input, t_token **tokens);
void		handle_special_chars(char **input, t_token **tokens);
void		handle_word(char **input, t_token **tokens);
t_token		*tokenize_input(t_shell *shell);
char		*ft_strndup(const char *src, size_t n);
size_t		ft_strnlen(const char *s, size_t maxlen);

#endif
