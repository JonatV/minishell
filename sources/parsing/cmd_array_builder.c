/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_array_builder.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 13:51:43 by jveirman          #+#    #+#             */
/*   Updated: 2024/10/25 16:02:09 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

static bool handle_token_word(t_cmd *cmd, char *value)
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
