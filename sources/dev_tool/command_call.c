/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_call.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:37:17 by jveirman          #+#    #+#             */
/*   Updated: 2024/06/03 12:21:14 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

void	dev_cmd_call(t_shell shell)
{
	if (ft_strlen(shell.buf) >= 3)
	{
		if (shell.buf[0] == 'e' && shell.buf[1] == 'n' && shell.buf[2] == 'v')
		{
			ft_arrayprint(shell.env, NULL);
		}
	}
}
