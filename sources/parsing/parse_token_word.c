/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token_word.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 23:38:24 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/08 12:42:53 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	handle_cmd_name(t_cmd *cmd, char *content)
{
	cmd->data[CMD_NAME] = ft_strdup(content);
	free(content);
	if (!cmd->data[CMD_NAME])
		return (1);
	return (0);
}

static int	handle_cmd_arg_n_flag(t_cmd *cmd, char *content, int data_slot)
{
	char	*temp;

	if (!cmd->data[data_slot])
		cmd->data[data_slot] = ft_strdup("");
	if (!cmd->data[data_slot])
		return (1);
	if (cmd->data[data_slot][0] == '\0')
		temp = ft_strjoin(cmd->data[data_slot], content);
	else
	{
		temp = ft_strjoin(cmd->data[data_slot], " ");
		if (!temp)
			return (1);
		free(cmd->data[data_slot]);
		cmd->data[data_slot] = temp;
		temp = ft_strjoin(cmd->data[data_slot], content);
	}
	if (!temp)
		return (1);
	free(cmd->data[data_slot]);
	cmd->data[data_slot] = temp;
	if (data_slot == CMD_ARG)
		cmd->num_arg++;
	else
		cmd->num_flag++;
	free(content);
	return (0);
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
int	handle_token_word(t_cmd *cmd, t_token **tokens_list)
{
	char	*content;
	char	*temp;

	content = ft_strdup("");
	if (!content)
		return (1);
	while (*tokens_list && ((*tokens_list)->type == TOKEN_WORD || (*tokens_list)->type == TOKEN_SINGLE_QUOTE || (*tokens_list)->type == TOKEN_DOUBLE_QUOTE))
	{
		temp = ft_strjoin(content, (*tokens_list)->content);
		free(content);
		if (!temp)
			return (1);
		content = temp;
		*tokens_list = (*tokens_list)->next;
	}
	if (!cmd->data[CMD_NAME])
		return (handle_cmd_name(cmd, content));
	else if (content[0] == '-')
		return (handle_cmd_arg_n_flag(cmd, content, CMD_FLAG));
	else
		return (handle_cmd_arg_n_flag(cmd, content, CMD_ARG));
	return (0);
}
