/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:23:05 by haroldsorel       #+#    #+#             */
/*   Updated: 2024/11/04 19:13:02 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_struct(t_cmd *cmd)
{
	cmd->fd_in = DEFAULT_FD;
	cmd->fd_out = DEFAULT_FD;
	cmd->num_arg = 0;
	cmd->num_flag = 0;
	cmd->type = -1;
	cmd->here_doc_delimiter = NULL;
	cmd->here_doc_input = NULL;
	cmd->data[CMD_NAME] = NULL; //dev wip
	cmd->data[CMD_FLAG] = NULL; //dev wip
	cmd->data[CMD_ARG] = NULL; //dev wip
	cmd->data[CMD_END] = NULL; //dev wip its the null terminated
	cmd->final_cmd_line = NULL;
}

int	count_cmd(t_token *tokens_list)
{
	int	i;

	i = 0;
	while (tokens_list)
	{
		if (tokens_list->type == TOKEN_PIPE && tokens_list->next)
			i++;
		tokens_list = tokens_list->next;
	}
	return (i + 1);
}

int	get_type(char **str)
{
	if (ft_strlen(str[0]) == 4 && !ft_strncmp(str[0], "echo", 4))
		return (1);
	else if (ft_strlen(str[0]) == 2 && !ft_strncmp(str[0], "cd", 2))
		return (2);
	else if (ft_strlen(str[0]) == 3 && !ft_strncmp(str[0], "pwd", 3))
		return (3);
	else if (ft_strlen(str[0]) == 6 && !ft_strncmp(str[0], "export", 6))
		return (4);
	else if (ft_strlen(str[0]) == 5 && !ft_strncmp(str[0], "unset", 5))
		return (5);
	else if (ft_strlen(str[0]) == 3 && !ft_strncmp(str[0], "env", 3))
		return (6);
	else if (ft_strlen(str[0]) == 4 && !ft_strncmp(str[0], "exit", 4))
		return (7);
	else
		return (0);
}

int	print_syntax_error(char *str, int i)
{
	if (ft_strncmp(str, "\n", 1) == 0)
		printf("minishell: syntax error near unexpected token `newline'\n");
	else
		printf("minishell: syntax error near unexpected token `%c'\n", str[i]);
	return (0);
}
