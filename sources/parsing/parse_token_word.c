/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token_word.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 23:38:24 by jveirman          #+#    #+#             */
/*   Updated: 2024/10/29 13:35:52 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


static bool	handle_cmd_name(t_cmd *cmd, char *value)
{
	cmd->data[CMD_NAME] = ft_strdup(value);
	if (!cmd->data[CMD_NAME])
		return (false);
	return (true);
}

static bool	handle_cmd_arg_n_flag(t_cmd *cmd, char *value, int data_slot)
{
	char	*temp;

	if (!cmd->data[data_slot])
		cmd->data[data_slot] = ft_strdup("");
	if (cmd->data[data_slot][0] == '\0')
		temp = ft_strjoin(cmd->data[data_slot], value);
	else
	{
		temp = ft_strjoin(cmd->data[data_slot], " ");
		if (!temp)
			return (false);
		free(cmd->data[data_slot]);
		cmd->data[data_slot] = temp;
		temp = ft_strjoin(cmd->data[data_slot], value);
	}
	if (!temp)
		return (false);
	free(cmd->data[data_slot]);
	cmd->data[data_slot] = temp;
	return (true);
}

/*
* INFO:
*	Handle TOKEN_WORD from the cmd sent.
*	TOKEN_WORD can be 3 things:
*		CMD_NAME	= first TOKEN_WORD found
*		CMD_FLAG	= all TOKEN_WORD starting with an hyphen "-flag_name"
*		CMD_ARG		= all non first TOKEN_WORD
*	First condition store the name
*	Second condition store the flags
*	Third condition store the args
*/
bool	handle_token_word(t_cmd *cmd, char *value)
{
	if (!cmd->data[CMD_NAME])
		return (handle_cmd_name(cmd, value));
	else if (value[0] == '-')
		return (handle_cmd_arg_n_flag(cmd, value, CMD_FLAG));
	else
		return (handle_cmd_arg_n_flag(cmd, value, CMD_ARG));
	return (true);
}
