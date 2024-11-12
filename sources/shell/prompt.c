/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:00:12 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/12 12:29:18 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	prompt_msg(t_shell *shell)
{
	char	*user;
	int		i;
	int		pos_prompt;

	pos_prompt = 0;
	if (ft_arrayfind(shell->env, "USER") == -1)
	{
		i = 0;
		while (PROMPT_DEFAULT_NAME[i])
			shell->prompt_msg[pos_prompt++] = PROMPT_DEFAULT_NAME[i++];
	}
	user = shell->env[ft_arrayfind(shell->env, "USER")];
	i = 0;
	while (PROMPT_MSG_START[i])
		shell->prompt_msg[pos_prompt++] = PROMPT_MSG_START[i++];
	i = 5;
	while (user[i])
		shell->prompt_msg[pos_prompt++] = user[i++];
	i = 0;
	while (PROMPT_MSG_END[i])
		shell->prompt_msg[pos_prompt++] = PROMPT_MSG_END[i++];
	shell->prompt_msg[pos_prompt] = '\0';
}
