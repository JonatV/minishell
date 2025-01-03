/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_array_builder.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 13:51:43 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/14 14:21:23 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	find_correct_handling(t_token **tokens_list, t_cmd *cmd)
{
	int	success;

	success = 0;
	if ((*tokens_list)->type == TOKEN_WORD \
		|| (*tokens_list)->type == TOKEN_SINGLE_QUOTE \
		|| (*tokens_list)->type == TOKEN_DOUBLE_QUOTE)
		success = handle_token_word(cmd, tokens_list);
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
		return (-2);
	}
	else if ((*tokens_list)->type == TOKEN_SPACE)
		*tokens_list = (*tokens_list)->next;
	return (success);
}

static int	handle_single_token(t_token **tokens_list, t_cmd *cmd)
{
	int		success;
	t_token	*current;

	current = *tokens_list;
	if (current->content[0] != '\0' || current->type != TOKEN_SKIP)
	{
		success = find_correct_handling(tokens_list, cmd);
		if (success != 0)
			return (success);
	}
	else
		*tokens_list = (*tokens_list)->next;
	return (0);
}

static int	parse_cmds(t_token **tokens_list, t_cmd *cmd)
{
	int	success;

	init_struct(cmd);
	while (*tokens_list)
	{
		success = handle_single_token(tokens_list, cmd);
		if (success == -2)
			break ;
		if (success != 0)
			return (success);
		if (*tokens_list == NULL)
			break ;
	}
	return (0);
}

bool	cmd_array_builder(t_shell *shell)
{
	int		i;
	t_token	*tmp;
	int		ret;

	shell->cmd_number = count_cmd(shell->tokens_list);
	shell->cmd_array = malloc(sizeof(t_cmd) * shell->cmd_number);
	if (!shell->cmd_array)
		panic(ERR_MALLOC, shell);
	tmp = shell->tokens_list;
	i = 0;
	while (i < shell->cmd_number)
	{
		ret = parse_cmds(&tmp, &shell->cmd_array[i]);
		if (ret == 1)
			panic(ERR_MALLOC, shell);
		else if (ret == 2)
			return (false);
		i++;
	}
	return (true);
}
