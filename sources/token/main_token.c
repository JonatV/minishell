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

void	print_lst(t_lists **lst)
{
	t_lists	*current;
	int		i;

	current = *lst;
	i = 0;
	while (current != NULL)
	{
		printf("%d\tcontent : %s\ttype : %d\n", i, current->token->content, current->token->type);
		current = current->next;
		i++;
	}
	printf("\n\nNEXT TOKENIZATION\n\n");
}

int	main_token(char *input, t_lists **lst)
{
	if (!token(input, lst))
		return (0);
	print_lst(lst);
	set_variable(lst);
	print_lst(lst);
	if (!second_token(lst))
		return (0);
	print_lst(lst);
	delete_quotes(lst);
	print_lst(lst);
	if (!third_token(lst))
		return (0);
	print_lst(lst);
		return (1);
}
