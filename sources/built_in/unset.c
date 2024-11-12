/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:47:07 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/12 17:45:32 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	str_is_in_debut(char *str, char *to_find)
{
	int	i;

	i = 0;
	while (str[i] == to_find[i] && str[i] != '\0' && to_find[i] != '\0')
		i++;
	return (to_find[i] == '\0' && (str[i] == '\0' || str[i] == '='));
}

static void	remove_env_var(t_shell *shell, char *current_var, char ***array)
{
	char	**new_env;
	int		i;
	int		j;

	new_env = malloc(sizeof(char *) * ft_arraysize(shell->env));
	if (!new_env)
	{
		ft_arrayfree(*array);
		panic(ERR_MALLOC, shell);
	}
	i = 0;
	j = 0;
	while (shell->env[i])
	{
		if (!str_is_in_debut(shell->env[i], current_var))
			new_env[j++] = ft_strdup(shell->env[i]);
		i++;
	}
	new_env[j] = NULL;
	ft_arrayfree(shell->env);
	shell->env = new_env;
}

int	builtin_unset(t_shell *shell, int cmd_num, bool secu)
{
	int		k;
	char	**data_cmd_arg;

	if (secu && \
		!check_data_validity(shell->cmd_array[cmd_num].data, BUILTIN_UNSET))
	{
		ft_putendl_fd(ERR_UNSET, STDERR_FILENO);
		return (2);
	}
	if (!shell->cmd_array[cmd_num].data[CMD_ARG])
		return (0);
	data_cmd_arg = ft_split(shell->cmd_array[cmd_num].data[CMD_ARG], ' ');
	if (!data_cmd_arg)
		panic(ERR_MALLOC, shell);
	k = -1;
	while (data_cmd_arg[++k])
	{
		if (!ft_strchr(data_cmd_arg[k], '=') && \
			ft_arrayfind(shell->env, data_cmd_arg[k]) != -1)
			remove_env_var(shell, data_cmd_arg[k], &data_cmd_arg);
	}
	ft_arrayfree(data_cmd_arg);
	return (0);
}
