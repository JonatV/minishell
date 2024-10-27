/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_array_builder.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 13:51:43 by jveirman          #+#    #+#             */
/*   Updated: 2024/10/27 23:02:43 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *get_next_line(int fd);

static bool	handle_token_redir_out(t_cmd *cmd, t_token **tokens_list)
{
	int		fd;

	cmd->fd_out = -1;
	if (!(*tokens_list)->next)
		return (printf("minishell: syntax error near unexpected token `newline'\n"), false);
	else if ((*tokens_list)->next->type != TOKEN_WORD)
		return (printf("minishell: syntax error near unexpected token `%s'", (*tokens_list)->next->value), false);
	else
	{
		fd = open((*tokens_list)->next->value, O_CREAT | O_WRONLY | O_TRUNC, \
		S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
		if (fd == -1)
		{
			printf("minishell: %s: No such file or directory\n", (*tokens_list)->value);
			*tokens_list = (*tokens_list)->next;
			return (false);
		}
		cmd->fd_out = fd;
		// close(fd);
		*tokens_list = (*tokens_list)->next;
	}
	return (true);
}

static bool	handle_token_redir_in(t_cmd *cmd, t_token **tokens_list)
{
	int		fd;
	
	cmd->fd_in = -1;
	if (!(*tokens_list)->next)
		return (printf("minishell: syntax error near unexpected token `newline'\n"), false);
	else if ((*tokens_list)->next->type != TOKEN_WORD)
		return (printf("minishell: syntax error near unexpected token `%s'", (*tokens_list)->next->value), false);
	else
	{
		fd = open((*tokens_list)->next->value, O_RDONLY);
		if (fd == -1)
		{
			printf("minishell: %s: No such file or directory\n", (*tokens_list)->value);
			*tokens_list = (*tokens_list)->next;
			return (false);
		}
		cmd->fd_in = fd;
		*tokens_list = (*tokens_list)->next;
	}
	return (true);
}
	// else
	// {
	// 	buffer = readline(">");
	// 	if (!buffer)
	// 	{
	// 		free(buffer);
	// 		return (false);
	// 	}
	// }
static bool	handle_token_word(t_cmd *cmd, char *value)
{
	char *temp;

	if (!cmd->data[CMD_NAME])
	{
		cmd->data[CMD_NAME] = ft_strdup(value);
		if (!cmd->data[CMD_NAME])
			return (false);
	}
	else
	{
		if (!cmd->data[CMD_ARG])
			cmd->data[CMD_ARG] = ft_strdup("");
		temp = ft_strjoin(cmd->data[CMD_ARG], value);
		if (!temp)
			return (false);
		free(cmd->data[CMD_ARG]);
		cmd->data[CMD_ARG] = temp;
	}
	return (true);
}

static bool	parse_cmds(t_token **tokens_list, t_cmd *cmd) //todo check if var i is ok in the parse_cmds
{
	init_struct(cmd);
	while (*tokens_list)
	{
		if ((*tokens_list)->type == TOKEN_WORD)
		{
			if (!handle_token_word(cmd, (*tokens_list)->value))
				return (false);
		}
		else if ((*tokens_list)->type == TOKEN_REDIR_IN)
		{
			if (!handle_token_redir_in(cmd, tokens_list))
			{
				return (false);
			}
		}
		else if ((*tokens_list)->type == TOKEN_REDIR_OUT)
		{
			if (!handle_token_redir_out(cmd, tokens_list))
			{
				return (false);
			}
		}
		else if ((*tokens_list)->type == TOKEN_PIPE)
		{
			*tokens_list = (*tokens_list)->next;
			break ;
		}
		*tokens_list = (*tokens_list)->next;
	}
	return (true);
}

bool cmd_array_builder(t_shell *shell, t_token **tokens_list)
{
	int	i;

	shell->cmd_number = count_cmd(*tokens_list);
	shell->cmd_array = malloc(sizeof(t_cmd) * shell->cmd_number);
	if (!shell->cmd_array)
		return (0);
	i = 0;
	while (i < shell->cmd_number)
	{
		if(!parse_cmds(tokens_list, &shell->cmd_array[i]))
			return (false);
		i++;
	}
	return (true);
}
