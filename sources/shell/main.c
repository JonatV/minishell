/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:33:54 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/06 00:39:29 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	g_exit_status = 0;

void	shell_init(t_shell *shell, char **envp)
{
	ft_memset(shell, '\0', sizeof(t_shell));
	shell->pid = getpid();
	set_default_current_fds(shell);
	init_env(shell, envp);
	prompt_msg(shell);
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
		signals_handler();
		if (!check_cmd_line_structure(&shell))
			continue ;
		add_history(shell.buf);// todo check where to put it
		tokenizer(&shell);
		if (!shell.tokens_list)
			panic("Error while tokenizing", &shell);
		// display_tokens(shell.tokens_list);
		if (!parsing(&shell))
		{
			free_tokens_list(&shell.tokens_list);
			panic("Error while parsing", &shell);
		}
		free_tokens_list(&shell.tokens_list);
		shell.tokens_list = NULL;
		print_all_cmd(&shell); // dev
		shell_executor(&shell);
		free_after_execution(&shell);
		free(shell.buf);
	}
}
