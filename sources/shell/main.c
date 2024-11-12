/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:33:54 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/12 01:51:57 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	g_exit_status = 0;

void	shell_init(t_shell *shell, char **envp)
{
	ft_memset(shell, '\0', sizeof(t_shell));
	shell->pid = getpid();
	set_default_current_fds(shell);
	shell->number_of_pipe = 0;
	init_env(shell, envp);
	prompt_msg(shell);
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	if (!envp)
		return (error_msg("no environment"));
	if (ac != 1 || av[1])
		return (error_msg("This program does not accept arguments"));
	shell_init(&shell, envp);
	while (1)
	{
		signals_handler();
		if (!check_cmd_line_structure(&shell))
			continue ;
		add_history(shell.buf);
		if (!tokenizer(&shell))
			continue ;
		if (!shell.tokens_list)
			panic("Error while tokenizing", &shell);
		if (!parsing(&shell))
			continue ;
		if (!check_for_empty_cmd(&shell))
			continue ;
		free_tokens_list(&shell.tokens_list);
		shell.tokens_list = NULL;
		shell_executor(&shell);
		clean(NULL, &shell, false);
	}
}
