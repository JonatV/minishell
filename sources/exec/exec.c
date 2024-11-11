/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:04:30 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/12 00:36:20 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE
#include "../../includes/minishell.h"

/*
*	@note:	Function that concatenate the two array, CMD_FLAG and CMD ARG,
*			into one null terminated array -> final_cmd_line.
*	@param:	Current command structure
*/
static bool	prepare_execve_data(t_cmd *cmd)
{
	char	**data_flag;
	char	**data_arg;
	int		i;
	
	if (!ft_arraypush(&cmd->final_cmd_line, cmd->data[CMD_NAME]))
		return (false);
	if (cmd->data[CMD_FLAG] != NULL)
	{
		data_flag = ft_split(cmd->data[CMD_FLAG], ' ');
		if (!data_flag)
			return (false);
		i = -1;
		while (data_flag[++i])
		{
			if (!ft_arraypush(&cmd->final_cmd_line, data_flag[i]))
			{
				ft_arrayfree(data_flag);
				return (false);
			}
		}
	}
	if (cmd->data[CMD_ARG] != NULL)
	{
		data_arg = ft_split(cmd->data[CMD_ARG], ' ');
		if (!data_arg)
		{
			ft_arrayfree(data_flag);
			return (false);
		}
		i = -1;
		while (data_arg[++i])
		{
			if (!ft_arraypush(&cmd->final_cmd_line, data_arg[i]))
			{
				ft_arrayfree(data_flag);
				ft_arrayfree(data_arg);
				return (false);
			}
		}
	}
	return (true);
}

void	execution(int i, t_shell *shell)
{
	char	*valid_path;

	valid_path = NULL;
	if (!shell->cmd_array[i].data[CMD_NAME])
		exit(0);
	valid_path = find_valid_path(shell->cmd_array[i].data[CMD_NAME], shell->env, shell);
	if (0 == valid_path)
	{
		mini_printf("", shell->cmd_array[i].data[CMD_NAME], ": command not found\n", STDERR_FILENO);
		free_cmd_array_struct(shell);
		exit(127);
	}
	if (!prepare_execve_data(&shell->cmd_array[i]))
	{
		free(valid_path);
		valid_path = NULL;
		panic(ERR_MALLOC, shell);
	}
	execve(valid_path, shell->cmd_array[i].final_cmd_line, shell->env);
	if (valid_path)
		free(valid_path);
	error_msg("execve failed");
	exit(1);
}

void waiting_for_children(t_shell *shell)
{
	int status;
	int i;
	
	i = 0;
	while (i < shell->cmd_number)
	{
		if (waitpid(shell->pid_array[i], &status, 0) == -1)
			panic("waitpid failed", shell);
		if (i == shell->cmd_number - 1)
		{
			if (WIFEXITED(status))
				g_exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				g_exit_status = 128 + WTERMSIG(status);
		}
		i++;
	}
}

static void	forks_process(t_shell *shell, int i, int built_in_index)
{
	pid_t	pid;

	signal(SIGINT, signal_ctlc_on_fork);
	signal(SIGQUIT, SIG_DFL);
	pid = fork();
	if (pid == 0)
	{
		fd_error(shell, i);
		if (is_here_doc_available(shell, i))
			here_doc_exploit(shell, i);
		else
			fd_in_management(shell, i);
		fd_out_management(shell, i);
		pipes_closing(shell, i);
		execute_builtin(shell, i, built_in_index);
		execution(i, shell);
	}
	else if (pid < 0)
		panic("fork failed", shell);
	else
	{
		shell->pid_array[i] = pid;
		parent_process_close_fds(shell, i);
	}
}

void	shell_executor(t_shell *shell)
{
	int	i;
	int	built_in_index;
	
	signal(SIGINT, SIG_IGN);
	g_exit_status = 0;
	i = 0;
	if (!here_doc_management(shell))
		return ;
	pipes_init(shell);
	while (i < shell->cmd_number)
	{
		built_in_index = is_builtin(shell->cmd_array[i].data[CMD_NAME]);
		use_builtin_env_changer(shell, &i, built_in_index);
		forks_process(shell, i, built_in_index);
		i++;
	}
	set_default_current_fds(shell);
	pipes_free(shell);
	waiting_for_children(shell);
}
