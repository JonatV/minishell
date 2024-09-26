/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 10:47:29 by jveirman          #+#    #+#             */
/*   Updated: 2024/09/26 14:27:09 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/built_in.h"

/*
*	TODO :
*		Check for the number of arg, it cant accept more arg.
*		Which means, the array will looks like that, no more 
*		shell->cmd_array[0].data[0] = "exit";
*		shell->cmd_array[0].data[1] = NULL;
*/
void	builtin_exit(t_shell *shell)
{
	clean("exit", shell);
	exit(shell->exit_code);
}
