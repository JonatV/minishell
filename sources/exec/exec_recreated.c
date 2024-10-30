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
	int i;
	int j;
	pid_t pid;
	int built_in_index;

	here_doc_management(shell);
	update_var_lastarg(shell);
	if (shell->cmd_number > 1)
	{
		num_pipes = shell->cmd_number;
		shell->pipefds = malloc(sizeof(int) * ((num_pipes - 1 * 2)));
		if (!shell->pipefds)
			panic("malloc pipes", shell);
		i = 0;
		while (i < num_pipes - 1)
		{
			if (pipe(shell->pipefds + i * 2) < 0)
				panic("Pipe opening", shell);
			i++;
		}
	}
	i = 0;
	j = 0;
	while (i < shell->cmd_number)
	{
		built_in_index = is_builtin(shell->cmd_array[i].data[CMD_NAME]);
		if (built_in_index > -1 && (built_in_index == BUILTIN_EXPORT || built_in_index == BUILTIN_UNSET))
		{
			select_builtin(shell, i, built_in_index);
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
				{
					dup2(shell->cmd_array[i].fd_in, STDIN_FILENO);
				}
				else if (i != 0)
				{
					dup2(shell->pipefds[j - 2], STDIN_FILENO);
				}
			}
			if (shell->cmd_array[i].fd_out != DEFAULT_FD)
			{
				dup2(shell->cmd_array[i].fd_out, STDOUT_FILENO);
			}
			else if (i != (shell->cmd_number - 1))
			{
				dup2(shell->pipefds[j + 1], STDOUT_FILENO);
			}
			if (shell->cmd_number > 1)
			{
				i = 0;
				while (i < shell->cmd_number * 2)
				{
					close(shell->pipefds[i]);
					i++;
				}
			}
			execution(i, shell);
		}
		else if (pid < 0)
			panic("Fork", shell);
		j += 2;
		i++;
	}
	if (shell->cmd_number > 1)
	{
		i = 0;
		while (i < shell->cmd_number * 2)
		{
			close(shell->pipefds[i]);
			i++;
		}
	}
	int status;
	i = 0;
	while (i < shell->cmd_number)
	{
		wait(&status);
		i++;
	}
}
