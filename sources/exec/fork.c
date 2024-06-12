/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:03:35 by jveirman          #+#    #+#             */
/*   Updated: 2024/06/12 12:21:47 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	forks_process(t_shell *shell)
{
	int		i;
	int		j;
	pid_t	pid;

	i = 0;
	j = 0;
	while (i < shell->cmd_number)
	{
		pid = fork();
		if (pid == 0)
		{
			fd_error(shell, i);
			if (is_here_doc_available(shell, i))
				here_doc_exploit(shell, i);
			else
				fd_in_management(i, j, *shell);
			fd_out_management(i, j, *shell);
			pipes_closing(shell);
			execution(i, shell);
		}
		else if (pid < 0)
			panic("Fork", shell);
		j += 2;
		i++;
	}
}

void	waiting_for_children(t_shell shell)
{
	int	i;

	i = 0;
	while (i < shell.cmd_number)
	{
		wait(NULL);
		i++;
	}
}
