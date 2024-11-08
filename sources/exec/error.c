/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:01:49 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/08 12:36:52 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fd_error(t_shell *shell, int i)
{
	if (shell->cmd_array[i].fd_in == -1)
	{
		mini_printf("minishell: ", shell->cmd_array[i].file_name_in, ": No such file or directory\n", STDERR_FILENO);
		clean(NULL, shell, false);
		exit(1);
	}
	if (shell->cmd_array[i].fd_out == -1)
	{
		mini_printf("minishell: ", shell->cmd_array[i].file_name_out, ": No such file or directory\n", STDERR_FILENO);
		clean(NULL, shell, false);
		exit(1);
	}
}
