/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:28:05 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/14 12:20:27 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_here_doc_available(t_shell *shell, int i)
{
	if (shell->cmd_array[i].fd_in != USE_HEREDOC)
		return (0);
	return (1);
}

static char *free_n_restore(char *buf, char *ret, int stdin_backup, t_shell *shell)
{
	if (buf)
		free(buf);
	if (ret)
		free(ret);
	restore_stdin(stdin_backup, shell, false);
	return (NULL);
}

static void	join_to_buffer(t_shell *shell, char *buf, char **ret)
{
	char	*temp;

	temp = *ret;
	*ret = ft_strjoin(*ret, buf);
	free(temp);
	if (!*ret)
	{
		free(buf);
		panic(ERR_MALLOC, shell);
	}
	temp = *ret;
	*ret = ft_strjoin(*ret, "\n");
	free(temp);
	free(buf);
	if (!*ret)
		panic(ERR_MALLOC, shell);
}

static char	*ft_delimiter_hunter(char *ret, char *to_find, t_shell *shell)
{
	char	*buf;
	int		stdin_backup;

	stdin_backup = dup(STDIN_FILENO);
	if (stdin_backup == -1)
		panic("dup failed", shell);
	signal(SIGINT, signal_ctlc_on_subprocess);
	while (1)
	{
		buf = readline("> ");
		if (!buf || g_exit_status == SUBPROCESS_SIG)
			return (free_n_restore(buf, ret, stdin_backup, shell));
		if (ft_strcmp(buf, to_find) == 0)
		{
			free(buf);
			break ;
		}
		join_to_buffer(shell, buf, &ret);
	}
	restore_stdin(stdin_backup, shell, false);
	return (ret);
}

char	*to_the_delimiter(char *to_find, t_shell *shell)
{
	char	*text_stored;

	text_stored = NULL;
	if (!to_find || !to_find[0])
		return (NULL);
	text_stored = ft_delimiter_hunter(text_stored, to_find, shell);
	if (g_exit_status == SUBPROCESS_SIG)
	{
		if (text_stored)
			free(text_stored);
		return (NULL);
	}
	else if (!text_stored)
	{
		text_stored = ft_strdup("");
		if (!text_stored)
			panic(ERR_MALLOC, shell);
	}
	return (text_stored);
}
