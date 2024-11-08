/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:06:09 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/08 13:47:09 by jveirman         ###   ########.fr       */
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

const char	*get_token_type_name(t_token_type type)
{
	const char	*token_type_names[11];
	
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
	token_type_names[10] = "DOUBLE_PIPE";
	if (type >= 0 && type < 11)
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
