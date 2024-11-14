/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 10:33:13 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/14 14:22:15 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
* INFO:
*	we will need to open the terminal for every here doc
*	And loop through until it reaches the last one.
*	When at the last index of delimiter, it will store it
*	to the here_doc_in string variable.
*	Then during the cmd execution, if the cmd has this string not set
*	to NULL, then we will use this string has an input.
*/
static bool	here_doc_found(t_shell *shell, int i)
{
	int		j;
	char	**delimiter;

	j = 0;
	delimiter = shell->cmd_array[i].here_doc_delimiter;
	while (delimiter && delimiter[j])
	{
		if (shell->cmd_array[i].here_doc_input)
			free(shell->cmd_array[i].here_doc_input);
		shell->cmd_array[i].here_doc_input = NULL;
		shell->cmd_array[i].here_doc_input = \
			to_the_delimiter(delimiter[j], shell);
		if (g_exit_status == SUBPROCESS_SIG)
		{
			g_exit_status = 1;
			return (false);
		}
		if (!shell->cmd_array[i].here_doc_delimiter[j + 1])
			break ;
		j++;
	}
	return (true);
}

/*
* INFO:
*	Checks for each command whether one or more 
*	here_doc_delimiter delimiters are defined.
*/
bool	here_doc_management(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->cmd_number)
	{
		if (!shell->cmd_array[i].here_doc_delimiter)
		{
			i++;
			continue ;
		}
		if (!here_doc_found(shell, i))
			return (false);
		i++;
	}
	return (true);
}

static void	handle_parent_process(int pipe_fd[2], pid_t pid, t_shell *shell)
{
	if (close(pipe_fd[1]) == -1)
		panic("close failed", shell);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		panic("dup2 failed", shell);
	if (waitpid(pid, NULL, 0) == -1)
		panic("waitpid failed", shell);
	if (close(pipe_fd[0]) == -1)
		panic("close failed", shell);
}

void	here_doc_exploit(t_shell *shell, int i)
{
	int		pipe_fd[2];
	pid_t	pid;
	char	*text_input;

	if (0 > pipe(pipe_fd))
		panic("pipe failed", shell);
	pid = fork();
	if (-1 == pid)
		panic("fork failed", shell);
	if (pid)
		handle_parent_process(pipe_fd, pid, shell);
	if (0 == pid)
	{
		if (close(pipe_fd[0]) == -1)
			panic("close failed", shell);
		text_input = shell->cmd_array[i].here_doc_input;
		ft_putstr_fd(text_input, pipe_fd[1]);
		if (text_input)
			free(text_input);
		if (close(pipe_fd[1]) == -1)
			panic("close failed", shell);
		exit(EXIT_SUCCESS);
	}
}
