/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_variables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 02:30:54 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/06 02:35:59 by jveirman         ###   ########.fr       */
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