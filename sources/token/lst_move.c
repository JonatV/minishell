/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsorel <hsorel@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:49:34 by hsorel            #+#    #+#             */
/*   Updated: 2024/09/26 12:49:36 by hsorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/token.h"

t_lists	*newlst(t_token *token)
{
	t_lists	*new;

	new = malloc(sizeof(t_lists));
	if (!new)
		return (NULL);
	new->token = token;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_lists	*first_lst(t_lists *lst)
{
	while (lst)
	{
		if (lst->prev == NULL)
			return (lst);
		lst = lst->prev;
	}
	return (lst);
}

t_lists	*last_lst(t_lists *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	add_back(t_lists **lst, t_lists *new)
{
	t_lists	*last;

	if (*lst)
	{
		last = last_lst(*lst);
		last->next = new;
		new->prev = last;
	}
	else
		*lst = new;
}
