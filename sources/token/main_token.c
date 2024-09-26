/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsorel <hsorel@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:49:41 by hsorel            #+#    #+#             */
/*   Updated: 2024/09/26 12:49:43 by hsorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/token.h"

int	main_token(char *input, t_lists **lst)
{
	if (!token(input, lst))
		return (0);
	set_variable(lst);
	if (!second_token(lst))
		return (0);
	delete_quotes(lst);
	if (!third_token(lst))
		return (0);
	return (1);
}
