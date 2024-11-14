/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 09:45:17 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/14 22:24:37 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	check_echo_flags(char **data, bool *flag)
{
	int	i;
	int	j;

	if (!data[CMD_FLAG])
		return (true);
	i = 0;
	while (data[CMD_FLAG][i])
	{
		j = 0;
		while (data[CMD_FLAG][i + j] && !ft_isspace(data[CMD_FLAG][i + j]))
			j++;
		if (j == 2 && data[CMD_FLAG][(i + j) - 1] != 'n')
			return (false);
		else if (j == 2 && data[CMD_FLAG][(i + j) - 1] == 'n')
			*flag = true;
		if (!data[CMD_FLAG][i + j])
			break ;
		if (j == 0)
			i++;
		else
			i += j;
	}
	return (true);
}

static void	print_flags(t_shell *shell, char *data_flag, char *data_arg)
{
	int	i;

	i = 0;
	while (data_flag && data_flag[i])
	{
		if (data_flag[i] && data_flag[i] == '-' && data_flag[i + 1] && data_flag[i + 1] == 'n')
		{
			if (!data_flag[i + 2])
				break ;
			if (ft_isspace(data_flag[i + 2]))
			{
				i += 3;
				continue ;
			}
		}
		while (data_flag[i])
		{
			ft_putchar_fd(data_flag[i], shell->current_fd_out);
			i++;
			if (ft_isspace(data_flag[i - 1]))
				break ;
		}
	}
	if (data_arg && data_flag)
		ft_putchar_fd(' ', shell->current_fd_out);
}

int	builtin_echo(t_shell *shell, char **data)
{
	bool	flag;

	if (!check_echo_flags(data, &flag))
	{
		ft_putendl_fd(ERR_ECHO, STDERR_FILENO);
		return (2);
	}
	print_flags(shell, data[CMD_FLAG], data[CMD_ARG]);
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
