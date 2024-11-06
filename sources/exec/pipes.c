/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:24:36 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/06 20:25:44 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pipes_init(t_shell *shell)
{
	int	i;

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
	int	num_pipes;
	int	i;

	i = 0;
	num_pipes = shell->cmd_number - 1;
	while (i < num_pipes)
	{
		if (pipe(shell->pipefds[i]) < 0)
			panic("Pipe opening", shell);
		i++;
	}
}

void	pipes_closing(t_shell *shell)
{
	int	i;
	
	i = 0;
	while (i < shell->cmd_number - 1)
	{
		close(shell->pipefds[i][PIPE_READ_END]);
		close(shell->pipefds[i][PIPE_WRITE_END]);
		i++;
	}
}

void	pipes_free(t_shell *shell)
{
	int	i;
	
	i = 0;
	while (i < shell->cmd_number - 1)
	{
		close(shell->pipefds[i][PIPE_READ_END]);
		close(shell->pipefds[i][PIPE_WRITE_END]);
		free(shell->pipefds[i]);
		i++;
	}
	free(shell->pipefds);
	shell->pipefds = NULL;
}

void parent_process_close_fds(t_shell *shell, int i)
{
	if (i < shell->cmd_number - 1 && shell->pipefds[i])
	{
		close(shell->pipefds[i][PIPE_WRITE_END]);
		if (shell->cmd_array[i].fd_in >= 0)
			close(shell->cmd_array[i].fd_in);
	}
	if (i > 0)
		close(shell->pipefds[i - 1][PIPE_READ_END]);
}
