/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd_line_structure.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:44:12 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/12 18:48:47 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	join_to_buffer(t_shell *shell, char *additional_buffer)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_strjoin(shell->buf, " ");
	if (!tmp)
		panic(ERR_MALLOC, shell);
	free(shell->buf);
	shell->buf = tmp;
	tmp = ft_strjoin(shell->buf, additional_buffer);
	free(shell->buf);
	shell->buf = tmp;
	free(additional_buffer);
	if (!shell->buf)
		panic(ERR_MALLOC, shell);
}

static bool	check_additional_buffer(t_shell *shell, \
	char **additional_buffer, int stdin_backup)
{
	if (!*additional_buffer || g_exit_status == SUBPROCESS_SIG)
	{
		restore_stdin(stdin_backup, shell);
		if (g_exit_status == SUBPROCESS_SIG)
		{
			free(additional_buffer);
			g_exit_status = 1;
		}
		else
			ft_putendl_fd(ERR_EOF, shell->current_fd_out);
		free(shell->buf);
		shell->buf = NULL;
		return (false);
	}
	return (true);
}

static bool	get_additionnal_cmd_line(t_shell *shell)
{
	char	*additional_buffer;
	int		stdin_backup;

	additional_buffer = NULL;
	stdin_backup = dup(STDIN_FILENO);
	if (stdin_backup == -1)
		panic("dup failed", shell);
	signal(SIGINT, signal_ctlc_on_subprocess);
	while (1)
	{
		additional_buffer = readline("> ");
		if (!check_additional_buffer(shell, &additional_buffer, stdin_backup))
			return (false);
		join_to_buffer(shell, additional_buffer);
		if (!is_incomplete_cmd_line(shell->buf))
			break ;
	}
	return (restore_stdin(stdin_backup, shell));
}

bool	check_cmd_line_structure(t_shell *shell)
{
	char	*buffer;

	buffer = readline(shell->prompt_msg);
	if (!buffer)
		sigeof_handler(shell);
	else if (buffer[0] == '\0' || only_isspace_string(buffer))
	{
		free(buffer);
		g_exit_status = 0;
		return (false);
	}
	shell->buf = ft_strdup(buffer);
	free(buffer);
	if (!shell->buf)
		panic(ERR_MALLOC, shell);
	if (is_incomplete_cmd_line(shell->buf))
		return (get_additionnal_cmd_line(shell));
	add_history(shell->buf);
	return (true);
}
