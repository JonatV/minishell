/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:40:08 by jveirman          #+#    #+#             */
/*   Updated: 2024/10/30 17:41:38 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	free_machine(t_shell *shell)
{
	if (shell->pipefds != NULL)
		free(shell->pipefds);
	if (shell->prompt_msg != NULL)
		free(shell->prompt_msg);
	if (shell->env != NULL)
		ft_arrayfree(shell->env);
	if (shell->cmd_array)
		free(shell->cmd_array);
}

void	clean(char *str, t_shell *shell)
{
	if (str)
		ft_putstr_fd(str, shell->current_fd_out);
	free_machine(shell);
}

void	panic(char *str, t_shell *shell)
{
	ft_putstr_fd(MSG_ERROR, STDERR_FILENO);
	if (str)
	{
		ft_putstr_fd(" : ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
	}
	ft_putstr_fd("\n", STDERR_FILENO);
	if (shell != NULL)
		free_machine(shell);
	exit(EXIT_FAILURE);
}
