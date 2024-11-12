/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:24:36 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/12 18:27:16 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pipes_init(t_shell *shell)
{
	int	i;

	if (shell->cmd_number == 1)
		return ;
	shell->pipefds = malloc(sizeof(int *) * ((shell->cmd_number - 1)));
	if (!shell->pipefds)
		panic("malloc pipes", shell);
	i = 0;
	while (i < shell->cmd_number - 1)
	{
		shell->pipefds[i] = malloc(sizeof(int) * 2);
		if (!shell->pipefds[i])
			panic("malloc pipes", shell);
		if (pipe(shell->pipefds[i]) == -1)
			panic("pipe failed", shell);
		i++;
	}
}

void	pipes_opening(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->cmd_number - 1)
	{
		if (pipe(shell->pipefds[i]) < 0)
			panic("Pipe opening", shell);
		i++;
	}
}

void	pipes_closing(t_shell *shell, int i)
{
	if (i == 0)
		return ;
	if (close(shell->pipefds[i - 1][PIPE_READ_END]) == -1)
		panic("Pipe closing", shell);
	if (close(shell->pipefds[i - 1][PIPE_WRITE_END]) == -1)
		panic("Pipe closing", shell);
}

void	pipes_free(t_shell *shell)
{
	int	i;

	if (shell->cmd_number == 1)
		return ;
	i = 0;
	while (i < shell->cmd_number - 1)
		free(shell->pipefds[i++]);
	free(shell->pipefds);
	shell->pipefds = NULL;
}

void	parent_process_close_fds(t_shell *shell, int i)
{
	if (i == 0)
		return ;
	if (shell->pipefds[i - 1])
	{
		if (close(shell->pipefds[i - 1][PIPE_WRITE_END]) == -1)
			panic("Pipe closing", shell);
		if (shell->cmd_array[i].fd_in >= 0)
		{
			if (close(shell->cmd_array[i].fd_in) == -1)
				panic("Pipe closing", shell);
		}
	}
	if (i > 0)
		if (close(shell->pipefds[i - 1][PIPE_READ_END]) == -1)
			panic("Pipe closing", shell);
}
