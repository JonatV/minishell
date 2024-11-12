/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:09:18 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/12 23:05:56 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	use_builtin_env_changer(t_shell *shell, int *i, int built_in_index)
{
	if (built_in_index == BUILTIN_EXIT || built_in_index == BUILTIN_CD \
		|| built_in_index == BUILTIN_UNSET || (built_in_index == BUILTIN_EXPORT \
		&& shell->cmd_array[*i].data[CMD_ARG] != NULL))
		shell->cmd_array[*i].builtin_return = select_builtin(shell, *i, \
			built_in_index, SKIP_EXIT);
	return (false);
}

void	execute_builtin(t_shell *shell, int i, int built_in_index)
{
	if (built_in_index == -1)
		return ;
	if (built_in_index == BUILTIN_EXIT || built_in_index == BUILTIN_CD \
		|| built_in_index == BUILTIN_UNSET || (built_in_index == BUILTIN_EXPORT \
		&& shell->cmd_array[i].data[CMD_ARG] != NULL))
		exit(shell->cmd_array[i].builtin_return);
	select_builtin(shell, i, built_in_index, NOSKIP_EXIT);
}

static bool	push_data(t_cmd *cmd, int pos)
{
	char	**data_array;
	int		i;

	data_array = NULL;
	if (cmd->data[pos] != NULL)
	{
		data_array = ft_split(cmd->data[pos], ' ');
		if (!data_array)
			return (false);
		i = -1;
		while (data_array[++i])
		{
			if (!ft_arraypush(&cmd->final_cmd_line, data_array[i]))
			{
				ft_arrayfree(data_array);
				return (false);
			}
		}
	}
	return (true);
}

/*
*	@note:	Function that concatenate the two array, CMD_FLAG and CMD ARG,
*			into one null terminated array -> final_cmd_line.
*	@param:	Current command structure
*/
bool	prepare_execve_data(t_cmd *cmd)
{
	if (!ft_arraypush(&cmd->final_cmd_line, cmd->data[CMD_NAME]))
		return (false);
	if (!push_data(cmd, CMD_FLAG) || !push_data(cmd, CMD_ARG))
		return (false);
	return (true);
}

char	*ft_strjoin_free(char *s1, char *s2, t_shell *shell)
{
	char	*new_str;

	new_str = ft_strjoin(s1, s2);
	free(s1);
	if (!new_str)
		return (NULL);
	return (new_str);
}
