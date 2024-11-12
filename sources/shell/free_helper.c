/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 21:26:29 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/12 23:56:26 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_shell_struct(t_shell *shell, bool free_env)
{
	int	i;

	if (shell->buf)
		free(shell->buf);
	shell->buf = NULL;
	if (shell->pipefds)
	{
		i = -1;
		while (++i < shell->cmd_number - 1)
			free(shell->pipefds[i]);
		free(shell->pipefds);
		shell->pipefds = NULL;
	}
	if (free_env && shell->env)
	{
		ft_arrayfree(shell->env);
		shell->env = NULL;
	}
}

static void	free_data(t_shell *shell, int i)
{
	if (shell->cmd_array[i].data)
	{
		if (shell->cmd_array[i].data[CMD_NAME])
			free(shell->cmd_array[i].data[CMD_NAME]);
		if (shell->cmd_array[i].data[CMD_FLAG])
			free(shell->cmd_array[i].data[CMD_FLAG]);
		if (shell->cmd_array[i].data[CMD_ARG])
			free(shell->cmd_array[i].data[CMD_ARG]);
	}
}

void	free_cmd_array_struct(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->cmd_number && shell->cmd_array)
	{
		free_data(shell, i);
		if (shell->cmd_array[i].here_doc_delimiter)
			ft_arrayfree(shell->cmd_array[i].here_doc_delimiter);
		if (shell->cmd_array[i].here_doc_input)
			free(shell->cmd_array[i].here_doc_input);
		if (shell->cmd_array[i].final_cmd_line)
			ft_arrayfree(shell->cmd_array[i].final_cmd_line);
		if (shell->cmd_array[i].file_name_in)
			free(shell->cmd_array[i].file_name_in);
		if (shell->cmd_array[i].file_name_out)
			free(shell->cmd_array[i].file_name_out);
		i++;
	}
	if (shell->cmd_array)
		free(shell->cmd_array);
	shell->cmd_array = NULL;
}
