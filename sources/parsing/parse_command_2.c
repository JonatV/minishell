/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:18:46 by haroldsorel       #+#    #+#             */
/*   Updated: 2024/10/25 13:36:25 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

int	check_cmd_2(char **cmd, t_token *token, int i)
{
	char	*str;

	if (!set_path(cmd))
	{
		free(*cmd);
		return (0);
	}
	str = ft_substr(token->value, i, ft_strlen(token->value));
	free(token->value);
	token->value = ft_strjoin(*cmd, str);
	free(*cmd);
	free(str);
	return (1);
}

int	set_path_2(char **cmd, char **tpm, int i)
{
	char	**path;

	path = malloc(sizeof(char *) * (i + 1));
	if (!path)
		return (0);
	i = -1;
	while (tpm[++i])
		path[i] = ft_strjoin(tpm[i], *cmd);
	path[i] = NULL;
	i = check_acces(path);
	if (i == -1)
	{
		//free_env(tpm);
		//free_env(path);
		return (0);
	}
	ft_free(*cmd);
	*cmd = ft_strdup(path[i]);
	//free_env(path);
	//free_env(tpm);
	return (1);
}

int	check_env(char *str)
{
	if (ft_strlen(str) > 3)
	{
		if (str[0] == 'P')
			if (str[1] == 'A')
				if (str[2] == 'T')
					if (str[3] == 'H')
						return (1);
	}
	return (0);
}

int	check_acces(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		if (access(str[i], F_OK) != -1 && access(str[i], X_OK) != -1)
			return (i);
		i++;
	}
	return (-1);
}
