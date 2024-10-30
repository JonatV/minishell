/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:33:54 by jveirman          #+#    #+#             */
/*   Updated: 2024/10/29 21:42:56 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	// init_all_cmd(shell);//dev
	init_env(shell, envp);
	prompt_msg(shell);
	signals_handler();
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;
	t_token	*tokens;

	tokens = NULL;
	if (!envp)
		panic("Error no environment pointer", NULL);
	if (ac != 1 || av[1])
		panic("This program does not accept arguments", NULL);
	shell_init(&shell, envp);
	while (1)
	{
		if (!check_cmd_line_structure(&shell))
			continue ;
		add_history(shell.buf);
		tokens = tokenize_input(&shell);
		// display_tokens(tokens);
		parsing(&shell, &tokens);
		// print_all_cmd(&shell); // dev
		shell_executor(&shell);
		free(shell.buf);
	}
}
