/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listener.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:29:01 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/05 16:12:51 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define _GNU_SOURCE
#include "../../includes/minishell.h"

void	signal_ctlc_on_subprocess(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_status = 130;
		close(STDIN_FILENO);
		write(STDERR_FILENO, "\n", 1);
	}
}

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
	clean("exit\n", shell);
	exit(shell->exit_code);
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
