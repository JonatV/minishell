/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:48:28 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/06 02:57:07 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	add_var_full(t_shell *shell, char *var_name, char *str, int var_exist)
{
	int		i;
	char	*var_name_equal;
	
	if (var_exist != -1)
		env_unset(shell, var_name);
	var_name_equal = ft_strjoin(var_name, "=");
	if (!var_name_equal)
	{
		free(var_name);
		panic("Malloc failed when adding var to env", shell);
	}
	i = 0;
	while (str[i])
	{
		if (str[i++] == '=')
			break ;
	}
	if (str[i])
		ft_arraypush(&(shell->env), str);
	else
		ft_arraypush(&(shell->env), var_name_equal);
}

static void	add_var_name_only(t_shell *shell, char *var_name, int var_exist)
{
	if (var_exist == -1)
		ft_arraypush(&(shell->env), var_name);
}

/*
* TODO:
*	- create the check_var_name function
*/
static void	update_export(t_shell *shell, char *str)
{
	char	*var_name;
	int		var_exist;

	var_name = ft_extract(str, '=', 0);
	if (!var_name)
		panic("Malloc export var", shell);
	// if (check_var_name(var_name) != 0)
	// 	return ;
	var_exist = ft_arrayfind(shell->env, var_name);
	if (ft_strchr(str, '=') == 0)
		add_var_name_only(shell, var_name, var_exist);
	else
		add_var_full(shell, var_name, str, var_exist);
	free(var_name);
}

void	builtin_export(t_shell *shell, int cmd_num)
{
	int	j;
	char	**data_cmd_arg;
	
	if (!check_data_validity(shell->cmd_array[cmd_num].data, BUILTIN_EXPORT))
	{
		ft_putstr_fd("Minishell: export: no options allowed\n", STDERR_FILENO);
		return ;
	}
	data_cmd_arg = NULL;
	if (shell->cmd_array[cmd_num].data[CMD_ARG] != NULL)
	{
		data_cmd_arg = ft_split(shell->cmd_array[cmd_num].data[CMD_ARG], ' ');
		j = 0;
		while (data_cmd_arg[j])
			update_export(shell, data_cmd_arg[j++]);
	}
	else
		print_export(shell->env, shell->current_fd_out);
}
