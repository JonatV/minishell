/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 13:56:41 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/12 02:04:55 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	start_with_pipe(t_shell *shell)
{
	int i;

	i = 0;
	while (shell->buf[i] && ft_isspace(shell->buf[i]))
		i++;
	if (shell->buf[i] == '|')
		return (false);
	return (true);
}

bool	add_token(t_token **tokens_list, t_token *new_token)
{
	t_token	*current;

	if (!new_token)
		return (false);
	if (!*tokens_list)
	{
		*tokens_list = new_token;
		return (true);
	}
	current = *tokens_list;
	while (current->next) 
		current = current->next;
	current->next = new_token;
	return (true);
}

t_token	*create_token(t_token_type type, char **content)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
	{
		free(*content);
		return (NULL);
	}
	new_token->type = type;
	new_token->content = *content;
	new_token->next = NULL;
	return (new_token);
}

bool	tokenizer(t_shell *shell)
{
	int	i;

	if (!start_with_pipe(shell))
	{
		clean(NULL, shell, false);
		return (error_msg("syntax error near unexpected token `|'"));
	}
	i = 0;
	while (shell->buf[i])
	{
		if (ft_isspace(shell->buf[i]))
			handle_space(shell, &i, &shell->tokens_list);
		else if (shell->buf[i] == '>' || shell->buf[i] == '<')
			handle_redirections(shell, &i, &shell->tokens_list);
		else if (shell->buf[i] == '|')
		{
			if (!handle_pipe(shell, &i, &shell->tokens_list))
				return (false);
		}
		else
			handle_word(shell, &i, &shell->tokens_list);
	}
	return (true);
}
