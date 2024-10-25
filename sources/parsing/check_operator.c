/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:09:16 by haroldsorel       #+#    #+#             */
/*   Updated: 2024/10/25 13:35:55 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

int	close_op(char **input, char *content, char *line, int i)
{
	char	*tmp;

	if (i == 1)
	{
		tmp = ft_strdup(*input);
		free(*input);
		*input = NULL;
		*input = ft_strjoin(tmp, content);
		if (!*input)
			return (0);
		free(tmp);
	}
	free(content);
	free(line);
	if (i == 0)
		return (0);
	return (1);
}

int	check_closed_op(char *line)
{
	int	i;
	int	val;

	i = 0;
	val = 0;
	while (line[i])
	{
		if (line[i] >= 33 && line[i] <= 126)
			val = 1;
		i++;
	}
	return (val);
}

int	unclosed_operator(char **input)
{
	char	*content;
	char	*tmp;
	char	*line;

	input_signals();
	set_sig_code(0);
	content = ft_strdup("\n");
	ft_putstr("pipe>");
	line = get_next_line(0);
	while (line)
	{
		if (get_sig_code())
			return (close_op(input, content, line, 0));
		tmp = ft_strdup(content);
		ft_free(content);
		content = ft_strjoin(tmp, line);
		ft_free(tmp);
		if (check_closed_op(line))
			return (close_op(input, content, line, 1));
		ft_putstr("pipe>");
		ft_free(line);
		line = get_next_line(0);
	}
	return (close_op(input, content, line, 1));
}
