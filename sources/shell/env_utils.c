/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 13:04:14 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/12 17:30:51 by jveirman         ###   ########.fr       */
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
		return ;
	new_env = malloc(sizeof(char *) * ft_arraysize(shell->env));
	if (!new_env)
		panic(ERR_MALLOC, shell);
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
		return (1);
	shlvl_str = ft_extract(shell->env[pos], '=', 1);
	if (!shlvl_str)
		panic(ERR_MALLOC, shell);
	shlvl = ft_atoi(shlvl_str);
	free(shlvl_str);
	return (shlvl);
}

static void	update_shlvl(t_shell *shell)
{
	int		shlvl;
	char	*str_shlvl;
	char	*str_to_add;

	shlvl = get_shlvl(shell);
	if (shlvl == -1)
	{
		if (!ft_arraypush(&shell->env, "SHLVL=1"))
			panic(ERR_MALLOC, shell);
		return ;
	}
	shlvl++;
	env_unset(shell, "SHLVL");
	str_shlvl = ft_itoa(shlvl);
	str_to_add = ft_strjoin("SHLVL=", str_shlvl);
	free(str_shlvl);
	if (!str_to_add)
		panic(ERR_MALLOC, shell);
	if (!ft_arraypush(&shell->env, str_to_add))
	{
		if (str_to_add)
			free(str_to_add);
		panic(ERR_MALLOC, shell);
	}
	free(str_to_add);
}

void	init_env(t_shell *shell, char **envp)
{
	int		pos;
	char	*last_arg;

	shell->env = ft_arrayndup(envp, ft_arraysize(envp));
	if (!shell->env)
		panic(ERR_MALLOC, shell);
	update_shlvl(shell);
	pos = ft_arrayfind(shell->env, "_");
	last_arg = ft_strdup("_=/usr/bin/env");
	if (!last_arg)
		panic(ERR_MALLOC, shell);
	if (pos != -1)
	{
		if (!ft_arraypush(&shell->env, last_arg))
		{
			free(last_arg);
			panic(ERR_MALLOC, shell);
		}
		free(last_arg);
		return ;
	}
	free(shell->env[pos]);
	shell->env[pos] = last_arg;
}
