/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_array_all_cmd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:03:02 by jveirman          #+#    #+#             */
/*   Updated: 2024/10/27 10:56:13 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void print_cmd1(t_cmd *cmd)
{
	if (!cmd)
		return;

	printf("Command Type: %d\n", cmd->type);
	printf("Input File Descriptor: %d\n", cmd->fd_in);
	printf("Output File Descriptor: %d\n", cmd->fd_out);
		
	printf("Command: ");
	if (cmd->cmd) {
		for (int i = 0; cmd->cmd[i] != NULL; i++) {
			printf("\e[35m%s \e[0m", cmd->cmd[i]);
		}
	}
	printf("\n");
}

void print_all_cmd(t_shell *shell)
{
	if (!shell)
		return;
	printf("Number of Commands: %d\n", shell->cmd_number);
	printf("Status: %d\n", shell->status);
	// Print the commands
	for (int i = 0; i < shell->cmd_number; i++) {
		printf("\n\e[4;33m Command %d:\n \e[0m", i + 1);
		print_cmd1(&shell->cmd_array[i]);
	}
}
