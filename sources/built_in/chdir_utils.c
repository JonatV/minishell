/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:48:14 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/12 17:48:47 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_word(char *str)
{
	int	i;
	int	word_count;

	if (!str)
		return (0);
	word_count = 1;
	i = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]) && str[i + 1])
			word_count++;
		i++;
	}
	return (word_count);
}

char	*get_path_name(t_shell *shell, char **data)
{
	int		i;
	char	*path_name;

	if (!data[CMD_ARG])
	{
		i = ft_arrayfind(shell->env, "HOME");
		if (i == -1)
		{
			error_msg("cd: HOME not set");
			return (NULL);
		}
		path_name = ft_strchr(shell->env[i], '=');
		return (path_name + 1);
	}
	return (data[CMD_ARG]);
}
