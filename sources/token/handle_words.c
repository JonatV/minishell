/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_words.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:09:42 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/05 00:31:31 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*extract_quoted(char *buf, int *i, char quote, int *type)
{
	int	start;
	int	end;

	*i += 1;
	start = *i;
	while (buf[*i] && buf[*i] != quote)
		*i += 1;
	end = *i;
	*i += 1;
	if (quote == 39)
		*type = TOKEN_SINGLE_QUOTE;
	else
		*type = TOKEN_DOUBLE_QUOTE;
	return (ft_substr(buf, start, end - start));
}

static char	*extract_word(char *buf, int *i, int *type)
{
	int	start;

	start = *i;
	while (buf[*i] && !ft_isspace(buf[*i]) && buf[*i] != '>' && buf[*i] != '<' && buf[*i] != '|' && buf[*i] != '"' && buf[*i] != 39)
		*i += 1;
	*type = TOKEN_WORD;
	return (ft_substr(buf, start, *i - start));
}

void	handle_word(char *buf, int *i, t_token **tokens_list)
{
	char		*tmp;
	int		type;
	t_token		*pending_token;

	if (buf[*i] == '"' || buf[*i] == 39)
		tmp = extract_quoted(buf, i, buf[*i], &type);
	else
		tmp = extract_word(buf, i, &type);
	if (!tmp)
	{
		free_tokens_list(tokens_list);
		return ;
	}
	pending_token = create_token(type, &tmp);
	if (!pending_token || !add_token(tokens_list, pending_token))
	{
		free_tokens_list(tokens_list);
		return ;
	}
	return ;
}
