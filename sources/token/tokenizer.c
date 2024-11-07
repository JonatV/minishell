/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 13:56:41 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/07 00:56:48 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

	i = 0;
	while (shell->buf[i])
	{
		if (ft_isspace(shell->buf[i]))
			handle_space(shell->buf, &i, &shell->tokens_list);
		else if (shell->buf[i] == '>' || shell->buf[i] == '<')
			handle_redirections(shell->buf, &i, &shell->tokens_list);
		else if (shell->buf[i] == '|')
		{
			if (!handle_pipe(&i, &shell->tokens_list, shell->buf))
				return (false);
		}
		else
			handle_word(shell->buf, &i, &shell->tokens_list);
	}
	return (true);
}

// int	main(void)
// {
// 	t_shell shell;
	
// 	ft_memset(&shell, '\0', sizeof(t_shell));

// 	while (1)
// 	{
// 		shell.buf = readline("Tokenizer test $ ");
// 		if (!shell.buf)
// 			break ;
// 		if (!*shell.buf)
// 		{
// 			free(shell.buf);
// 			continue ;
// 		}
// 		tokenizer(&shell);
// 		if (!shell.tokens_list)
// 		{
// 			free(shell.buf);
// 			return (printf("Error with tokens list\n"), 1);
// 		}
// 		add_history(shell.buf);
// 		free(shell.buf);
// 		display_tokens(shell.tokens_list);
// 		free_tokens_list(&shell.tokens_list);
// 	}
// 	return (0);
// }

// int	main(void)
// {
// 	char *buf;
// 	t_token *tokens_list;

// 	tokens_list = NULL;
// 	while (1)
// 	{
// 		buf = readline("Tokenizer test $ ");
// 		if (!buf)
// 			break ;
// 		if (!*buf)
// 		{
// 			free(buf);
// 			continue ;
// 		}
// 		tokens_list = tokenizer(buf);
// 		if (!tokens_list)
// 		{
// 			free(buf);
// 			return (printf("Error with tokens list\n"), 1);
// 		}
// 		add_history(buf);
// 		free(buf);
// 		display_tokens(tokens_list);

// 		// printf("tokens_list: %s\n", tokens_list->content);
// 		free_tokens_list(tokens_list);
// 	}
// 	return (0);
// }
