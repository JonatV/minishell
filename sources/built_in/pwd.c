/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:24:42 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/09 18:57:42 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_pwd(t_shell *shell, char **data)
{
	char	*pwd;
	char	*s;
	int		pos;
	char	temp[1024];

	s = "PWD";
	if (!check_data_validity(data, BUILTIN_PWD))
	{
		ft_putstr_fd("minishell: pwd: no options allowed\n", STDERR_FILENO);
		return (2);
	}
	pos = ft_arrayfind(shell->env, s);
	if (pos == -1)
	{
		if (getcwd(temp, sizeof(temp)) == NULL)
			panic("getcwd failed", shell);
		pwd_management(shell, temp);
	}
	pwd = shell->env[ft_arrayfind(shell->env, s)];
	ft_putendl_fd(pwd + ft_strlen(s), shell->current_fd_out);
	return (0);
}
