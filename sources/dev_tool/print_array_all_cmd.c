/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_array_all_cmd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:03:02 by jveirman          #+#    #+#             */
/*   Updated: 2024/10/21 16:05:14 by jveirman         ###   ########.fr       */
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
	printf("Input Pipe: %d\n", cmd->pipe_i);
	printf("Output Pipe: %d\n", cmd->pipe_o);
	printf("Saved Stdin: %d\n", cmd->saved_stdin);
	printf("Saved Stdout: %d\n", cmd->saved_stdout);
	printf("File Redirection: %d\n", cmd->f_redir);
		
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

	// Print pipe file descriptors if they exist
	if (all_cmd->pipefd) {
		printf("\n\e[4;33m Pipes:\n \e[0m");
		for (int i = 0; i < all_cmd->nbrcmd - 1; i++) {
			printf("Pipe %d: [%d, %d]\n", i, all_cmd->pipefd[i][0], all_cmd->pipefd[i][1]);
		}
	}

	// Print PIDs if they exist
	if (all_cmd->pids) {
		printf("\n\e[4;33m PIDs:\n \e[0m");
		for (int i = 0; i < all_cmd->nbrcmd; i++) {
			printf("PID %d: %d\n", i + 1, all_cmd->pids[i]);
		}
	}
}
