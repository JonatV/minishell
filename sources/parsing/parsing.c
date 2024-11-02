/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:21:39 by haroldsorel       #+#    #+#             */
/*   Updated: 2024/11/03 00:31:11 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static int	single_token(t_lists *lst)
// {
// 	int				i;
// 	t_token_type	type;

// 	i = 0;
// 	if (!lst)
// 		return (0);
// 	type = lst->token->type;
// 	while (lst)
// 	{
// 		lst = lst->next;
// 		i++;
// 	} // todo : isnt it better to check if lst->token->next is false (meaning the token is alone)
// 	if (i == 1)
// 		if (type != TOKEN_WORD && type != TOKEN_REDIR_HEREDOC
// 			&& type != TOKEN_REDIR_APPEND
// 			&& type != TOKEN_REDIR_IN && type != TOKEN_REDIR_OUT)
// 			return (0);
// 	return (1);
// }

int	parsing(t_shell *shell)
{
	// int	i;

	// i = 0;
	// if (!check_quotes_op(input)) //todo
	// 	return (0);
	// if (!single_token(lst)) //todo to keep?
	// 	return (0);
	if (!cmd_array_builder(shell))
	{
		printf("Error while building cmd array\n");
		return (0);
	}
	// if (!parse_command(lst))
	// 	return (0);
	// if (!set_cmd(shell, lst, i))
	// {
	// 	return (0);
	// }
	//todo Make a function fill_data
	return (1);
}
