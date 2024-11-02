/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 13:04:14 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/01 22:03:55 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


static int	str_is_in_debut(char *str, char *to_find)
{
	int	i;

	i = 0;
	while (str[i] == to_find[i] && str[i] != '\0' && to_find[i] != '\0')
	{
		i++;
	}
	if (to_find[i] == '\0' && (str[i] == '\0' || str[i] == '='))
		return (1);
	return (0);
}

void	env_unset(t_shell *shell, char *to_remove)
{
	char	**new_env;
	int		i;
	int		j;

	if (ft_arrayfind(shell->env, to_remove) == -1)
	{
		ft_putstr_fd("error: ", shell->current_fd_out);
		ft_putstr_fd(to_remove, shell->current_fd_out);
		ft_putendl_fd(" var isn't found", shell->current_fd_out);
	}
	new_env = malloc(sizeof(char *) * ft_arraysize(shell->env));
	if (!new_env)
		panic("Malloc in unset", shell);
	i = 0;
	j = 0;
	while (shell->env[i])
	{
		if (str_is_in_debut(shell->env[i], to_remove))
		{
			i++;
			continue ;
		}
		new_env[j++] = ft_strdup(shell->env[i++]);
	}
	new_env[j] = NULL;
	ft_arrayfree(shell->env);
	shell->env = new_env;
}

static int	get_shlvl(t_shell *shell)
{
	int		pos;
	int		shlvl;
	char	*shlvl_str;


	pos = ft_arrayfind(shell->env, "SHLVL");
	if (pos == -1)
		panic("No shlvl has been found", shell); //wip : is it the right behaviour?
	shlvl_str = ft_extract(shell->env[pos], '=', 1);
	shlvl = ft_atoi(shlvl_str);
	free(shlvl_str);
	return (shlvl);
}

/*
* INFO:
*	find the last arg of the last command
*	and replace the previous shell->last_arg ($_)
*	with this last arg.
*/
static void	update_shlvl(t_shell *shell)
{
	int		shlvl;
	char	*str_shlvl;
	char	*str_to_add;

	shlvl = get_shlvl(shell);
	shlvl++;
	env_unset(shell, "SHLVL");
	str_shlvl = ft_itoa(shlvl);
	str_to_add = ft_strjoin("SHLVL=", str_shlvl);
	free(str_shlvl);
	if (!str_to_add)
		panic("Malloc update shell level", shell);
	ft_arraypush(&shell->env, str_to_add);
	free(str_to_add);
}

void	update_var_lastarg(t_shell *shell)
{
	/*
	int	data_end;
	int	cmd_end;

	cmd_end = shell->cmd_number - 1;
	data_end = ft_arraysize(shell->cmd_array[cmd_end].data);
	if (shell->last_arg)
		free(shell->last_arg);
	shell->last_arg = NULL;
	shell->last_arg = ft_strdup(shell->cmd_array[cmd_end].data[data_end - 1]); // wip it segfault - cause merging process then no data array yet //todo display
	*/
	shell->last_arg = ft_strdup("==work in progress=="); //wip 
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
	if (shell->last_arg)
	{
		free(shell->last_arg);
		shell->last_arg = NULL;
	}
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
	env_unset(shell, "_");
}
