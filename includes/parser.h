/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:32:16 by mcygan            #+#    #+#             */
/*   Updated: 2024/06/12 13:25:27 by mcygan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>

enum
{
	VOID	= 0,
	WORD	= 1,
	PIPE	= 2,
	STREAM	= 3,
	HEREDOC	= 4,
	END		= 5
};

typedef struct s_token
{
	int		type;
	char	*data;
}	t_token;

typedef struct s_cmd
{
	int		fd_in;
	int		fd_out;
	char	**data;
	char	*path;
}	t_cmd;

typedef struct s_shell
{
	int		cmd_number;
	t_cmd	*cmd_array;		// malloc
	int		*pipefds;		// malloc
	char	**env;			// malloc + inside malloc
	char	*prompt_msg;	// malloc
	char	*buf;			// malloc form readline, don't handle
	int		exit_status;
	char	*last_arg;
}	t_shell;

// lexer
int		token_count(char *input);
t_token	*tokens_init(char *input);
char	*get_token_data(char *str, int *idx);
void	set_token_type(t_token *tokens, int idx);

// parser
int		validate_cmd_order(t_token *tokens);
char	*strip_redir(char *path);
int 	open_check(char *file_path, int option);
int		word_count(t_token *tokens);
int		expr_count(t_token *tokens);
void	set_fd(t_cmd *cmd_info, t_token token);
t_cmd	*fill_cmd_info(t_token *tokens);

// utils
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int		ft_strncmp(const char *s1, const char *s2, int n);
int 	is_whitespace(const char c);
int		skip_whitespace(char *str, int *idx);
int		is_quote(const char c);
int		skip_quote(char *str, int *idx);

#endif