/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 09:45:17 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/15 13:13:26 by jveirman         ###   ########.fr       */
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

static void	print_flags(t_shell *shell, char *flag, char *arg)
{
	int	i;

	i = 0;
	while (flag && flag[i])
	{
		if (flag[i] && flag[i] == '-' && flag[i + 1] && flag[i + 1] == 'n')
		{
			if (!flag[i + 2])
				break ;
			if (ft_isspace(flag[i + 2]))
			{
				i += 3;
				continue ;
			}
		}
		while (flag[i])
		{
			ft_putchar_fd(flag[i], shell->current_fd_out);
			i++;
			if (ft_isspace(flag[i - 1]))
				break ;
		}
	}
	if (arg && flag)
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
