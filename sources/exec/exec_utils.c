/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:51:03 by jveirman          #+#    #+#             */
/*   Updated: 2024/06/12 12:21:27 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

char	*find_valid_path(char *cmd, char **env)
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
