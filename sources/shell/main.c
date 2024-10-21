/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:33:54 by jveirman          #+#    #+#             */
/*   Updated: 2024/10/21 16:02:18 by jveirman         ###   ########.fr       */
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

void	shell_init(t_shell *shell, char **envp)
{
	ft_memset(shell, '\0', sizeof(t_shell));
	init_all_cmd(shell);//dev
	init_env(shell, envp);
	prompt_msg(shell);
	signals();
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;
	t_lists	*lst;
	t_all_cmd	all_cmd;
	
	lst = NULL;
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
			// break ;
		}
		add_history(shell.buf);
		parsing(&all_cmd, &(shell.buf), &lst);
		print_all_cmd(&all_cmd);// dev
		free(shell.buf);
		lst = NULL;
		//main_token(shell.buf, &lst);
		//dev_cmd_call(&shell); // dev
	}
	builtin_env(&shell);												// dev	- use to check if the shlvl is correclty updated
	if (ft_strchr(shell.env[ft_arrayfind(shell.env, "SHLVL")], '4'))	// dev	and if minishell can be run in minishell(4 times deep).
		builtin_exit(&shell);											// dev
	shell_executor(&shell);
	builtin_exit(&shell);
}
