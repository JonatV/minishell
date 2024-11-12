/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:40:08 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/12 15:52:04 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clean(char *str, t_shell *shell, bool free_env)
{
	if (str)
		ft_putstr_fd(str, shell->current_fd_out);
	free_cmd_array_struct(shell);
	free_tokens_list(&shell->tokens_list);
	free_shell_struct(shell, free_env);
}

void	panic(char *str, t_shell *shell)
{
	if (str)
		error_msg(str);
	clean(NULL, shell, true);
	g_exit_status = 1;
	system("leaks minishell");
	exit(g_exit_status);
}

