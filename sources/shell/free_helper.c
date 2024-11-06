/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 21:26:29 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/06 01:03:59 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_after_execution(t_shell *shell, bool with_pipefds)
{
	int	i;
	
	i = 0;
	if (shell->cmd_array)
	{
		while (i < shell->cmd_number)
		{
			if (shell->cmd_array[i].data[CMD_NAME])
				free(shell->cmd_array[i].data[CMD_NAME]);
			if (shell->cmd_array[i].data[CMD_FLAG])
				free(shell->cmd_array[i].data[CMD_FLAG]);
			if (shell->cmd_array[i].data[CMD_ARG])
				free(shell->cmd_array[i].data[CMD_ARG]);
			if (shell->cmd_array[i].here_doc_delimiter)
				ft_arrayfree(shell->cmd_array[i].here_doc_delimiter);
			if (shell->cmd_array[i].here_doc_input)
				free(shell->cmd_array[i].here_doc_input);
			if (shell->cmd_array[i].final_cmd_line)
				ft_arrayfree(shell->cmd_array[i].final_cmd_line);
			i++;
		}
		if (with_pipefds && g_exit_status == 0)
			free_pipefds(shell);
		if (shell->cmd_array)
			free(shell->cmd_array);
		shell->cmd_array = NULL;
		if (shell->buf)
			free(shell->buf);
		shell->buf = NULL;
	}
}
