/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:03:35 by jveirman          #+#    #+#             */
/*   Updated: 2024/06/03 12:04:53 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	forks_process(t_shell *shell, char **envp)
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
			fd_in_management(i, j, *shell);
			fd_out_management(i, j, *shell);
			pipes_closing(shell);
			execution(i, shell, envp);
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
