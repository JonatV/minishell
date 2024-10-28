/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token_word.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 23:38:24 by jveirman          #+#    #+#             */
/*   Updated: 2024/10/28 23:46:15 by jveirman         ###   ########.fr       */
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

static bool	handle_cmd_flag(t_cmd *cmd, char *value)
{
	char	*temp;

	if (!cmd->data[CMD_FLAG])
		cmd->data[CMD_FLAG] = ft_strdup("");
	temp = ft_strjoin(cmd->data[CMD_FLAG], value);
	if (!temp)
		return (false);
	free(cmd->data[CMD_FLAG]);
	cmd->data[CMD_FLAG] = temp;
	return (true);
}

static bool	handle_cmd_arg(t_cmd *cmd, char *value)
{
	char	*temp;
	if (!cmd->data[CMD_ARG])
		cmd->data[CMD_ARG] = ft_strdup("");
	temp = ft_strjoin(cmd->data[CMD_ARG], value);
	if (!temp)
		return (false);
	free(cmd->data[CMD_ARG]);
	cmd->data[CMD_ARG] = temp;
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
		return (handle_cmd_flag(cmd, value));
	else
		return (handle_cmd_arg(cmd, value));
	return (true);
}
