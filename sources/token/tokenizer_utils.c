/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsorel <hsorel@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 20:00:33 by hsorel            #+#    #+#             */
/*   Updated: 2024/10/21 20:00:34 by hsorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/token.h"

char	*ft_strndup(const char *src, size_t n)
{
	size_t	i;
	size_t	size;
	char	*str;

	i = 0;
	size = ft_strnlen(src, n);
	str = malloc(size + 1);
	if (str == NULL)
		return (NULL);
	while (i < size)
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

size_t	ft_strnlen(const char *s, size_t maxlen)
{
	size_t	len;

	len = 0;
	while (len < maxlen && s[len])
		len++;
	return (len);
}

 const char	*get_token_type_name(t_token_type type)
 {
 	const char	*token_type_names[7];

 	token_type_names[0] = "WORD";
 	token_type_names[1] = "PIPE";
 	token_type_names[2] = "REDIRECT_IN";
 	token_type_names[3] = "REDIRECT_OUT";
 	token_type_names[4] = "REDIRECT_APPEND";
 	token_type_names[5] = "REDIRECT_HEREDOC";
 	token_type_names[6] = "TOKEN_ENV_VAR";
 	if (type >= 0 && type < 7)
 		return (token_type_names[type]);
 	return ("UNKNOWN");
 }

 void	display_tokens(t_token *tokens)
{
 	t_token	*token;

 	token = tokens;
 	while (token)
 	{
 		printf("Token: %s\t\t|\t\tType: %s", token->value, get_token_type_name(token->type));
 		printf("\n---------------------------------------------------------------------\n");
 		token = token->next;
 	}
}

t_token	*new_token(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = ft_strdup(value);
	if (!token->value)
	{
		free(token);
		return (NULL);
	}
	token->next = NULL;
	return (token);
}

void	add_token_to_list(t_token **tokens, t_token *new_token)
{
	t_token	*last;

	if (!*tokens)
		*tokens = new_token;
	else
	{
		last = *tokens;
		while (last->next)
			last = last->next;
		last->next = new_token;
	}
}

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		free(tmp->value);
		free(tmp);
	}
}

void	update_quote_status(char c, int *in_quote, char *quote_char)
{
	if (!*in_quote && (c == '\'' || c == '\"'))
	{
		*in_quote = 1;
		*quote_char = c;
	}
	else if (*in_quote && c == *quote_char)
		*in_quote = 0;
}

void	add_word_token_if_valid(char **start, char **input, t_token **tokens)
{
	char	*word;

	if (*input > *start)
	{
		word = ft_strndup(*start, *input - *start);
		if (word)
		{
			if (word[0] == '$' && word[1])
			{
				add_token_to_list(tokens, new_token(TOKEN_ENV_VAR, word));
				free(word);
				return ;
			}
			add_token_to_list(tokens, new_token(TOKEN_WORD, word));
			free(word);
		}
		else
			ft_putstr_fd("Error: Malloc failed in handle_word.\n", 2);
	}
}