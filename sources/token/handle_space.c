/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_space.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 20:14:11 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/02 23:35:02 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_space(char *buf, int *i, t_token **tokens_list)
{
	char		*tmp;
	t_token		*pending_token;
	int start;

	start = *i;
	while (buf[*i] && ft_isspace(buf[*i]))
		*i += 1;
	tmp = ft_substr(buf, start, *i - start);
	if (!tmp)
	{
		free_tokens_list(tokens_list);
		return ;
	}
	pending_token = create_token(TOKEN_SPACE, &tmp);
	if (!add_token(tokens_list, pending_token))
	{
		free_tokens_list(tokens_list);
		return ;
	}
}
