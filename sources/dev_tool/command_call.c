/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_call.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:37:17 by jveirman          #+#    #+#             */
/*   Updated: 2024/06/03 14:56:40 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/dev.h"

static int	str_is_in_debut(char *str, char *to_find)
{
	int	i;

	i = 0;
	while (str[i] == to_find[i] && str[i] != '\0' && to_find[i] != '\0')
	{
		i++;
	}
	if (to_find[i] == '\0')
		return (1);
	return (0);
}

void	dev_cmd_call(t_shell *shell)
{
	if (ft_strlen(shell->buf) >= 3)
	{
		if (shell->buf[0] == 'e' && shell->buf[1] == 'n' && shell->buf[2] == 'v')
		{
			ft_putendl_fd(DEV_COMMAND_START, 1);
			ft_arrayprint(shell->env, NULL);
			ft_putendl_fd(DEV_COMMAND_END, 0);
		}
		else if (str_is_in_debut(shell->buf, "unset "))
		{
			ft_putendl_fd(DEV_COMMAND_START, 1);
			builtin_unset(shell, shell->buf + 6);
			ft_putendl_fd(DEV_COMMAND_END, 0);
		}
		else if (str_is_in_debut(shell->buf, "export"))
		{
			ft_putendl_fd(DEV_COMMAND_START, 1);
			builtin_export(shell);
			ft_putendl_fd(DEV_COMMAND_END, 0);
		}
	}
}
