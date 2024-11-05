/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:06:09 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/05 17:42:56 by jveirman         ###   ########.fr       */
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

void	handle_pipe(int *i, t_token **tokens_list)
{
	t_token *new_token;
	char *content;
	
	content = NULL;
	content = ft_strdup("|");
	if (!content)
	{
		free_tokens_list(tokens_list);
		return ;
	}
	new_token = create_token(TOKEN_PIPE, &content);
	if (!add_token(tokens_list, new_token))
	{
		free_tokens_list(tokens_list);
		return ;
	}
	*i += 1;
}

const char	*get_token_type_name(t_token_type type)
{
	const char	*token_type_names[10];
	
	token_type_names[0] = "WORD";
	token_type_names[1] = "PIPE";
	token_type_names[2] = "REDIRECT_IN";
	token_type_names[3] = "REDIRECT_OUT";
	token_type_names[4] = "REDIRECT_APPEND";
	token_type_names[5] = "REDIRECT_HEREDOC";
	token_type_names[6] = "DOUBLE_QUOTE";
	token_type_names[7] = "SINGLE_QUOTE";
	token_type_names[8] = "SPACE";
	token_type_names[9] = "SKIP";
	if (type >= 0 && type < 10)
		return (token_type_names[type]);
	return ("UNKNOWN");
}

void	display_tokens(t_token *tokens)
{
 	t_token	*token;

 	token = tokens;
 	printf("\n---------------------------------------------------------------------\n");
 	while (token)
 	{
 		printf("Token: %s\t\t|\t\tType: %s %s"N" (%d)", token->content, token->type ? GREEN : "", get_token_type_name(token->type), token->type);
 		printf("\n---------------------------------------------------------------------\n");
 		token = token->next;
 	}
}
