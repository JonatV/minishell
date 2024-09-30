/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 13:04:14 by jveirman          #+#    #+#             */
/*   Updated: 2024/09/16 09:38:32 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include "../../includes/token.h"
/*
* INFO:
*	find the last arg of the last command
*	and replace the previous shell->last_arg ($_)
*	with this last arg.
*/
static void	update_shlvl(t_shell *shell)
{
	int		pos;
	int		shlvl;
	char	*str_shlvl;
	char	*str_to_add;

	pos = ft_arrayfind(shell->env, "SHLVL");
	if (pos == -1)
		panic("No shlvl has been found", shell); //wip : is it the right behaviour?
	shlvl = ft_atoi(ft_extract(shell->env[pos], '=', 1));
	shlvl++;
	builtin_unset(shell, "SHLVL");
	str_shlvl = ft_itoa(shlvl);
	str_to_add = ft_strjoin("SHLVL=", str_shlvl);
	free(str_shlvl);
	if (!str_to_add)
		panic("Malloc update shell level", shell);
	ft_arraypush(&shell->env, str_to_add);
}

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

/*
* INFO:
*	function to init the minishell env by copying the envp.
*	The var &_ is appart from the shell->env array
*	so it unset this var from the env and place it
*	in the shell->last_arg variable.
*/
void	init_env(t_shell *shell, char **envp)
{
	int		pos;
	int		len;
	int		skip;
	char	*last_arg;

	shell->env = ft_arrayndup(envp, ft_arraysize(envp));
	if (!shell->env)
		panic("Malloc dup env", shell);
	update_shlvl(shell);
	pos = ft_arrayfind(shell->env, "_");
	if (pos == -1)
	{
		last_arg = (char *)malloc(sizeof(char) * 3);
		if (!last_arg)
			panic("Malloc init env", shell);
		ft_strlcpy(last_arg, "_=", 2);
		shell->last_arg = last_arg;
		return ;
	}
	len = ft_strlen(shell->env[pos]);
	skip = 2;
	shell->last_arg = ft_substr(shell->env[pos], skip, len - skip);
	builtin_unset(shell, "_");


	/*testing : find a way to pass the g_env another way than a gobal variable*/


	g_env = ft_arrayndup(envp, ft_arraysize(envp));
	if (!g_env)
		panic("Malloc dup env", shell);
	update_shlvl(shell);
	pos = ft_arrayfind(g_env, "_");
	if (pos == -1)
	{
		last_arg = (char *)malloc(sizeof(char) * 3);
		if (!last_arg)
			panic("Malloc init env", shell);
		ft_strlcpy(last_arg, "_=", 2);
		shell->last_arg = last_arg;
		return ;
	}
	len = ft_strlen(g_env[pos]);
	skip = 2;
	shell->last_arg = ft_substr(g_env[pos], skip, len - skip);
	builtin_unset(shell, "_");
}
