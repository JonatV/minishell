/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_variables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 02:30:54 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/12 18:37:40 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	replace_double_dollar(char **str, int *i)
{
	char	*segments[3];

	segments[0] = ft_substr(*str, 0, *i);
	segments[1] = ft_itoa(getpid());
	segments[2] = ft_substr(*str, *i + 2, ft_strlen(*str));
	if (!segments[0] || !segments[1] || !segments[2])
		return (free_all_segments(segments));
	*i = ft_strlen(segments[0]) + ft_strlen(segments[1]);
	return (assemble_all_segments(segments, str));
}

bool	replace_dollar_question_mark(char **str, int *i)
{
	char	*segments[3];

	segments[0] = ft_substr(*str, 0, *i);
	segments[1] = ft_itoa(g_exit_status);
	segments[2] = ft_substr(*str, *i + 2, ft_strlen(*str));
	if (!segments[0] || !segments[1] || !segments[2])
		return (free_all_segments(segments));
	*i = ft_strlen(segments[0]) + ft_strlen(segments[1]);
	return (assemble_all_segments(segments, str));
}

bool	block_special_variables(char *str, int i)
{
	char	char_found[2];

	char_found[0] = str[i + 1];
	char_found[1] = '\0';
	if (str[i + 1] && ft_strrchr("_@0#*!-", str[i + 1]))
	{
		mini_printf("minishell: $", char_found, ERR_SPCLVAR, STDERR_FILENO);
		return (false);
	}
	return (true);
}
