/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:33:54 by jveirman          #+#    #+#             */
/*   Updated: 2024/09/16 11:23:29 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include "../../includes/exec.h"
#include "../../includes/signal.h"
#include "../../includes/built_in.h"
#include "../../includes/built_in.h"
#include "../../includes/built_in.h"
#include "../../includes/token.h"

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
			break ;
			signal_eof(&shell);
		}
		add_history(shell.buf);
		main_token(shell.buf, &lst); 
		//dev_cmd_call(&shell); // dev
		free(shell.buf);
	}
	builtin_env(&shell);
	if (ft_strchr(shell.env[ft_arrayfind(shell.env, "SHLVL")], '9'))// dev
		clean("Bye", &shell);// dev
	shell_executor(&shell);
	clean("Bye", &shell);
}
