/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:29:56 by jveirman          #+#    #+#             */
/*   Updated: 2024/10/27 10:55:54 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin(char *to_find)
{
	int					i;
	const char *const	built_in[B_SIZE] = \
	{"pwd", "env", "exit", "echo", "unset", "cd", "export", NULL};

	i = ft_arrayfind((char **)built_in, to_find);
	return (i);
}

/*
* TODO:
*	- ✅pwd
*	- ✅chdir
*	- ✅unset
*	- ✅export
*	- ✅env
*	- echo
*	- ✅exit
*/
void	select_builtin(t_shell *shell, int i, int built_in_index)
{
	if (built_in_index == 0)
		builtin_pwd(shell);
	else if (built_in_index == 1)
		builtin_env(shell);
	else if (built_in_index == 2)
		builtin_exit(shell);
	else if (built_in_index == 3)
		builtin_echo(shell->cmd_array[i].data);
	else if (built_in_index == 4)
		builtin_unset(shell, shell->cmd_array[i].data[1]);
	else if (built_in_index == 5)
		builtin_chdir(shell, shell->cmd_array[i].data[1]);
	else if (built_in_index == 6)
		builtin_export(shell, i);
}
