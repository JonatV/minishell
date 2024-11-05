/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:28:05 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/05 14:51:17 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_here_doc_available(t_shell *shell, int i)
{
	if (!shell->cmd_array[i].here_doc_input)
		return (0);
	return (1);
}

static void	signal_ctlc_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_status = 130;
		close(STDIN_FILENO);
		write(STDERR_FILENO, "\n", 1);
	}
}

// todo - clean - check for eof and ctrl+c
// static char	*ft_delimiter_hunter(char *ret, char *to_find)
// {
// 	char	*buf;
// 	char	*temp;
	
// 	signal(SIGINT, signal_ctlc_heredoc);
// 	while (1)
// 	{
// 		buf = readline("> ");
// 		if (!buf)
// 			return (free(ret), NULL);
// 		if (ft_strcmp(buf, to_find) == 0)
// 		{
// 			free(buf);
// 			break ;
// 		}
// 		temp = ret;
// 		ret = ft_strjoin(ret, buf);
// 		free(temp);
// 		temp = ret;
// 		ret = ft_strjoin(ret, "\n");
// 		free(temp);
// 		free(buf);
// 	}
// 	return (ret);
// }

static char *ft_delimiter_hunter(char *ret, char *to_find)
{
    char    *buf;
    char    *temp;
    int     stdin_backup;
    
    stdin_backup = dup(STDIN_FILENO);
    if (stdin_backup == -1)
        return (NULL);
        
    signal(SIGINT, signal_ctlc_heredoc);
    while (1)
    {
        buf = readline("> ");
        if (!buf || g_exit_status == 130)
        {
            free(ret);
            dup2(stdin_backup, STDIN_FILENO);
            close(stdin_backup);
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
		temp = ret;
		ret = ft_strjoin(ret, "\n");
		free(temp);
		free(buf);
    }
    dup2(stdin_backup, STDIN_FILENO);
    close(stdin_backup);
    return (ret);
}

char	*to_the_delimiter(char *to_find)
{
	char	*text_stored;

	text_stored = NULL;
	if (!to_find || !to_find[0])
		return (NULL);
	text_stored = ft_delimiter_hunter(text_stored, to_find);
	if (!text_stored)
		text_stored = ft_strdup("");
	return (text_stored);
}
