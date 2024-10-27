/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listener.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:29:01 by jveirman          #+#    #+#             */
/*   Updated: 2024/10/27 11:21:39 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define _GNU_SOURCE
#include "../../includes/minishell.h"

void	sigint_handler(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sigeof_handler(t_shell *shell)
{
	builtin_exit(shell);
}

void signals_handler(void)
{
	struct sigaction sa_int;

	//SIGINT -> ctrl+c -> new line 
	memset(&sa_int, 0, sizeof(sa_int));
	sa_int.sa_handler = &sigint_handler;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
	{
		perror("sigaction SIGINT");
		exit(EXIT_FAILURE);
	}
	//SIGQUIT -> ctrl+\ -> ignore it
	signal(SIGQUIT, SIG_IGN);
}
