/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token_redirection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 23:22:04 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/04 01:22:36 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	handle_token_redir_heredoc(t_cmd *cmd, t_token **tokens_list)
{
	if ((*tokens_list)->next && (*tokens_list)->next->type == TOKEN_SPACE)
		(*tokens_list) = (*tokens_list)->next;
	if (!(*tokens_list)->next)
		return (printf("minishell: syntax error near unexpected token `newline'\n"), false);
	else if ((*tokens_list)->next->type != TOKEN_WORD && (*tokens_list)->next->type != TOKEN_DOUBLE_QUOTE && (*tokens_list)->next->type != TOKEN_SINGLE_QUOTE)
		return (printf("minishell: syntax error near unexpected token `%s'", (*tokens_list)->next->content), false);
	else
	{
		ft_arraypush(&cmd->here_doc_delimiter, (*tokens_list)->next->content);
		*tokens_list = (*tokens_list)->next->next;
	}
	return (true);
}

bool	handle_token_redir_append(t_cmd *cmd, t_token **tokens_list)
{
	int		fd;

	cmd->fd_out = -1;
	if ((*tokens_list)->next && (*tokens_list)->next->type == TOKEN_SPACE)
		(*tokens_list) = (*tokens_list)->next;
	if (!(*tokens_list)->next)
		return (printf("minishell: syntax error near unexpected token `newline'\n"), false);
	else if ((*tokens_list)->next->type != TOKEN_WORD && (*tokens_list)->next->type != TOKEN_DOUBLE_QUOTE && (*tokens_list)->next->type != TOKEN_SINGLE_QUOTE)
		return (printf("minishell: syntax error near unexpected token `%s'", (*tokens_list)->next->content), false);
	else
	{
		fd = open((*tokens_list)->next->content, O_CREAT | O_WRONLY | O_APPEND, \
		S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
		if (fd == -1)
		{
			printf("minishell: %s: No such file or directory\n", (*tokens_list)->content);
			*tokens_list = (*tokens_list)->next;
			return (false);
		}
		cmd->fd_out = fd;
		// close(fd);
		*tokens_list = (*tokens_list)->next->next;
	}
	return (true);
}

bool	handle_token_redir_out(t_cmd *cmd, t_token **tokens_list)
{
	int		fd;

	cmd->fd_out = -1;
	if ((*tokens_list)->next && (*tokens_list)->next->type == TOKEN_SPACE)
		(*tokens_list) = (*tokens_list)->next;
	if (!(*tokens_list)->next)
		return (printf("minishell: syntax error near unexpected token `newline'\n"), false);
	else if ((*tokens_list)->next->type != TOKEN_WORD && (*tokens_list)->next->type != TOKEN_DOUBLE_QUOTE && (*tokens_list)->next->type != TOKEN_SINGLE_QUOTE)
		return (printf("minishell: syntax error near unexpected token `%s'", (*tokens_list)->next->content), false);
	else
	{
		fd = open((*tokens_list)->next->content, O_CREAT | O_WRONLY | O_TRUNC, \
		S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
		if (fd == -1)
		{
			printf("minishell: %s: No such file or directory\n", (*tokens_list)->content);
			*tokens_list = (*tokens_list)->next;
			return (false);
		}
		cmd->fd_out = fd;
		// close(fd);
		*tokens_list = (*tokens_list)->next->next;
	}
	return (true);
}

bool	handle_token_redir_in(t_cmd *cmd, t_token **tokens_list)
{
	int		fd;
	
	cmd->fd_in = -1;
	if ((*tokens_list)->next && (*tokens_list)->next->type == TOKEN_SPACE)
		(*tokens_list) = (*tokens_list)->next;
	if (!(*tokens_list)->next)
		return (printf("minishell: syntax error near unexpected token `newline'\n"), false);
	else if ((*tokens_list)->next->type != TOKEN_WORD && (*tokens_list)->next->type != TOKEN_DOUBLE_QUOTE && (*tokens_list)->next->type != TOKEN_SINGLE_QUOTE)
		return (printf("minishell: syntax error near unexpected token `%s'", (*tokens_list)->next->content), false);
	else
	{
		fd = open((*tokens_list)-> next->content, O_RDONLY);
		if (fd == -1)
		{
			printf("minishell: %s: No such file or directory\n", (*tokens_list)->content);
			*tokens_list = (*tokens_list)->next;
			return (false);
		}
		cmd->fd_in = fd;
		*tokens_list = (*tokens_list)->next->next;
	}
	return (true);
}
