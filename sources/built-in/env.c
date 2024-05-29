/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:27:43 by jveirman          #+#    #+#             */
/*   Updated: 2024/05/28 17:28:59 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/env.h"

void	dup_env(t_list **list_env, char **envp, t_shell *shell)
{
	int		i;
	char	*temp;
	t_list	*new_node;

	temp = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		temp = ft_strdup(envp[i]);
		if (!temp)
			panic("Malloc dup_envp on ft_strdup", shell);
		new_node = ft_lstnew(temp);
		if (!new_node)
			panic("Malloc dup_envp on new_node", shell);
		ft_lstadd_back(list_env, new_node);
		i++;
	}
}
