/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 09:45:17 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/09 20:45:39 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_echo(t_shell *shell, char **data)
{
	bool	flag;

	flag = false;
	if (data[CMD_FLAG] && data[CMD_FLAG][0] == '-' && data[CMD_FLAG][1] == 'n' && data[CMD_FLAG][2] == '\0')
		flag = true;
	if (!check_data_validity(data, BUILTIN_ECHO) && (!flag && data[CMD_FLAG] != NULL))
	{
		ft_putstr_fd("minishell: echo: no options (but -n) allowed\n", STDERR_FILENO);
		return (2);
	}
	if (!data[CMD_ARG])
	{
		if (!flag)
			write(shell->current_fd_out, "\n", 1);
		return (0);
	}
	ft_putstr_fd(data[CMD_ARG], shell->current_fd_out);
	if (!flag)
		write(shell->current_fd_out, "\n", 1);
	return (0);
}
