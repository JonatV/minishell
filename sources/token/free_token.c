/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsorel <hsorel@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:49:23 by hsorel            #+#    #+#             */
/*   Updated: 2024/09/26 12:49:25 by hsorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/token.h"

void	free_content(t_lists **lst)
{
	while (*lst)
	{
		if ((*lst)->token)
			if ((*lst)->token->content)
				free((*lst)->token->content);
		*lst = (*lst)->next;
	}
}

void	free_token(t_lists **lst)
{
	while (*lst)
	{
		if ((*lst)->token)
			free((*lst)->token);
		*lst = (*lst)->next;
	}
}

void	free_lst(t_lists **lst)
{
	t_lists	*tpm;

	tpm = *lst;
	free_content(lst);
	*lst = tpm;
	free_token(lst);
	*lst = tpm;
	while (*lst)
	{
		tpm = (*lst)->next;
		if (*lst)
			free(*lst);
		*lst = tpm;
	}
	*lst = NULL;
}
