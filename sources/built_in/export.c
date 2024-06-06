/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:48:28 by jveirman          #+#    #+#             */
/*   Updated: 2024/06/06 11:57:59 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/built_in.h"

static void	add_var_full(t_shell *shell, char *var_name, char *str)
{
	int		i;
	char	*var_name_equal;

	builtin_unset(shell, var_name);
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
		ft_arraypush(&(shell->env), ft_strjoin(var_name, "="));
}

void	add_var_name_only(t_shell *shell, char *var_name, int var_exist)
{
	if (var_exist == -1)
		ft_arraypush(&(shell->env), var_name);
}

/*
* TODO: create the check_var_name function
*/
void	update_export(t_shell *shell, char *str)
{
	char	*var_name;
	int		var_exist;

	var_name = ft_extract(str, '=');
	if (!var_name)
		panic("Malloc export var", shell);
	if (check_var_name(var_name) != 0)
		return ;
	var_exist = ft_arrayfind(shell->env, var_name);
	if (ft_strchr(str, '=') == 0)
		add_var_name_only(shell, var_name, var_exist);
	else
		add_var_full(shell, var_name, str);
	free(var_name);
}

void	builtin_export(t_shell *shell)
{
	char	*dev_buf;

	dev_buf = shell->buf + ft_strlen("export");
	if (!(dev_buf[0]))
		print_export(shell->env);
	else
		update_export(shell, dev_buf + 1);
}
