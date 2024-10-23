/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 20:00:21 by hsorel            #+#    #+#             */
/*   Updated: 2024/10/23 15:42:11 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/token.h"
#include "../../includes/expander.h"
#include "../../includes/shell.h"

void	handle_variables(t_token **tokens, t_shell *shell)
{
	t_token *current;
	char	*word;

	current = *tokens;
	word = NULL;
	while (current)
	{
		if (current->type == TOKEN_ENV_VAR)
		{
			expander(shell->env, &(current->value));
			current->type = 0;
		}
		current = current->next;
	}
}

void	handle_special_chars(char **input, t_token **tokens)
{
	if (**input == '>')
	{
		if (*(*input + 1) == '>')
		{
			add_token_to_list(tokens, new_token(TOKEN_REDIR_APPEND, ">>"));
			(*input)++;
		}
		else
			add_token_to_list(tokens, new_token(TOKEN_REDIR_OUT, ">"));
	}
	else if (**input == '<')
	{
		if (*(*input + 1) == '<')
		{
			add_token_to_list(tokens, new_token(TOKEN_REDIR_HEREDOC, "<<"));
			(*input)++;
		}
		else
			add_token_to_list(tokens, new_token(TOKEN_REDIR_IN, "<"));
	}
	else if (**input == '|')
		add_token_to_list(tokens, new_token(TOKEN_PIPE, "|"));
	(*input)++;
}

void	handle_word(char **input, t_token **tokens)
{
	char	*start;
	int		in_quote;
	char	quote_char;

	start = *input;
	in_quote = 0;
	quote_char = '\0';
	while (**input)
	{
		update_quote_status(**input, &in_quote, &quote_char);
		if (!in_quote && ft_strchr(" \t\n><|", **input))
			break ;
		(*input)++;
	}
	add_word_token_if_valid(&start, input, tokens);
}

t_token	*tokenize_input(t_shell *shell)
{
	t_token	*tokens;
	char	*buf;
	
	tokens = NULL;
	buf = shell->buf;
	while (*buf)
	{
		while (*buf && ft_strchr(" \t\n", *buf))
			buf++;
		if (ft_strchr("><|", *buf))
			handle_special_chars(&buf, &tokens);
		else
			handle_word(&buf, &tokens);
	}
	handle_variables(&tokens, shell);
	return (tokens);
}
