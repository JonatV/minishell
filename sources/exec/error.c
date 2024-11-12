/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:01:49 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/12 16:40:48 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fd_error(t_shell *shell, int i)
{
	if (shell->cmd_array[i].fd_in == -1)
	{
		mini_printf(NAME, shell->cmd_array[i].file_name_in, ERR_FIDIR, STDERR_FILENO);
		clean(NULL, shell, false);
		exit(1);
	}
	if (shell->cmd_array[i].fd_out == -1)
	{
		mini_printf(NAME, shell->cmd_array[i].file_name_out, ERR_FIDIR, STDERR_FILENO);
		clean(NULL, shell, false);
		exit(1);
	}
}
