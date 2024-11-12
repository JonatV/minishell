/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:51:03 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/12 18:32:16 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*find_in_env(char *cmd, char **env, t_shell *shell);

static void	is_directory(char *cmd, t_shell *shell, bool skip_slash)
{
	Stat	path_cmd;
	int		end;

	end = ft_strlen(cmd) - 1;
	if (cmd[end] == '/' || skip_slash)
	{
		if (stat(cmd, &path_cmd) == 0)
		{
			if (S_ISDIR(path_cmd.st_mode))
			{
				mini_printf(NAME, cmd, ": is a directory\n", STDERR_FILENO);
				clean(NULL, shell, false);
				exit(126);
			}
		}
		else
		{
			mini_printf(NAME, cmd, ERR_FIDIR, STDERR_FILENO);
			clean(NULL, shell, false);
			exit(127);
		}
	}
}

char	*find_valid_path(char *cmd, char **env, t_shell *shell)
{
	is_directory(cmd, shell, false);
	if (cmd[0] == '.' && cmd[1] == '/')
	{
		is_directory(cmd, shell, false);
		if (0 == access(cmd, F_OK))
		{
			if (0 == access(cmd, X_OK))
				return (cmd);
			else
			{
				mini_printf(NAME, cmd, ": Permission denied\n", STDERR_FILENO);
				clean(NULL, shell, false);
				exit(126);
			}
		}
		else
		{
			mini_printf(NAME, cmd, ERR_FIDIR, STDERR_FILENO);
			clean(NULL, shell, false);
			exit(127);
		}
	}
	return (find_in_env(cmd, env, shell));
}

static char	*find_in_env(char *cmd, char **env, t_shell *shell)
{
	char	**all_paths;
	char	*temp_path;
	char	*full_path;
	int		i;

	i = ft_arrayfind(env, "PATH");
	if (i == -1)
	{
		is_directory(cmd, shell, true);
		if (0 == access(cmd, F_OK))
		{
			if (0 == access(cmd, X_OK))
				return (cmd);
			else
			{
				mini_printf(NAME, cmd, ": Permission denied\n", STDERR_FILENO);
				clean(NULL, shell, false);
				exit(126);
			}
		}
		else
		{
			mini_printf(NAME, cmd, ERR_FIDIR, STDERR_FILENO);
			clean(NULL, shell, false);
			exit(127);
		}
	}
	all_paths = ft_split(env[i] + 5, ':');
	if (!all_paths)
		panic(ERR_MALLOC, shell);
	i = -1;
	while (all_paths[++i])
	{
		temp_path = ft_strjoin(all_paths[i], "/");
		if (!temp_path)
		{
			ft_arrayfree(all_paths);
			panic(ERR_MALLOC, shell);
		}
		full_path = ft_strjoin(temp_path, cmd);
		free(temp_path);
		if (!full_path)
		{
			ft_arrayfree(all_paths);
			panic(ERR_MALLOC, shell);
		}
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
