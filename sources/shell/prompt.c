/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:00:12 by jveirman          #+#    #+#             */
/*   Updated: 2024/05/28 15:01:37 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/shell.h"

void	prompt_msg(t_shell *shell, t_shell copy)
{
	char	*bracket_open;
	char	*user;
	char	*bracket_close;

	while (ft_strnstr(copy.env->content, "USER=", 5) == 0)
	{
		copy.env = copy.env->next;
		if (copy.env->next == NULL)
			break ;
	}
	user = ft_substr(copy.env->content, 5, 15);
	if (!user)
		panic("Malloc prompt_msg", shell);
	bracket_open = ft_strjoin("[\033[1;31m", user);
	if (!bracket_open)
		panic("Malloc prompt_msg", shell);
	bracket_close = ft_strjoin(bracket_open, "\033[0m] ");
	if (!bracket_close)
		panic("Malloc prompt_msg", shell);
	shell->prompt_msg = ft_strjoin(bracket_close, PROMPT_MSG);
	free(user);
	free(bracket_open);
	free(bracket_close);
	if (!shell->prompt_msg)
		panic("Malloc prompt_msg", shell);
}
