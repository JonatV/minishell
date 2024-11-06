/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 10:47:29 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/06 03:02:45 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	is_non_numeric(t_shell *shell, char *str)
{
	int i = 0;
	if (!str)
		return (false);
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != ' ')
		{
			mini_printf("Minishell: exit: ", str, ": numeric argument required\n", shell->current_fd_out);
			return (true);
		}
		i++;
	}
	return (false);
}

static bool	non_numeric_found(t_shell *shell, int i)
{
	return (is_non_numeric(shell, shell->cmd_array[i].data[CMD_FLAG]) \
			|| is_non_numeric(shell, shell->cmd_array[i].data[CMD_ARG]));
}

//todo clean function for the all minishell
void	builtin_exit(t_shell *shell, int i)
{
	int	size;

	size = shell->cmd_array[i].num_flag + shell->cmd_array[i].num_arg;
	ft_putstr_fd("exit\n", shell->current_fd_out);
	if (size > 1)
	{
		ft_putstr_fd("Minishell: exit: too many arguments\n", STDERR_FILENO);
		return ;
	}
	non_numeric_found(shell, i);
	exit(shell->exit_code);
}
