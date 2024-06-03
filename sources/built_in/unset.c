/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:47:07 by jveirman          #+#    #+#             */
/*   Updated: 2024/06/03 14:55:55 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/built_in.h"

static int	str_is_in_debut(char *str, char *to_find)
{
	int	i;

	i = 0;
	while (str[i] == to_find[i] && str[i] != '\0' && to_find[i] != '\0')
	{
		i++;
	}
	if (to_find[i] == '\0')
		return (1);
	return (0);
}

void	builtin_unset(t_shell *shell, char *to_remove)
{
	char	**new_env;
	int		i;
	int		j;

	if (!ft_arrayfind(shell->env, to_remove))
		return ;
	new_env = malloc(sizeof(char *) * ft_arraysize(shell->env));
	if (!new_env)
		panic("Malloc in unset", shell);
	i = 0;
	j = 0;
	while (shell->env[i])
	{
		if (str_is_in_debut(shell->env[i], to_remove))
		{
			i++;
			continue ;
		}
		new_env[j] = ft_strdup(shell->env[i]);
		j++;
		i++;
	}
	new_env[j] = NULL;
	ft_arrayfree(shell->env);
	shell->env = new_env;
}
