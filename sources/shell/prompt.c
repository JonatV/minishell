/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:00:12 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/07 16:09:08 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	prompt_msg(t_shell *shell)
{
	char	*user;
	int		i;
	int		pos_prompt;

	pos_prompt = 0;
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
