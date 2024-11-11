/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 09:45:17 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/11 22:30:36 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	check_echo_flags(char **data, bool *flag)
{
	int i;
	int j;

	if (!data[CMD_FLAG])
		return (true);
	i = 0;
	while (data[CMD_FLAG][i])
	{
		j = 0;
		while (data[CMD_FLAG][i + j] && !ft_isspace(data[CMD_FLAG][i + j]))
			j++;
		// printf("check letter -[%c]\n", data[CMD_FLAG][(i + j) - 1]);
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

static void print_flags(t_shell *shell, char *str)
{
	int		i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] && str[i] == '-' && str[i + 1] && str[i + 1] == 'n')
		{
			if (!str[i + 2])
				break;
			if (ft_isspace(str[i + 2]))
			{
				i += 3;
				continue;
			}
		}
		while (str[i])
		{
			ft_putchar_fd(str[i], shell->current_fd_out);
			i++;
			if (ft_isspace(str[i - 1]))
				break ;
		}
	}
}

int	builtin_echo(t_shell *shell, char **data)
{
	bool	flag;

	if (!check_echo_flags(data, &flag))
	{
		ft_putstr_fd("minishell: echo: no options (but -n) allowed\n", STDERR_FILENO);
		return (2);
	}
	print_flags(shell, data[CMD_FLAG]);
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
