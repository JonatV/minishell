/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:33:54 by jveirman          #+#    #+#             */
/*   Updated: 2024/06/03 12:05:59 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include "../../includes/exec.h"
#include "../../includes/signal.h"

/*
#####################################################################
#																	#
#							--- MAIN ---							#
#																	#
#####################################################################
*/

void	shell_init(t_shell *shell, char **envp)
{
	ft_memset(shell, '\0', sizeof(t_shell));
	init_all_cmd(shell);
	dup_env(&shell->env, envp, shell);
	// ft_lstdisplay(shell->env);
	prompt_msg(shell, *shell);
	signals();
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	if (ac != 1 || av[1])
	{
		panic("This program does not accept arguments", NULL);
	}
	shell_init(&shell, envp);
	while (1)
	{
		shell.buf = readline(shell.prompt_msg);
		if (!shell.buf)
		{
			free(shell.buf);
			break ;
			signal_eof(&shell);
		}
		add_history(shell.buf);
		dev_cmd_call(shell);
		free(shell.buf);
	}
	shell_executor(&shell, envp);
	clean("Bye", &shell);
}
