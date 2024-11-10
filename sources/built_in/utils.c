/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:29:56 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/10 15:00:56 by jveirman         ###   ########.fr       */
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
	return (true);
}

int	is_builtin(char *to_find)
{
	int					i;
	const char	*built_in[B_SIZE];

	if (!to_find)
		return (-1);
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
int	select_builtin(t_shell *shell, int i, int built_in_index, bool skip_exit)
{
	char	**data;
	int		ret_value;

	data = shell->cmd_array[i].data;
	if (built_in_index == BUILTIN_PWD)
		ret_value = builtin_pwd(shell, data);
	else if (built_in_index == BUILTIN_ENV)
		ret_value = builtin_env(shell, data);
	else if (built_in_index == BUILTIN_EXIT)
		ret_value = builtin_exit(shell, i);
	else if (built_in_index == BUILTIN_ECHO)
		ret_value = builtin_echo(shell, data);
	else if (built_in_index == BUILTIN_UNSET)
		ret_value = builtin_unset(shell, i, true);
	else if (built_in_index == BUILTIN_CD)
		ret_value = builtin_chdir(shell, data);
	else if (built_in_index == BUILTIN_EXPORT)
		ret_value = builtin_export(shell, i);
	if (ret_value == -1)
		panic(ERR_MALLOC, shell);
	if (skip_exit)
		return (ret_value);
	exit(ret_value);
}
