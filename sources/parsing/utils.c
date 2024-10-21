/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:23:05 by haroldsorel       #+#    #+#             */
/*   Updated: 2024/10/21 17:34:23 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

static void	input_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		set_sig_code(1);
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
	}
}

void	input_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, input_signal_handler);
}

static int	sig_code_static(int err_code, bool set_err_code)
{
	static int	static_err_code = 0;

	if (set_err_code)
		static_err_code = err_code;
	return (static_err_code);
}

void	set_sig_code(int err_code)
{
	sig_code_static(err_code, true);
}

int	get_sig_code(void)
{
	return (sig_code_static(0, false));
}

void	init_struct(t_cmd1 *cmd)
{
	cmd->fd_i = DEFAULT_FD;
	cmd->fd_o = DEFAULT_FD;
	cmd->type = -1;
/*
-	cmd->f_redir = 0;
*/
}

int	count_cmd(t_lists *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		if (lst->token->type == pipeline)
			i++;
		lst = lst->next;
	}
	return (i + 1);
}

int	get_type(char **str)
{
	if (ft_strlen(str[0]) == 4 && !ft_strncmp(str[0], "echo", 4))
		return (1);
	else if (ft_strlen(str[0]) == 2 && !ft_strncmp(str[0], "cd", 2))
		return (2);
	else if (ft_strlen(str[0]) == 3 && !ft_strncmp(str[0], "pwd", 3))
		return (3);
	else if (ft_strlen(str[0]) == 6 && !ft_strncmp(str[0], "export", 6))
		return (4);
	else if (ft_strlen(str[0]) == 5 && !ft_strncmp(str[0], "unset", 5))
		return (5);
	else if (ft_strlen(str[0]) == 3 && !ft_strncmp(str[0], "env", 3))
		return (6);
	else if (ft_strlen(str[0]) == 4 && !ft_strncmp(str[0], "exit", 4))
		return (7);
	else
		return (0);
}

int	print_syntax_error(char *str, int i)
{
	if (ft_strncmp(str, "\n", 1) == 0)
		printf("minishell: syntax error near unexpected token `newline'\n");
	else
		printf("minishell: syntax error near unexpected token `%c'\n", str[i]);
	return (0);
}

void	ft_free(char *str)
{
	free(str);
	str = NULL;
}
