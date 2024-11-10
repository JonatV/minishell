/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 10:47:29 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/09 20:15:18 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_non_numeric(t_shell *shell, char *str)
{
	int i = 0;
	if (!str)
		return (0);
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != ' ')
		{
			mini_printf("minishell: exit: ", str, ": numeric argument required\n", shell->current_fd_out);
			return (2);
		}
		i++;
	}
	return (0);
}

static int	non_numeric_found(t_shell *shell, int i)
{
	return (is_non_numeric(shell, shell->cmd_array[i].data[CMD_FLAG]) \
			|| is_non_numeric(shell, shell->cmd_array[i].data[CMD_ARG]));
}

int	builtin_exit(t_shell *shell, int i)
{
	int	size;
	int ret_value;
	
	ret_value = 0;
	size = shell->cmd_array[i].num_flag + shell->cmd_array[i].num_arg;
	ft_putstr_fd("exit\n", shell->current_fd_out);
	if (size > 1)
	{
		error_msg("exit: too many arguments");
		return (1);
	}
	ret_value = non_numeric_found(shell, i);
	if (ret_value)
		return (ret_value);
	if (shell->cmd_array[i].data[CMD_FLAG])
		ret_value = ft_atoi(shell->cmd_array[i].data[CMD_FLAG]);
	else
		ret_value = ft_atoi(shell->cmd_array[i].data[CMD_ARG]);
	ret_value = ret_value % 256;
	return (ret_value);
}
