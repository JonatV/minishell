/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:21:39 by haroldsorel       #+#    #+#             */
/*   Updated: 2024/10/22 14:47:44 by jveirman         ###   ########.fr       */
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

int	parsing(t_shell *shell, char **input)
{
	int	i;
	t_lists *lst;

	lst = NULL;
	i = 0;
	if (!check_quotes_op(input))
		return (0);
	if (!main_token(*input, &lst))
		return (0);
	if (!single_token(lst))
		return (0);
	if (!parse_command(lst))
		return (0);
	if (!set_cmd(shell, lst, i))
	{
		//free_cmds(all_cmd);
		return (0);
	}
	//todo Make a function fill_data
	return (1);
}
