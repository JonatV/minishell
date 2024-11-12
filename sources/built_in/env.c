/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s9.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:27:43 by jveirman          #+#    #+#             */
/*   Updated: 2024/10/30 17:35:32 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_env(t_shell *shell, char **data)
{
	int		i;
	char	**array;

	if (!check_data_validity(data, BUILTIN_ENV))
	{
		ft_putendl_fd(ERR_ENV, STDERR_FILENO);
		return (2);
	}
	array = shell->env;
	i = 0;
	while (array[i])
	{
		if (ft_strchr(array[i], '=') == 0)
		{
			i++;
			continue ;
		}
		else
			ft_putendl_fd(array[i], shell->current_fd_out);
		i++;
	}
	return (0);
}
