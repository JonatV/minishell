/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:48:28 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/12 17:25:07 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	add_var_full(t_shell *shell, char *var_name, \
	char *str, int var_exist)
{
	int		i;
	char	*var_name_equal;
	bool	success;

	if (var_exist != -1)
		env_unset(shell, var_name);
	var_name_equal = ft_strjoin(var_name, "=");
	if (!var_name_equal)
		panic(ERR_MALLOC, shell);
	i = 0;
	while (str[i])
	{
		if (str[i++] == '=')
			break ;
	}
	if (str[i])
		success = ft_arraypush(&(shell->env), str);
	else
		success = ft_arraypush(&(shell->env), var_name_equal);
	free(var_name_equal);
	return (success);
}

static bool	add_var_name_only(t_shell *shell, char *var_name, int var_exist)
{
	if (var_exist == -1)
		return (ft_arraypush(&(shell->env), var_name));
	return (true);
}

static int	check_var_name(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
	{
		mini_printf(ERR_EXP, str, ERR_IDNTFIR, STDERR_FILENO);
		return (1);
	}
	i++;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			mini_printf(ERR_EXP, str, ERR_IDNTFIR, STDERR_FILENO);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	update_export(t_shell *shell, char *str)
{
	char	*var_name;
	int		var_exist;
	bool	success;

	var_name = ft_extract(str, '=', 0);
	if (!var_name)
		panic(ERR_MALLOC, shell);
	if (check_var_name(var_name) == 1)
	{
		free(var_name);
		return (1);
	}
	var_exist = ft_arrayfind(shell->env, var_name);
	if (ft_strchr(str, '=') == 0)
		success = add_var_name_only(shell, var_name, var_exist);
	else
		success = add_var_full(shell, var_name, str, var_exist);
	free(var_name);
	if (!success)
		panic(ERR_MALLOC, shell);
	return (0);
}

int	builtin_export(t_shell *shell, int cmd_num)
{
	int		j;
	char	**data_cmd_arg;
	int		success;

	if (!check_data_validity(shell->cmd_array[cmd_num].data, BUILTIN_EXPORT))
	{
		error_msg("export: no options allowed");
		return (2);
	}
	data_cmd_arg = NULL;
	if (shell->cmd_array[cmd_num].data[CMD_ARG] != NULL)
	{
		data_cmd_arg = ft_split(shell->cmd_array[cmd_num].data[CMD_ARG], ' ');
		if (!data_cmd_arg)
			panic(ERR_MALLOC, shell);
		j = 0;
		while (data_cmd_arg[j])
			success = update_export(shell, data_cmd_arg[j++]);
		ft_arrayfree(data_cmd_arg);
	}
	else
		return (print_export(shell->env, shell->current_fd_out));
	return (success);
}
