
# include "../../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <string.h>
# include <errno.h>
# include <stdbool.h>
# include <signal.h>
# define CMD_NAME 0
# define CMD_FLAG 1
# define CMD_ARG 2
# define CMD_END 3
# define PIPE_WRITE_END 1
# define PIPE_READ_END 0

typedef struct s_cmd
{
	char	*data[4];
	char	*valid_path;
	bool	is_builtin;
}	t_cmd;

typedef struct s_shell
{
	int		cmd_number;
	t_cmd	*cmd_array;
	int		**pipefds;
}	t_shell;


static void	init_struct(t_shell *shell)
{
	shell->cmd_number = 3;
	shell->cmd_array = malloc(shell->cmd_number * (sizeof(t_cmd)));
	if (shell->cmd_array == NULL)
		exit(EXIT_FAILURE);
	shell->cmd_array[0].data[CMD_NAME] = "cat";
	shell->cmd_array[0].data[CMD_FLAG] = "-n";
	shell->cmd_array[0].data[CMD_ARG] = "Makefile";
	shell->cmd_array[0].data[CMD_END] = NULL;
	shell->cmd_array[0].valid_path = "/bin/cat";
	shell->cmd_array[0].is_builtin = false;

	shell->cmd_array[1].data[CMD_NAME] = "grep";
	shell->cmd_array[1].data[CMD_FLAG] = "-ni";
	shell->cmd_array[1].data[CMD_ARG] = "flag";
	shell->cmd_array[1].data[CMD_END] = NULL;
	shell->cmd_array[1].valid_path = "/usr/bin/grep";
	shell->cmd_array[1].is_builtin = false;

	shell->cmd_array[2].data[CMD_NAME] = "grep";
	shell->cmd_array[2].data[CMD_FLAG] = "-n";
	shell->cmd_array[2].data[CMD_ARG] = "CC";
	shell->cmd_array[2].data[CMD_END] = NULL;
	shell->cmd_array[2].valid_path = "/usr/bin/grep";
	shell->cmd_array[2].is_builtin = false;
}

int main(int argc, char const *argv[], char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	
	t_shell	shell;
	int	num_pipes;
	int	num_cmd;
	int	i;
	pid_t pid;

	init_struct(&shell);

	num_pipes = shell.cmd_number - 1;
	num_cmd = shell.cmd_number;
	shell.pipefds = malloc(sizeof(int *) * (num_pipes * 2));
	i = 0;
	while (i < num_cmd)
	{
		shell.pipefds[i] = malloc(sizeof(int) * 2);
		i++;
	}

	i = 0;
	while (i < num_pipes)
	{
		pipe(shell.pipefds[i]);
		i++;
	}

	i = 0;
	while (i < num_cmd)
	{
		if (shell.cmd_array[i].is_builtin)
		{
			ft_putstr_fd("exeaquo\n", shell.pipefds[i][PIPE_WRITE_END]);
			ft_putstr_fd("tetraedre\n", shell.pipefds[i][PIPE_WRITE_END]);
			ft_putstr_fd("carabine a beurre\n", shell.pipefds[i][PIPE_WRITE_END]);
			ft_putstr_fd("mon ex\n", shell.pipefds[i][PIPE_WRITE_END]);
			i++;
			continue;
		}
		pid = fork();
		if (pid == 0)
		{
			printf("\nCurrent i = [%d]\n", i);
			printf("num_pipes = [%d]\n", num_pipes);
			printf("num_cmd = [%d]\n", num_cmd);
			printf("pipefd[i][READ] = [%d]\n", shell.pipefds[i][PIPE_READ_END]);
			printf("pipefd[i][WRITE] = [%d]\n", shell.pipefds[i][PIPE_WRITE_END]);
			if (i > 0)
				dup2(shell.pipefds[i - 1][PIPE_READ_END], STDIN_FILENO);
			if (i < num_cmd - 1) // means the last cmd
				dup2(shell.pipefds[i][PIPE_WRITE_END], STDOUT_FILENO);

			for (int j = 0; j < num_pipes; j++)
			{
				close(shell.pipefds[j][PIPE_READ_END]);
				close(shell.pipefds[j][PIPE_WRITE_END]);
			}
			printf("before execve...\n");
			execve(shell.cmd_array[i].valid_path, shell.cmd_array[i].data, envp);
		}
		i++;
	}
	return 0;
}
