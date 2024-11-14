/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:51:03 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/14 15:32:03 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*find_in_env(char *cmd, char **env, t_shell *shell);

static void	is_directory(char *cmd, t_shell *shell, bool skip_slash)
{
	t_stat	path_cmd;
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

static void	handle_no_path_var(char *cmd, t_shell *shell)
{
	is_directory(cmd, shell, true);
	if (0 == access(cmd, F_OK))
	{
		if (0 == access(cmd, X_OK))
			return ;
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

static char	*try_paths(char **all_paths, char *cmd, t_shell *shell, int i)
{
	char	*temp_path;
	char	*full_path;

	while (all_paths[++i])
	{
		temp_path = ft_strjoin(all_paths[i], "/");
		if (!temp_path)
		{
			ft_arrayfree(all_paths);
			panic(ERR_MALLOC, shell);
		}
		full_path = ft_strjoin_free(temp_path, cmd);
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
	return (NULL);
}

static char	*find_in_env(char *cmd, char **env, t_shell *shell)
{
	char	**all_paths;
	char	*full_path;
	int		i;

	i = ft_arrayfind(env, "PATH");
	if (i == -1)
	{
		handle_no_path_var(cmd, shell);
		return (cmd);
	}
	all_paths = ft_split(env[i] + 5, ':');
	if (!all_paths)
		panic(ERR_MALLOC, shell);
	if (check_if_absolute(cmd, shell))
		return (cmd);
	i = -1;
	full_path = try_paths(all_paths, cmd, shell, i);
	if (!full_path)
		ft_arrayfree(all_paths);
	return (full_path);
}
