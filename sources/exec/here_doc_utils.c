/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:28:05 by jveirman          #+#    #+#             */
/*   Updated: 2024/10/28 22:59:20 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_here_doc_available(t_shell *shell, int i)
{
	if (!shell->cmd_array[i].here_doc_input)
		return (0);
	return (1);
}

// todo - clean - check for eof and ctrl+c
static char *ft_delimiter_hunter(char *ret, char *to_find)
{
	char	*buf;
	char	*temp;

	while (1)
	{
		buf = readline("> ");
		if (!buf)
			return (free(ret), NULL);
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
