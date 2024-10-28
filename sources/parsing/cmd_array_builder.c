/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_array_builder.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 13:51:43 by jveirman          #+#    #+#             */
/*   Updated: 2024/10/28 23:51:08 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	parse_cmds(t_token **tokens_list, t_cmd *cmd)
{
	bool	success;

	init_struct(cmd);
	while (*tokens_list)
	{
		if ((*tokens_list)->type == TOKEN_WORD)
			success = handle_token_word(cmd, (*tokens_list)->value);
		else if ((*tokens_list)->type == TOKEN_REDIR_IN)
			success = handle_token_redir_in(cmd, tokens_list);
		else if ((*tokens_list)->type == TOKEN_REDIR_OUT)
			success = handle_token_redir_out(cmd, tokens_list);
		else if ((*tokens_list)->type == TOKEN_REDIR_APPEND)
			success = handle_token_redir_append(cmd, tokens_list);
		else if ((*tokens_list)->type == TOKEN_REDIR_HEREDOC)
			success = handle_token_redir_heredoc(cmd, tokens_list);
		else if ((*tokens_list)->type == TOKEN_PIPE)
		{
			*tokens_list = (*tokens_list)->next;
			break ;
		}
		else//dev
			return (printf("Error : unknown token type number [%d]\n", (*tokens_list)->type), false);//dev
		if (!success)
			return (false);
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
