/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:24:42 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/06 23:34:33 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_pwd(t_shell *shell, char **data)
{
	char	*pwd;
	char	*s;

	if (!check_data_validity(data, BUILTIN_PWD))
	{
		ft_putstr_fd("minishell: pwd: no options allowed\n", STDERR_FILENO);
		return;
	}
	s = "PWD";
	pwd = shell->env[ft_arrayfind(shell->env, s)];
	ft_putendl_fd(pwd + ft_strlen(s), shell->current_fd_out);
}
