/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_all_token_types.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:09:42 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/08 13:41:59 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_token	*token_redirection_out(char *buf, int *i)
{
	t_token *new_token;
	char *content;
	t_token_type type;

	content = NULL;
	if (buf[*i + 1] && buf[*i + 1] == '>')
	{
		content = ft_strdup(">>");
		type = TOKEN_REDIR_APPEND;
		*i += 2;
	}
	else
	{
		content = ft_strdup(">");
		type = TOKEN_REDIR_OUT;
		*i += 1;
	}
	if (!content)
		return (NULL);
	new_token = create_token(type, &content);
	if (!new_token)
		return (NULL);
	return (new_token);
}

static t_token	*token_redirection_in(char *buf, int *i)
{
	t_token *new_token;
	char *content;
	t_token_type type;

	content = NULL;
	if (buf[*i + 1] && buf[*i + 1] == '<')
	{
		content = ft_strdup("<<");
		type = TOKEN_REDIR_HEREDOC;
		*i += 2;
	}
	else
	{
		content = ft_strdup("<");
		type = TOKEN_REDIR_IN;
		*i += 1;
	}
	if (!content)
		return (NULL);
	new_token = create_token(type, &content);
	if (!new_token)
		return (NULL);
	return (new_token);
}

void handle_redirections(t_shell *shell, int *i, t_token **tokens_list)
{
	t_token *pending_token;
	
	if (shell->buf[*i] == '>')
	{
		pending_token = token_redirection_out(shell->buf, i);
		if(!add_token(tokens_list, pending_token))
			panic(ERR_MALLOC, shell);
	}
	else if (shell->buf[*i] == '<')
	{
		pending_token = token_redirection_in(shell->buf, i);
		if(!add_token(tokens_list, pending_token))
			panic(ERR_MALLOC, shell);
	}
}

bool	handle_pipe(t_shell *shell, int *i, t_token **tokens_list)
{
	char	*content;
	t_token	*new_token;

	if (shell->buf[*i + 1] && shell->buf[*i + 1] == '|')
	{
		clean(NULL, shell, false);
		return (error_msg("'||': OR operator not allowed"));
	}
	content = NULL;
	content = ft_strdup("|");
	if (!content)
		panic(ERR_MALLOC, shell);
	new_token = create_token(TOKEN_PIPE, &content);
	if (!add_token(tokens_list, new_token))
			panic(ERR_MALLOC, shell);
	*i += 1;
	return (true);
}

void	handle_space(t_shell *shell, int *i, t_token **tokens_list)
{
	char		*tmp;
	t_token		*pending_token;
	int start;

	start = *i;
	while (shell->buf[*i] && ft_isspace(shell->buf[*i]))
		*i += 1;
	tmp = ft_substr(shell->buf, start, *i - start);
	if (!tmp)
		panic(ERR_MALLOC, shell);
	pending_token = create_token(TOKEN_SPACE, &tmp);
	if (!add_token(tokens_list, pending_token))
		panic(ERR_MALLOC, shell);
}
