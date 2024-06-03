/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:01:49 by jveirman          #+#    #+#             */
/*   Updated: 2024/06/03 12:20:33 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

/*
#####################################################################
#																	#
#						ERROR MANAGEMENT							#
#																	#
#####################################################################
*/

/*
	- ✅ pipefds in pipes.c 
	- ✅ prompt msg
	- ✅ env array
		- ✅ content in the array
	- ✅ array of the cmd parsed
*/
static void	free_machine(t_shell *shell)
{
	if (shell->pipefds != NULL)
		free(shell->pipefds);
	if (shell->prompt_msg != NULL)
		free(shell->prompt_msg);
	// if (shell->env != NULL)
	ft_arrayfree(shell->env);
	if (shell->cmd_array)
		free(shell->cmd_array);
}

void	clean(char *str, t_shell *shell)
{
	if (str)
		ft_putstr(str);
	free_machine(shell);
	exit(EXIT_SUCCESS);
}

void	panic(char *str, t_shell *shell)
{
	ft_putstr(MSG_ERROR);
	if (str)
	{
		ft_putstr(" : ");
		ft_putstr(str);
	}
	ft_putstr("\n");
	if (shell != NULL)
		free_machine(shell);
	exit(EXIT_FAILURE);
}

void	fd_error(t_shell *shell, int i)
{
	if (shell->cmd_array[i].fd_in == -1)
		panic("in file", shell);
	if (shell->cmd_array[i].fd_out == -1)
		panic("out file", shell);
}
