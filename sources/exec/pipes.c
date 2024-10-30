/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:24:36 by jveirman          #+#    #+#             */
/*   Updated: 2024/10/30 20:11:14 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pipes_init(t_shell *shell)
{
	int	i;

	shell->pipefds = malloc(sizeof(int *) * ((shell->cmd_number - 1) * 2));
	if (!shell->pipefds)
		panic("malloc pipes", shell);
	i = 0;
	while (i < shell->cmd_number)
	{
		shell->pipefds[i] = malloc(sizeof(int) * 2);
		if (!shell->pipefds[i])
			panic("malloc pipes", shell);
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
	int	num_pipes;
	int	i;

	i = 0;
	num_pipes = shell->cmd_number - 1;
	while (i < num_pipes)
	{
		close(shell->pipefds[i][PIPE_READ_END]);
		close(shell->pipefds[i][PIPE_WRITE_END]);
		i++;
	}
}
