/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listener.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:29:01 by jveirman          #+#    #+#             */
/*   Updated: 2024/05/28 17:07:21 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/signal.h"

void	signal_eof(t_shell *shell)
{
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	// write(1, "exit", 4);
	clean("exit", shell);
}

void	signal_interrupted(int sig)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void) sig;
}

void	signals(void)
{
	signal(SIGINT, signal_interrupted);
	signal(SIGQUIT, SIG_IGN);
}
