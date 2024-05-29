/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdisplay.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 19:11:00 by jveirman          #+#    #+#             */
/*   Updated: 2024/05/28 17:33:20 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdisplay(t_list *list)
{
	int	size;

	size = ft_lstsize(list);
	while (list)
	{
		ft_putendl_fd(list->content, 0);
		list = list->next;
	}
}
