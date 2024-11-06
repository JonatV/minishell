/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:51:03 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/06 20:37:27 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*find_in_env(char *cmd, char **env);

char	*find_valid_path(char *cmd, char **env)
{
	if (0 == access(cmd, F_OK | X_OK))
	{
		if (cmd[0] == '.' && cmd[1] == '/')
			return (cmd);
	}
	return (find_in_env(cmd, env));
}

static char	*find_in_env(char *cmd, char **env)
{
	char	**all_paths;
	char	*temp_path;
	char	*full_path;
	int		i;

	i = ft_arrayfind(env, "PATH");
	if (i == -1)
		return (NULL);
	all_paths = ft_split(env[i] + 5, ':');
	i = -1;
	while (all_paths[++i])
	{
		temp_path = ft_strjoin(all_paths[i], "/");
		full_path = ft_strjoin(temp_path, cmd);
		free(temp_path);
		if (0 == access(full_path, F_OK | X_OK))
		{
			ft_arrayfree(all_paths);
			return (full_path);
		}
		free(full_path);
	}
	ft_arrayfree(all_paths);
	return (0);
}

bool	use_builtin_cmd(t_shell *shell, int *i, int *built_in_triggered)
{
	int	built_in_index;

	built_in_index = is_builtin(shell->cmd_array[*i].data[CMD_NAME]);
	if (built_in_index > -1)
	{
		set_default_current_fds(shell);
		if (shell->cmd_number != 1)
			shell->current_fd_out = shell->pipefds[*i][PIPE_WRITE_END];
		select_builtin(shell, *i, built_in_index);
		free(shell->pipefds);
		shell->pipefds = NULL;
		(*built_in_triggered)++;
		(*i)++;
		return (true);
	}
	return (false);
}
