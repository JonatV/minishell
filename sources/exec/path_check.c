/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:17:13 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/14 15:30:19 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	check_if_absolute(char *cmd, t_shell *shell)
{
	t_stat	path_cmd;

	if (0 == access(cmd, F_OK & X_OK))
	{
		if (stat(cmd, &path_cmd) == 0)
		{
			if (S_ISDIR(path_cmd.st_mode))
			{
				mini_printf(NAME, cmd, ": is a directory\n", STDERR_FILENO);
				clean(NULL, shell, false);
				exit(126);
			}
		}
		return (true);
	}
	return (false);
}
