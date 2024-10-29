/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:04:30 by jveirman          #+#    #+#             */
/*   Updated: 2024/10/29 14:58:33 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
#####################################################################
#								EXEC								#
#####################################################################
*/

void	shell_executor(t_shell *shell)
{
	here_doc_management(shell);
	update_var_lastarg(shell);
	pipes_init(shell);
	pipes_opening(shell);
	forks_process(shell);
	pipes_closing(shell);
	waiting_for_children(shell);
}
/*
*	@note:	Function that concatenate the two array, CMD_FLAG and CMD ARG,
*			into one null terminated array -> final_cmd_line.
*	@param:	Current command structure
*/
static void	prepare_execve_data(t_cmd *cmd)
{
	char	**data_flag;
	char	**data_arg;
	int		i;
	
	ft_arraypush(&cmd->final_cmd_line, cmd->data[CMD_NAME]);
	if (cmd->data[CMD_FLAG] != NULL)
	{
		data_flag = ft_split(cmd->data[CMD_FLAG], ' ');
		i = -1;
		while (data_flag[++i])
			ft_arraypush(&cmd->final_cmd_line, data_flag[i]);
	}
	if (cmd->data[CMD_ARG] != NULL)
	{
		data_arg = ft_split(cmd->data[CMD_ARG], ' ');
		i = -1;
		while (data_arg[++i])
			ft_arraypush(&cmd->final_cmd_line, data_arg[i]);
	}
}

/*
* TODO:
*	- clean the exit(0) from builtin process
*		I don't understand yet how to handle the built_in command error
*/
void	execution(int i, t_shell *shell)
{
	int		built_in_index;
	char	*valid_path;
	
	built_in_index = is_builtin(shell->cmd_array[i].data[CMD_NAME]);
	if (built_in_index > -1)
	{
		select_builtin(shell, i, built_in_index);
		exit(0);
	}
	else
	{
		valid_path = find_valid_path(shell->cmd_array[i].data[CMD_NAME], shell->env);
		if (0 == valid_path)
		{
			ft_putstr_fd("Error : No such command exists in the system.\n", \
			STDERR_FILENO);
			exit(127);
		}
		prepare_execve_data(&shell->cmd_array[i]);
		execve(valid_path, shell->cmd_array[i].final_cmd_line, shell->env);
		free(valid_path);
		panic("Execve failed", shell);
	}
}
