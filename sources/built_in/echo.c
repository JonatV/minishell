/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 09:45:17 by jveirman          #+#    #+#             */
/*   Updated: 2024/10/30 17:43:51 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_echo(t_shell *shell, char **data)
{
	bool	flag;

	if (!data[CMD_ARG][0])
	{
		write(shell->current_fd_out, "\n", 1);
		return ;
	}
	flag = false;
	if (data[CMD_FLAG] && data[CMD_FLAG][0] == '-' && data[CMD_FLAG][1] == 'n')
		flag = true;
	ft_putstr_fd(data[CMD_ARG], shell->current_fd_out);
	if (!flag)
		write(shell->current_fd_out, "\n", 1);
}
