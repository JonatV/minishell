/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd_line_structure.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:44:12 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/12 02:03:41 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool only_isspace_string(char *buffer)
{
	int	i;
	int	j;

	j = 0;
	i = ft_strlen(buffer);
	while (ft_isspace(buffer[j]))
		j++;
	if (j >= i)
		return (true);
	return (false);
}

static bool	is_quote_incomplete(char *buffer)
{
	int		i;
	bool	in_quote;
	int		quote_type;

	in_quote = false;
	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == 39 || buffer[i] == 34)
		{
			if (!in_quote)
			{
				in_quote = true;
				quote_type = buffer[i];
			}
			else if (quote_type == buffer[i])
				in_quote = false;
		}
		i++;
	}
	return (in_quote);
}

static bool	incomplete_cmd_line(char *buffer)
{
	int	i;
	
	if (is_quote_incomplete(buffer))
		return (true);
	i = ft_strlen(buffer) - 1;
	while (i >= 0 && ft_isspace(buffer[i]))
		i--;
	if (buffer[i] == '|')
		return (true);
	return (false);
}

static bool	get_additionnal_cmd_line(t_shell *shell)
{
	char	*tmp;
	char	*additional_buffer;
	int		stdin_backup;

	stdin_backup = dup(STDIN_FILENO);
	if (stdin_backup == -1)
		return (false);
	signal(SIGINT, signal_ctlc_on_subprocess);
	while (1)
	{
		additional_buffer = readline("> ");
		if (g_exit_status == 130)
		{
			free(additional_buffer);
			free(shell->buf);
			dup2(stdin_backup, STDIN_FILENO);
			close(stdin_backup);
			return (false);
		}
		if (!additional_buffer)
		{
			free(additional_buffer);
			dup2(stdin_backup, STDIN_FILENO);
			close(stdin_backup);
			ft_putstr_fd("minishell: unexpected EOF while looking for matching\n", shell->current_fd_out);
			sigeof_handler(shell);
		}
		tmp = ft_strjoin(shell->buf, additional_buffer);
		free(additional_buffer);
		if (!tmp)
			panic(ERR_MALLOC, shell);
		free(shell->buf);
		shell->buf = tmp;
		if (!incomplete_cmd_line(shell->buf))
			break ;
	}
	dup2(stdin_backup, STDIN_FILENO);
	close(stdin_backup);
	return (true);
}

bool	check_cmd_line_structure(t_shell *shell)
{
	char	*buffer;
	
	buffer = readline(shell->prompt_msg);
	if (!buffer)
	{
		free(buffer);
		sigeof_handler(shell);
	}
	else if (buffer[0] == '\0' || only_isspace_string(buffer))
	{
		free(buffer);
		g_exit_status = 0;
		return (false);
	}
	else if (incomplete_cmd_line(buffer))
	{
		shell->buf = ft_strdup(buffer);
		free(buffer);
		return (get_additionnal_cmd_line(shell));
	}
	shell->buf = buffer;
	return (true);
}
