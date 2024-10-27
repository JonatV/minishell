/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:24:36 by jveirman          #+#    #+#             */
/*   Updated: 2024/10/27 10:56:53 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
#####################################################################
#																	#
#								PIPES								#
#																	#
#####################################################################
*/

void	pipes_init(t_shell *shell)
{
	int	num_pipes;

	num_pipes = shell->cmd_number;
	shell->pipefds = malloc(sizeof(int) * ((num_pipes * 2)));
	if (!shell->pipefds)
		panic("malloc pipes", shell);
}

void	pipes_opening(t_shell *shell)
{
	int	num_pipes;
	int	i;

	num_pipes = shell->cmd_number;
	i = 0;
	while (i < num_pipes)
	{
		if (pipe(shell->pipefds + i * 2) < 0)
			panic("Pipe opening", shell);
		i++;
	}
}

void	pipes_closing(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->cmd_number * 2)
	{
		close(shell->pipefds[i]);
		i++;
	}
}
