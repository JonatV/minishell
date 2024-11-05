#include "../../includes/minishell.h"

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
	execve(valid_path, shell->cmd_array[i].final_cmd_line, shell->env);
	free(valid_path);
	panic("Execve failed", shell);
}

void shell_executor(t_shell *shell)
{
	int num_pipes;
	int num_cmd;
	int i;
	int j;
	pid_t pid;
	int built_in_index;
	int built_in_triggered;

	here_doc_management(shell);
	num_pipes = shell->cmd_number - 1;
	num_cmd = shell->cmd_number;
	shell->pipefds = malloc(sizeof(int *) * (num_pipes * 2));
	if (!shell->pipefds)
		panic("malloc pipes", shell);
	i = 0;
	while (i < num_pipes)
	{
		shell->pipefds[i] = malloc(sizeof(int) * 2);
		if (!shell->pipefds[i])
			panic("malloc pipes", shell);
		if (pipe(shell->pipefds[i]) < 0)
			panic("Pipe opening", shell);
		i++;
	}
	built_in_triggered = 0;
	i = 0;
	while (i < num_cmd)
	{
		built_in_index = is_builtin(shell->cmd_array[i].data[CMD_NAME]);
		if (built_in_index > -1 && (built_in_index == BUILTIN_EXPORT || built_in_index == BUILTIN_UNSET))
		{
			built_in_triggered++; // todo can be used to change the to check for the wait (i.e. num_cmd - built_in_triggered) cause no fork here in bultin
			select_builtin(shell, i, built_in_index); // todo send the correct fd
			i++;
			continue;
		}
		pid = fork();
		if (pid == 0)
		{
			fd_error(shell, i);
			if (is_here_doc_available(shell, i))
				here_doc_exploit(shell, i);
			else
			{
				if (shell->cmd_array[i].fd_in != DEFAULT_FD)
					dup2(shell->cmd_array[i].fd_in, STDIN_FILENO);
				else if (i > 0) // if current is not the first read from previous pipe read
					dup2(shell->pipefds[i - 1][PIPE_READ_END], STDIN_FILENO);
			}
			if (shell->cmd_array[i].fd_out != DEFAULT_FD)
				dup2(shell->cmd_array[i].fd_out, STDOUT_FILENO);
			else if (i < num_cmd - 1) // means all but the last command
				dup2(shell->pipefds[j + 1], STDOUT_FILENO);
			j = 0;
			while (j < num_pipes)
			{
				close(shell->pipefds[j][PIPE_READ_END]);
				close(shell->pipefds[j][PIPE_WRITE_END]);
				j++;
			}
			execution(i, shell);
		}
		else if (pid < 0)
			panic("Fork", shell);
		i++;
	}
	// i = 0;
	// while (i < shell->cmd_number * 2)
	// {
	// 	close(shell->pipefds[i]);
	// 	i++;
	// }
	// int status;
	// i = 0;
	// while (i < shell->cmd_number)
	// {
	// 	wait(&status);
	// 	i++;
	// }
}
