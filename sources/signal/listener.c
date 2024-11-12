/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listener.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:29:01 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/12 15:44:44 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define _GNU_SOURCE
#include "../../includes/minishell.h"

void	signal_ctlc_on_fork(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_status = 130;
		write(STDERR_FILENO, "\n", 1);
	}
}
void	signal_ctlc_on_subprocess(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_status = SUBPROCESS_SIG;
		write(STDERR_FILENO, "\n", 1);
		close(STDIN_FILENO);
	}
}

void	sigint_handler(int signal)
{
	if (signal == SIGINT)
	{
		g_exit_status = 1;
		write(STDERR_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sigeof_handler(t_shell *shell)
{
	clean("exit\n", shell, true);
	system("leaks minishell");
	exit(g_exit_status);
}

void signals_handler(void)
{
	struct sigaction sa_int;

	ft_memset(&sa_int, 0, sizeof(sa_int));
	sa_int.sa_handler = &sigint_handler;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
	{
		error_msg("sigaction SIGINT");
		exit(EXIT_FAILURE);
	}
	signal(SIGQUIT, SIG_IGN);
}
