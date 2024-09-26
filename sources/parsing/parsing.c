/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:21:39 by haroldsorel       #+#    #+#             */
/*   Updated: 2024/09/26 11:22:14 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/parsing.h"

int	single_token(t_lists *lst)
{
	int				i;
	t_token_type	type;

	i = 0;
	if (!lst)
		return (0);
	type = lst->token->type;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	if (i == 1)
		if (type != literal && type != double_redir_left
			&& type != double_redir_right
			&& type != simple_redir_left && type != simple_redir_right)
			return (0);
	return (1);
}

int	parsing(t_all_cmd *all_cmd, char **input, t_lists **lst)
{
	int	i;

	i = 0;
	if (!check_quotes_op(input))
		return (0);
	if (!main_token(*input, lst))
		return (0);
	if (!single_token(*lst))
		return (0);
	if (!parse_command(*lst))
		return (0);
	if (!set_cmd(all_cmd, *lst, i))
	{
		//free_cmds(all_cmd);
		return (0);
	}
	return (1);
}
