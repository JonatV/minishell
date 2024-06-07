/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:00:12 by jveirman          #+#    #+#             */
/*   Updated: 2024/06/07 15:31:08 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/shell.h"

void	prompt_msg(t_shell *shell)
{
	char	*bracket_open;
	char	*user;
	char	*bracket_close;

	user = shell->env[ft_arrayfind(shell->env, "USER")];
	user = ft_substr(user, 5, 15);
	if (!user)
		panic("Malloc prompt_msg", shell);
	bracket_open = ft_strjoin("[\033[1;31m", user);
	free(user);
	if (!bracket_open)
		panic("Malloc prompt_msg", shell);
	bracket_close = ft_strjoin(bracket_open, "\033[0m] ");
	free(bracket_open);
	if (!bracket_close)
		panic("Malloc prompt_msg", shell);
	shell->prompt_msg = ft_strjoin(bracket_close, PROMPT_MSG);
	free(bracket_close);
	if (!shell->prompt_msg)
		panic("Malloc prompt_msg", shell);
}
