/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_array_all_cmd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:03:02 by jveirman          #+#    #+#             */
/*   Updated: 2024/10/21 17:35:56 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/dev.h"

static void print_cmd1(t_cmd1 *cmd)
{
	if (!cmd)
		return;

	printf("Command Type: %d\n", cmd->type);
	printf("Input File Descriptor: %d\n", cmd->fd_i);
	printf("Output File Descriptor: %d\n", cmd->fd_o);
		
	printf("Command: ");
	if (cmd->cmd) {
		for (int i = 0; cmd->cmd[i] != NULL; i++) {
			printf("\e[35m%s \e[0m", cmd->cmd[i]);
		}
	}
	printf("\n");
}

void print_all_cmd(t_all_cmd *all_cmd)
{
	if (!all_cmd)
		return;

	printf("Number of Commands: %d\n", all_cmd->nbrcmd);
	printf("Status: %d\n", all_cmd->status);
		
	// Print the commands
	for (int i = 0; i < all_cmd->nbrcmd; i++) {
		printf("\n\e[4;33m Command %d:\n \e[0m", i + 1);
		print_cmd1(&all_cmd->cmds[i]);
	}

	// Print PIDs if they exist
	if (all_cmd->pids) {
		printf("\n\e[4;33m PIDs:\n \e[0m");
		for (int i = 0; i < all_cmd->nbrcmd; i++) {
			printf("PID %d: %d\n", i + 1, all_cmd->pids[i]);
		}
	}
}
