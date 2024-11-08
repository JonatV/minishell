/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:29:56 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/07 12:27:44 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	check_data_validity(char **data, t_builtin builtin_index)
{
	if (BUILTIN_PWD == builtin_index)
	{
		if (data[CMD_FLAG])
			return (false);
	}
	else if (BUILTIN_ENV == builtin_index)
	{
		if (data[CMD_FLAG] || data[CMD_ARG])
			return (false);
	}
	else if (BUILTIN_UNSET == builtin_index)
	{
		if (data[CMD_FLAG])
			return (false);
	}
	else if (BUILTIN_EXPORT == builtin_index)
	{
		if (data[CMD_FLAG])
			return (false);
	}
	else if (BUILTIN_ECHO == builtin_index)
	{
		if (data[CMD_FLAG])
			return (false);
	}
	else if (BUILTIN_CD == builtin_index)
	{
		if (data[CMD_FLAG])
			return (false);
	}
	// printf("data[NAME] = [%s] - data[FLAG] = [%s] - data[ARG] = [%s]\n", data[CMD_NAME], data[CMD_FLAG], data[CMD_ARG]);
	// else if (BUILTIN_ECHO == builtin_number)
	// 	if (data[CMD_FLAG][0] == '-' && data[CMD_FLAG][1] == 'n')
	// 		return ()
	return (true);
}

int	is_builtin(char *to_find)
{
	int					i;
	const char	*built_in[B_SIZE];

	built_in[BUILTIN_PWD] = "pwd";
	built_in[BUILTIN_ENV] = "env";
	built_in[BUILTIN_EXIT] = "exit";
	built_in[BUILTIN_ECHO] = "echo";
	built_in[BUILTIN_UNSET] = "unset";
	built_in[BUILTIN_CD] = "cd";
	built_in[BUILTIN_EXPORT] = "export";
	built_in[BUILTIN_NULL] = NULL;
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
	char	**data;

	data = shell->cmd_array[i].data;
	if (built_in_index == BUILTIN_PWD)
		builtin_pwd(shell, data);
	else if (built_in_index == BUILTIN_ENV)
		builtin_env(shell, data);
	else if (built_in_index == BUILTIN_EXIT)
		builtin_exit(shell, i);
	else if (built_in_index == BUILTIN_ECHO)
		builtin_echo(shell, data);
	else if (built_in_index == BUILTIN_UNSET)
		builtin_unset(shell, i, true);
	else if (built_in_index == BUILTIN_CD)
		builtin_chdir(shell, data);
	else if (built_in_index == BUILTIN_EXPORT)
		builtin_export(shell, i);
}
