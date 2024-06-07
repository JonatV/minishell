/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:32:10 by mcygan            #+#    #+#             */
/*   Updated: 2024/06/07 10:48:24 by mcygan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

static size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize > 0)
	{
		while (src[i] != 0 && i < (dstsize - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	while (src[i])
		i++;
	return (i);
}

static int is_space(const char c)
{
	return ((c > 8 && c < 14) || c == 32);
}

static int	is_quote(const char c)
{
	return (c == 39 || c == 34);
}

// TODO: BUGS WITH ADJACENT QUOTES
// Count tokens in command line
// input = command line
static int	token_count(char *input)
{
	int		count;
	int		i;
	char	first_quote;

	count = -1;
	i = 0;

	while (count++, input[i])
	{
		while (is_space(input[i]))
			i++;
		while (input[i] && !is_space(input[i]))
		{
			if (is_quote(input[i]))
			{
				first_quote = input[i++];
				while (input[i] && input[i] != first_quote)
					i++;
				if (!input[i])
					return (-1);
			}
			if (is_quote(input[i]) && i > 0 && is_space(input[i - 1]))
				break ;
			if (is_quote(input[i + 1]) && input[i + 2] && is_space(input[i + 2]))
				break ;
			while (input[i] && !is_space(input[i]))
				i++;
		}
		while (is_space(input[i]))
			i++;
	}
	return (count);
}

// TODO: QUOTE_OFFSET IS A VERY NAIVE IMPLEMENTATION
// Get data from next token
// str = command line; idx = index from which to search for next token data
static char	*get_token_data(char *str, int *idx)
{
	char	*data;
	char	a;
	int		start;
	int		quote_offset;

	while (is_space(str[*idx]))
		(*idx)++;
	start = *idx;
	quote_offset = 0;
	if (is_quote(str[*idx]))
	{
		start++;
		a = str[*idx];
		while (str[*idx + 1] && str[*idx + 1] != a)
			(*idx)++;
	}
	while (str[*idx] && !is_space(str[*idx]))
	{
		if (str[(*idx)++] == a)
			quote_offset++;
	}
	data = malloc(sizeof(char) * (*idx - start - quote_offset + 1));
	if (!data)
		return (NULL);
	ft_strlcpy(data, str + start, *idx - start - quote_offset + 1);
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
	{
		array[i].type = VOID;
		array[i].data = get_token_data(input, &idx);
	}
	array[i].type = END;
	return (array);
}

/* int	main(int argc, char **argv)
{
	t_token	*token_array;
	int		i;

	if (argc != 2)
		return (1);
	printf("%d\n", token_count(argv[1]));
	token_array = tokens_init(argv[1]);
	i = -1;
	while (token_array[++i].type != END)
		printf("%s\n", token_array[i].data);
	return (0);
} */