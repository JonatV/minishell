/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:16:19 by haroldsorel       #+#    #+#             */
/*   Updated: 2024/10/25 13:41:46 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

int	set_path(char **cmd)
{
	int		i;
	char	**tpm;
	char	*str;

	i = 0;
	while (g_env[i] && !check_env(g_env[i]))
		i++;
	str = ft_substr(g_env[i], 5, ft_strlen(g_env[i]));
	tpm = ft_split(str, ':');
	i = 0;
	if (!tpm)
		return (0);
	while (tpm[i])
		i++;
	free(str);
	return (set_path_2(cmd, tpm, i));
}

int	check_cmd(t_token *token)
{
	char	*tpm;
	char	*cmd;
	int		i;

	i = 0;
	if (!ft_strncmp(token->value, ".", ft_strlen(token->value) - 1)
		|| !ft_strncmp(token->value, "/", ft_strlen(token->value) - 1))
		return (0);
	while (token->value[i] != '\0' && token->value[i] != 32
		&& token->value[i] != -1)
		i++;
	if (i == 0)
		return (0);
	tpm = ft_substr(token->value, 0, i);
	cmd = ft_strjoin("/", tpm);
	free(tpm);
	return (check_cmd_2(&cmd, token, i));
}

int	check_builtins(t_token *token)
{
	char	*str;
	int		i;

	i = 0;
	while (token->value[i] != '\0' && token->value[i] != 32)
		i++;
	str = ft_substr(token->value, 0, i);
	i = 1;
	if (ft_strncmp(str, "pwd", 3) == 0)
		i = 0;
	if (ft_strncmp(str, "echo", 4) == 0)
		i = 0;
	if (ft_strncmp(str, "cd", 2) == 0)
		i = 0;
	if (ft_strncmp(str, "export", 6) == 0)
		i = 0;
	if (ft_strncmp(str, "unset", 5) == 0)
		i = 0;
	if (ft_strncmp(str, "env", 3) == 0)
		i = 0;
	if (ft_strncmp(str, "exit", 4) == 0)
		i = 0;
	free(str);
	return (i);
}

int	parse_command(t_lists *lst)
{
	while (lst)
	{
		if (lst->token->type == TOKEN_WORD)
		{
			if (check_builtins(lst->token))
				check_cmd(lst->token);
		}
		lst = lst->next;
	}
	return (1);
}
