/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:28:05 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/10 16:45:03 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_here_doc_available(t_shell *shell, int i)
{
	if (shell->cmd_array[i].fd_in != USE_HEREDOC)
		return (0);
	return (1);
}

// todo thouroughly check this function for the g_exit_status condition
// todo same for the other function
static char *ft_delimiter_hunter(char *ret, char *to_find, t_shell *shell)
{
	char	*buf;
	char	*temp;
	int  stdin_backup;

	stdin_backup = dup(STDIN_FILENO);
	if (stdin_backup == -1)
		panic("dup failed", shell);
	signal(SIGINT, signal_ctlc_on_subprocess);
	while (1)
	{
		buf = readline("> ");
		if (!buf || g_exit_status == 130)
		{
			free(ret);
			if (dup2(stdin_backup, STDIN_FILENO) == -1)
				panic("dup2 failed", shell);
			if (close(stdin_backup) == -1)
				panic("close failed", shell);
			return (NULL);
		}
		if (ft_strcmp(buf, to_find) == 0)
		{
			free(buf);
			break;
		}
		temp = ret;
		ret = ft_strjoin(ret, buf);
		free(temp);
		if (!ret)
		{
			free(buf);
			panic(ERR_MALLOC, shell);
		}
		temp = ret;
		ret = ft_strjoin(ret, "\n");
		free(temp);
		free(buf);
		if (!ret)
			panic(ERR_MALLOC, shell);
	}
	if (dup2(stdin_backup, STDIN_FILENO) == -1)
		panic("dup2 failed", shell);
	if (close(stdin_backup) == -1)
		panic("close failed", shell);
	return (ret);
}

char	*to_the_delimiter(char *to_find, t_shell *shell)
{
	char	*text_stored;

	text_stored = NULL;
	if (!to_find || !to_find[0])
		return (NULL);
	text_stored = ft_delimiter_hunter(text_stored, to_find, shell);
	if (g_exit_status == 130)
		return (NULL);
	else if (!text_stored)
	{
		text_stored = ft_strdup("");
		if (!text_stored)
			panic(ERR_MALLOC, shell);
	}
	
	return (text_stored);
}
