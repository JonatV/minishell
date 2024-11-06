/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:04:30 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/06 20:29:56 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE
#include "../../includes/minishell.h"

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

void	execution(int i, t_shell *shell)
{
	char	*valid_path;

	valid_path = find_valid_path(shell->cmd_array[i].data[CMD_NAME], shell->env);
	if (0 == valid_path)
	{
		mini_printf("", shell->cmd_array[i].data[CMD_NAME], ": command not found\n", STDERR_FILENO);
		exit(127);
	}
	prepare_execve_data(&shell->cmd_array[i]);
	execve(valid_path, shell->cmd_array[i].final_cmd_line, shell->env);
	free(valid_path);
	panic("Execve failed", shell);
}

void waiting_for_children(t_shell *shell, int built_in_triggered)
{
	int status;
	pid_t pid;
	int i;
	
	i = 0;
	while (i < shell->cmd_number - built_in_triggered)
	{
		pid = waitpid(shell->pid_array[i], &status, 0);
		if (pid == -1)
			perror("im waiting"); // todo refactor
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

static void	forks_process(t_shell *shell, int i)
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
		pipes_closing(shell);
		execution(i, shell);
	}
	else if (pid < 0)
		panic("Fork", shell);
	else
	{
		shell->pid_array[i] = pid;
		parent_process_close_fds(shell, i);
	}
}

void	shell_executor(t_shell *shell)
{
	int	i;
	int	built_in_triggered;
	
	signal(SIGINT, SIG_IGN);
	g_exit_status = 0;
	built_in_triggered = 0;
	i = 0;
	if (!here_doc_management(shell))
		return ;
	pipes_init(shell);
	while (i < shell->cmd_number)
	{
		if(shell->cmd_array[i].data[CMD_NAME] == NULL)
		{
			i++;
			continue ;
		}
		if (use_builtin_cmd(shell, &i, &built_in_triggered))
			continue ;
		forks_process(shell, i);
		i++;
	}
	set_default_current_fds(shell);
	pipes_free(shell);
	waiting_for_children(shell, built_in_triggered);
}
