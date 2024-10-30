/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:04:30 by jveirman          #+#    #+#             */
/*   Updated: 2024/10/30 00:45:10 by jveirman         ###   ########.fr       */
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
	printf("\n\e[1;31m/*----------------				start shell executor				---------------*/\e[0m\n");
	here_doc_management(shell);
	update_var_lastarg(shell);
	pipes_init(shell);
	pipes_opening(shell);
	forks_process(shell);
	pipes_closing(shell);
	waiting_for_children(shell);
	printf("\n\e[1;31m/*----------------				end shell executor				---------------*/\e[0m\n");
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

// /*
// * TODO:
// *	- clean the exit(0) from builtin process
// *		I don't understand yet how to handle the built_in command error
// */
// void	execution(int i, t_shell *shell)
// {
// 	int		built_in_index;
// 	char	*valid_path;
	
// 	built_in_index = is_builtin(shell->cmd_array[i].data[CMD_NAME]);
// 	if (built_in_index > -1)
// 	{
// 		select_builtin(shell, i, built_in_index);
// 		exit(0);
// 	}
// 	else
// 	{
// 		valid_path = find_valid_path(shell->cmd_array[i].data[CMD_NAME], shell->env);
// 		if (0 == valid_path)
// 		{
// 			ft_putstr_fd("Error : No such command exists in the system.\n", STDERR_FILENO);
// 			exit(127);
// 		}
// 		prepare_execve_data(&shell->cmd_array[i]);
// 		execve(valid_path, shell->cmd_array[i].final_cmd_line, shell->env);
// 		free(valid_path);
// 		panic("Execve failed", shell);
// 	}
// }


// void	shell_executor(t_shell *shell)
// {
// 	int	num_pipes = shell->cmd_number;
// 	int	i = 0;
// 	int status;
// 	pid_t pid;

// 	here_doc_management(shell);
// 	update_var_lastarg(shell);
// 	printf("cmd_number: %d\n", shell->cmd_number);
// 	// Setup pipes for multi-command pipelines
// 	if (shell->cmd_number > 1)
// 	{
// 		shell->pipefds = malloc(sizeof(int) * (num_pipes - 1) * 2);
// 		if (!shell->pipefds)
// 			panic("malloc pipes", shell);
// 		for (int k = 0; k < num_pipes - 1; k++)
// 			if (pipe(shell->pipefds + k * 2) < 0)
// 				panic("Pipe opening", shell);
// 	}

// 	for (i = 0; i < shell->cmd_number; i++)
// 	{
// 		int is_builtin_cmd = is_builtin(shell->cmd_array[i].data[CMD_NAME]);

// 		// Skip fork for environment-altering built-ins
// 		if (is_builtin_cmd > -1 && (is_builtin_cmd == BUILTIN_EXPORT || is_builtin_cmd == BUILTIN_UNSET))
// 		{
// 			select_builtin(shell, i, is_builtin_cmd);
// 			continue;
// 		}

// 		pid = fork();
// 		if (pid == 0)  // Child process
// 		{
// 			fd_error(shell, i);

// 			// Redirect input/output based on pipeline position
// 			if (i > 0)
// 				dup2(shell->pipefds[(i - 1) * 2], STDIN_FILENO);
// 			if (i < shell->cmd_number - 1)
// 				dup2(shell->pipefds[i * 2 + 1], STDOUT_FILENO);

// 			// Close all pipe FDs
// 			for (int k = 0; k < 2 * (num_pipes - 1); k++)
// 				close(shell->pipefds[k]);

// 			execution(i, shell);
// 		}
// 		else if (pid < 0)
// 			panic("Fork failed", shell);
// 	}

// 	// Close pipe FDs in parent
// 	for (int k = 0; k < 2 * (num_pipes - 1); k++)
// 		close(shell->pipefds[k]);

// 	// Wait for child processes
// 	for (i = 0; i < shell->cmd_number; i++)
// 		wait(&status);
// }

void execution(int i, t_shell *shell)
{
	char *valid_path;

	valid_path = find_valid_path(shell->cmd_array[i].data[CMD_NAME], shell->env);
	if (0 == valid_path)
	{
		ft_putstr_fd("Error : No such command exists in the system.\n", STDERR_FILENO);
		exit(127);
	}
	prepare_execve_data(&shell->cmd_array[i]);
	printf("valid_path: %s\n", valid_path);
	ft_arrayprint(shell->cmd_array[i].final_cmd_line, " ");
	write(1, "\n", 1);
	execve(valid_path, shell->cmd_array[i].final_cmd_line, shell->env);
	free(valid_path);
	panic("Execve failed", shell);
}

// void shell_executor(t_shell *shell)
// {
// 	int num_pipes;
// 	int i;
// 	int j;
// 	pid_t pid;
// 	int built_in_index;

// 	printf("cmd_number: %d\n", shell->cmd_number);
// 	here_doc_management(shell);
// 	update_var_lastarg(shell);
// 	if (shell->cmd_number > 1)
// 	{
// 		num_pipes = shell->cmd_number;
// 		shell->pipefds = malloc(sizeof(int) * ((num_pipes - 1 * 2)));
// 		if (!shell->pipefds)
// 			panic("malloc pipes", shell);
// 		i = 0;
// 		while (i < num_pipes - 1)
// 		{
// 			if (pipe(shell->pipefds + i * 2) < 0)
// 				panic("Pipe opening", shell);
// 			i++;
// 		}
// 	}
// 	i = 0;
// 	j = 0;
// 	while (i < shell->cmd_number)
// 	{
// 		built_in_index = is_builtin(shell->cmd_array[i].data[CMD_NAME]);
// 		if (built_in_index > -1 && (built_in_index == BUILTIN_EXPORT || built_in_index == BUILTIN_UNSET))
// 		{
// 			if (is_here_doc_available(shell, i))
// 				here_doc_exploit(shell, i);
// 			else
// 			{
// 				if (shell->cmd_array[i].fd_in != DEFAULT_FD)
// 				{
// 					dup2(shell->cmd_array[i].fd_in, STDIN_FILENO);
// 				}
// 				else if (i != 0)
// 				{
// 					dup2(shell->pipefds[j - 2], STDIN_FILENO);
// 				}
// 			}
// 			if (shell->cmd_array[i].fd_out != DEFAULT_FD)
// 			{
// 				dup2(shell->cmd_array[i].fd_out, STDOUT_FILENO);
// 			}
// 			else if (i != (shell->cmd_number - 1))
// 			{
// 				dup2(shell->pipefds[j + 1], STDOUT_FILENO);
// 			}
// 			select_builtin(shell, i, built_in_index);
// 			i++;
// 			j += 2;
// 			continue;
// 		}
// 		pid = fork();
// 		if (pid == 0)
// 		{
// 			fd_error(shell, i);
// 			if (is_here_doc_available(shell, i))
// 				here_doc_exploit(shell, i);
// 			else
// 			{
// 				if (shell->cmd_array[i].fd_in != DEFAULT_FD)
// 				{
// 					dup2(shell->cmd_array[i].fd_in, STDIN_FILENO);
// 				}
// 				else if (i != 0)
// 				{
// 					dup2(shell->pipefds[j - 2], STDIN_FILENO);
// 				}
// 			}
// 			if (shell->cmd_array[i].fd_out != DEFAULT_FD)
// 			{
// 				dup2(shell->cmd_array[i].fd_out, STDOUT_FILENO);
// 			}
// 			else if (i != (shell->cmd_number - 1))
// 			{
// 				dup2(shell->pipefds[j + 1], STDOUT_FILENO);
// 			}
// 			if (shell->cmd_number > 1)
// 			{
// 				i = 0;
// 				while (i < shell->cmd_number * 2)
// 				{
// 					close(shell->pipefds[i]);
// 					i++;
// 				}
// 			}
// 			execution(i, shell);
// 		}
// 		else if (pid < 0)
// 			panic("Fork", shell);
// 		j += 2;
// 		i++;
// 	}
// 	if (shell->cmd_number > 1)
// 	{
// 		i = 0;
// 		while (i < shell->cmd_number * 2)
// 		{
// 			close(shell->pipefds[i]);
// 			i++;
// 		}
// 	}
// 	int status;
// 	i = 0;
// 	while (i < shell->cmd_number)
// 	{
// 		wait(&status);
// 		i++;
// 	}
// }
	