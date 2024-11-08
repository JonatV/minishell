/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_array_builder.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 13:51:43 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/08 12:49:34 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	parse_cmds(t_token **tokens_list, t_cmd *cmd)
{
	int	success;
	
	init_struct(cmd);
	while (*tokens_list)
	{	
		if ((*tokens_list)->content[0] != '\0' || (*tokens_list)->type != TOKEN_SKIP)
		{
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
				break ;
			}
			else if ((*tokens_list)->type == TOKEN_SPACE)
			{
				*tokens_list = (*tokens_list)->next;
				continue ;
			}
			if (success != 0)
				return (success);
		}
		else
			*tokens_list = (*tokens_list)->next;
		if (*tokens_list == NULL)
			break ;
	}
	return (0);
}

bool cmd_array_builder(t_shell *shell)
{
	int		i;
	t_token	*tmp;
	int		ret;

	shell->cmd_number = count_cmd(shell->tokens_list);
	printf("cmd_number: %d\n", shell->cmd_number); // dev
	shell->cmd_array = malloc(sizeof(t_cmd) * shell->cmd_number);
	if (!shell->cmd_array)
		panic(ERR_MALLOC, shell);
	tmp = shell->tokens_list;
	i = 0;
	while (i < shell->cmd_number)
	{
		ret = parse_cmds(&tmp, &shell->cmd_array[i]);
		if(ret == 1)
			panic(ERR_MALLOC, shell);
		else if (ret == 2)
			return (false);
		i++;
	}
	return (true);
}
