/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:04:32 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/02 23:34:45 by jveirman         ###   ########.fr       */
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

void handle_redirections(char *buf, int *i, t_token **tokens_list)
{
	t_token *pending_token;
	
	if (buf[*i] == '>')
	{
		pending_token = token_redirection_out(buf, i);
		if(!add_token(tokens_list, pending_token))
		{
			free_tokens_list(tokens_list);
			return ;
		}
	}
	else if (buf[*i] == '<')
	{
		pending_token = token_redirection_in(buf, i);
		if(!add_token(tokens_list, pending_token))
		{
			free_tokens_list(tokens_list);
			return ;
		}
	}
	return ;
}
