/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:00:12 by jveirman          #+#    #+#             */
/*   Updated: 2024/06/03 13:13:57 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/shell.h"

void	prompt_msg(t_shell *shell)
{
	char	*bracket_open;
	char	*user;
	char	*bracket_close;

	user = shell->env[ft_arrayfind(shell->env, "USER=")];
	user = ft_substr(user, 5, 15);
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
