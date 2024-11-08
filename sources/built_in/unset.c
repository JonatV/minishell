/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:47:07 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/07 12:28:48 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	str_is_in_debut(char *str, char *to_find)
{
	int	i;

	i = 0;
	while (str[i] == to_find[i] && str[i] != '\0' && to_find[i] != '\0')
		i++;
	if (to_find[i] == '\0' && (str[i] == '\0' || str[i] == '='))
		return (1);
	return (0);
}

void	builtin_unset(t_shell *shell, int cmd_num, bool secu)
{
	char	**new_env;
	int		i;
	int		j;
	int		k;
	char	**data_cmd_arg;

	if (secu && !check_data_validity(shell->cmd_array[cmd_num].data, BUILTIN_UNSET))
	{
		ft_putstr_fd("minishell: unset: no options allowed\n", STDERR_FILENO);
		g_exit_status = 2;
		return ;
	}
	if (!shell->cmd_array[cmd_num].data[CMD_ARG])
		return ;
	data_cmd_arg = ft_split(shell->cmd_array[cmd_num].data[CMD_ARG], ' ');
	k = -1;
	while (data_cmd_arg[++k])
	{
		if (ft_strchr(data_cmd_arg[k], '='))
			continue ;
		if (ft_arrayfind(shell->env, data_cmd_arg[k]) == -1)
			continue ;
		new_env = malloc(sizeof(char *) * ft_arraysize(shell->env));
		if (!new_env)
			panic("Malloc in unset", shell);
		i = 0;
		j = 0;
		while (shell->env[i])
		{
			if (str_is_in_debut(shell->env[i], data_cmd_arg[k]))
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
}
