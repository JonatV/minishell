/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token_redirection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 23:22:04 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/12 18:44:38 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_token_redir_heredoc(t_cmd *cmd, t_token **tokens_list)
{
	if ((*tokens_list)->next && (*tokens_list)->next->type == TOKEN_SPACE)
		(*tokens_list) = (*tokens_list)->next;
	if (!(*tokens_list)->next)
		return (error_msg(ERR_TKNNL), 2);
	else if ((*tokens_list)->next->type != TOKEN_WORD \
		&& (*tokens_list)->next->type != TOKEN_DOUBLE_QUOTE \
		&& (*tokens_list)->next->type != TOKEN_SINGLE_QUOTE)
		return (mini_printf(ERR_TKNSNTX, (*tokens_list)->next->content, \
			"'\n", STDERR_FILENO), 2);
	else
	{
		ft_arraypush(&cmd->here_doc_delimiter, (*tokens_list)->next->content);
		if (!cmd->here_doc_delimiter)
			return (1);
		*tokens_list = (*tokens_list)->next->next;
		cmd->fd_in = USE_HEREDOC;
	}
	return (0);
}

int	handle_token_redir_append(t_cmd *cmd, t_token **tokens_list)
{
	int		fd;

	if ((*tokens_list)->next && (*tokens_list)->next->type == TOKEN_SPACE)
		(*tokens_list) = (*tokens_list)->next;
	if (!(*tokens_list)->next)
		return (error_msg(ERR_TKNNL), 2);
	else if ((*tokens_list)->next->type != TOKEN_WORD \
		&& (*tokens_list)->next->type != TOKEN_DOUBLE_QUOTE \
		&& (*tokens_list)->next->type != TOKEN_SINGLE_QUOTE)
		return (mini_printf(ERR_TKNSNTX, (*tokens_list)->next->content, \
			"'\n", STDERR_FILENO), 2);
	else
	{
		if (cmd->fd_out == -1)
		{
			*tokens_list = (*tokens_list)->next->next;
			return (0);
		}
		fd = open((*tokens_list)->next->content, \
			O_CREAT | O_WRONLY | O_APPEND, 0664);
		cmd->fd_out = fd;
		if (cmd->file_name_out)
			free(cmd->file_name_out);
		cmd->file_name_out = ft_strdup((*tokens_list)->next->content);
		if (!cmd->file_name_out)
			return (1);
		*tokens_list = (*tokens_list)->next->next;
	}
	return (0);
}

int	handle_token_redir_out(t_cmd *cmd, t_token **tokens_list)
{
	int		fd;

	if ((*tokens_list)->next && (*tokens_list)->next->type == TOKEN_SPACE)
		(*tokens_list) = (*tokens_list)->next;
	if (!(*tokens_list)->next)
		return (error_msg(ERR_TKNNL), 2);
	else if ((*tokens_list)->next->type != TOKEN_WORD \
		&& (*tokens_list)->next->type != TOKEN_DOUBLE_QUOTE \
		&& (*tokens_list)->next->type != TOKEN_SINGLE_QUOTE)
		return (mini_printf(ERR_TKNSNTX, (*tokens_list)->next->content, \
			"'\n", STDERR_FILENO), 2);
	else
	{
		if (cmd->fd_out == -1)
		{
			*tokens_list = (*tokens_list)->next->next;
			return (0);
		}
		fd = open((*tokens_list)->next->content, \
			O_CREAT | O_WRONLY | O_TRUNC, 0664);
		cmd->fd_out = fd;
		if (cmd->file_name_out)
			free(cmd->file_name_out);
		cmd->file_name_out = ft_strdup((*tokens_list)->next->content);
		if (!cmd->file_name_out)
			return (1);
		*tokens_list = (*tokens_list)->next->next;
	}
	return (0);
}

int	handle_token_redir_in(t_cmd *cmd, t_token **tokens_list)
{
	int		fd;

	if ((*tokens_list)->next && (*tokens_list)->next->type == TOKEN_SPACE)
		(*tokens_list) = (*tokens_list)->next;
	if (!(*tokens_list)->next)
		return (error_msg(ERR_TKNNL), 2);
	else if ((*tokens_list)->next->type != TOKEN_WORD \
		&& (*tokens_list)->next->type != TOKEN_DOUBLE_QUOTE \
		&& (*tokens_list)->next->type != TOKEN_SINGLE_QUOTE)
		return (mini_printf(ERR_TKNSNTX, (*tokens_list)->next->content, \
			"'\n", STDERR_FILENO), 2);
	else
	{
		if (cmd->fd_in == -1)
		{
			*tokens_list = (*tokens_list)->next->next;
			return (0);
		}
		fd = open((*tokens_list)->next->content, O_RDONLY);
		cmd->fd_in = fd;
		if (cmd->file_name_in)
			free(cmd->file_name_in);
		cmd->file_name_in = ft_strdup((*tokens_list)->next->content);
		if (!cmd->file_name_in)
			return (1);
		*tokens_list = (*tokens_list)->next->next;
	}
	return (0);
}
