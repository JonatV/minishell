/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 13:04:14 by jveirman          #+#    #+#             */
/*   Updated: 2024/06/13 11:36:44 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
/*
* INFO:
*	find the last arg of the last command
*	and replace the previous shell->last_arg ($_)
*	with this last arg.
*/
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

static void	update_shlvl(t_shell *shell)
{
	int		pos;
	int		number;

	pos = ft_arrayfind(shell->env, "SHLVL");
	if (-1 == pos)
	{
		ft_arraypush(&shell->env, "SHLVL=1");
		return ;
	}
	number = ft_atoi(shell->env[pos] + ft_strlen("SHLVL="));
	free(shell->env[pos]);
	shell->env[pos] = NULL;
	shell->env[pos] = ft_strjoin("SHLVL=", ft_itoa(++number));
}

/*
* INFO:
*	function to init the minishell env by copying the envp.
*	The var &_ is appart from the shell->env array
*	so it unset this var from the env and place it
*	in the shell->last_arg variable.
*/
void	init_env(t_shell *shell, char **envp)
{
	int	pos;
	int	len;
	int	skip;

	shell->env = ft_arrayndup(envp, ft_arraysize(envp));
	if (!shell->env)
		panic("Malloc dup env", shell);
	update_shlvl(shell);
	pos = ft_arrayfind(shell->env, "_");
	len = ft_strlen(shell->env[pos]);
	skip = 2;
	shell->last_arg = ft_substr(shell->env[pos], skip, len - skip);
	builtin_unset(shell, "_");
}
