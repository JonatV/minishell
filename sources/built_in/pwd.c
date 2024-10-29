/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:24:42 by jveirman          #+#    #+#             */
/*   Updated: 2024/10/29 12:18:09 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_pwd(t_shell *shell, char **data, t_builtin builtin_index)
{
	char	*pwd;
	char	*s;

	if (!check_data_validity(data, builtin_index))
	{
		printf("minishell: pwd: no options allowed\n");
		return;
	}
	s = "PWD";
	pwd = shell->env[ft_arrayfind(shell->env, s)];
	ft_putendl_fd(pwd + ft_strlen(s), 1);
}
