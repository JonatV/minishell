/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:33:54 by jveirman          #+#    #+#             */
/*   Updated: 2024/10/23 14:24:24 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include "../../includes/exec.h"
#include "../../includes/signal.h"
#include "../../includes/built_in.h"
#include "../../includes/built_in.h"
#include "../../includes/built_in.h"

/*
#####################################################################
#																	#
#							--- MAIN ---							#
#																	#
#####################################################################
*/
/* this is the test merge*/

void	shell_init(t_shell *shell, char **envp)
{
	ft_memset(shell, '\0', sizeof(t_shell));
	// init_all_cmd(shell);//dev
	init_env(shell, envp);
	prompt_msg(shell);
	signals();
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;
	
	if (!envp)
		panic("Error no environment pointer", NULL);
	if (ac != 1 || av[1])
		panic("This program does not accept arguments", NULL);
	shell_init(&shell, envp);
	while (1)
	{
		shell.buf = readline(shell.prompt_msg);
		if (!shell.buf)
		{
			free(shell.buf);
			signal_eof(&shell);
		}
		add_history(shell.buf);
		parsing(&shell, &(shell.buf));
		print_all_cmd(&shell); // dev
		shell_executor(&shell);
		free(shell.buf);
		//dev_cmd_call(&shell); // dev
	}
	builtin_env(&shell);												// dev	- use to check if the shlvl is correclty updated
	if (ft_strchr(shell.env[ft_arrayfind(shell.env, "SHLVL")], '4'))	// dev	and if minishell can be run in minishell(4 times deep).
		builtin_exit(&shell);											// dev
	shell_executor(&shell);
	builtin_exit(&shell);
}
