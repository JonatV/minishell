/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 10:55:16 by mcygan            #+#    #+#             */
/*   Updated: 2024/06/11 17:41:23 by mcygan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

// Count tokens in command line
// input = command line
int	token_count(char *input)
{
	int		count;
	int		i;

	count = -1;
	i = 0;
	while (count++, input[i])
	{
		skip_whitespace(input, &i);
		while (input[i] && !is_whitespace(input[i]))
		{
			if (skip_quote(input, &i) < 0)
					return (-1);
			if (is_quote(input[i]) && i > 0 && is_whitespace(input[i - 1]))
				break ;
			if (is_quote(input[i + 1]) && input[i + 2] && is_whitespace(input[i + 2]))
				break ;
			if (input[i] == '>' || input[i] == '<')
			{
				i++;
				if (input[i] == '>' || input[i] == '<')
				 	i++;
				skip_whitespace(input, &i);
			}
			while (input[i] && !is_whitespace(input[i]))
				i++;
		}
		skip_whitespace(input, &i);
	}
	return (count);
}

// Get data from next token
// str = command line; idx = index from which to search for next token data
char	*get_token_data(char *str, int *idx)
{
	char	*data;
	int		start;

	skip_whitespace(str, idx);
	start = *idx;
	skip_quote(str, idx);
	if ((is_quote(str[*idx]) && *idx > 0 && is_whitespace(str[*idx - 1])) || \
		(is_quote(str[*idx + 1]) && str[*idx + 2] && is_whitespace(str[*idx + 2])))
		goto jump;
	if (str[*idx] == '<' || str[*idx] == '>')
	{
		(*idx)++;
		if (str[*idx] == '<'|| str[*idx] == '>')
			(*idx)++;
		skip_whitespace(str, idx);
	}
	if (*idx > 0 && is_quote(str[*idx - 1]) && str[*idx])
		(*idx)--;
	while (str[*idx] && !is_whitespace(str[*idx]))
		(*idx)++;
	jump:
	data = malloc(sizeof(char) * (*idx - start + 1));
	if (!data)
		return (NULL);
	ft_strlcpy(data, str + start, *idx - start + 1);
	return (data);
}

// Initialize token array and respective data values
// input = command line
t_token	*tokens_init(char *input)
{
	t_token	*array;
	int		count;
	int		idx;
	int		i;

	count = token_count(input);
	array = malloc(sizeof(t_token) * (count + 1));
	if (!array)
		return (NULL);
	idx = 0;
	i = -1;
	while (++i < count)
		array[i].data = get_token_data(input, &idx);
	array[i].type = END;
	return (array);
}

void	set_token_type(t_token *tokens, int idx)
{
	if (!ft_strncmp(tokens[idx].data, "|", 0))
		tokens[idx].type = PIPE;
	else if (!ft_strncmp(tokens[idx].data, ">", 0) \
			|| !ft_strncmp(tokens[idx].data, "<", 0))
		tokens[idx].type = STREAM;
	else
		tokens[idx].type = CMD;
}

/* int	main(int argc, char **argv)
{
	t_token	*token_array;
	int		cmd_set;
	int		tc;
	int		i;

	if (argc != 2)
		return (1);
	tc = token_count(argv[1]);
	printf("%d\n", tc);
	token_array = tokens_init(argv[1]);
	cmd_set = 0;
	i = -1;
	while (token_array[++i].type != END)
		set_token_type(token_array, i);
	i = -1;
	while (token_array[++i].type != END)
		printf("type: %d \tdata: %s%%\n", token_array[i].type, token_array[i].data);
	return (0);
} */

//BUGS:
//hello'there ' returns -1
//hello' there' improper quote distribution
