/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 13:04:14 by jveirman          #+#    #+#             */
/*   Updated: 2024/06/07 16:00:03 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

void	update_var_lastarg(t_shell *shell)
{
	int	data_end;
	int	cmd_end;

	cmd_end = shell->cmd_number - 1;
	data_end = ft_arraysize(shell->cmd_array[cmd_end].data);
	if (shell->last_arg)
		free(shell->last_arg);
	shell->last_arg = NULL;
	shell->last_arg = ft_strdup(shell->cmd_array[cmd_end].data[data_end - 1]);
}

void	init_env(t_shell *shell, char **envp)
{
	int	pos;
	int	len;
	int	skip;

	shell->env = ft_arrayndup(envp, ft_arraysize(envp));
	if (!shell->env)
		panic("Malloc dup env", shell);
	pos = ft_arrayfind(shell->env, "_");
	len = ft_strlen(shell->env[pos]);
	skip = 2;
	shell->last_arg = ft_substr(shell->env[pos], skip, len - skip);
	printf("first init last arg [%s]\n", shell->last_arg);
	builtin_unset(shell, "_");
}
