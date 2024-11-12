/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:06:09 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/12 01:57:53 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tokens_list(t_token **tokens)
{
	t_token *current;
	t_token *next;

	current = *tokens;
	while (current)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
	*tokens = NULL;
}

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

void	handle_word(t_shell *shell, int *i, t_token **tokens_list)
{
	char		*tmp;
	int		type;
	t_token		*pending_token;

	if (shell->buf[*i] == '"' || shell->buf[*i] == 39)
		tmp = extract_quoted(shell->buf, i, shell->buf[*i], &type);
	else
		tmp = extract_word(shell->buf, i, &type);
	if (!tmp)
		panic(ERR_MALLOC, shell);
	pending_token = create_token(type, &tmp);
	if (!add_token(tokens_list, pending_token))
		panic(ERR_MALLOC, shell);
}
