/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_array_all_cmd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:03:02 by jveirman          #+#    #+#             */
/*   Updated: 2024/10/27 21:08:43 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void print_cmd1(t_cmd *cmd)
{
	if (!cmd)
		return;

	printf("Input File Descriptor: %d\n", cmd->fd_in);
	printf("Output File Descriptor: %d\n", cmd->fd_out);
	printf("Command:\n");
	if (!cmd->data[CMD_NAME])
		printf(YELLOW"Name = unknow\n"N);
	else
		printf(GREEN"Name = %s\n"N, cmd->data[CMD_NAME]);
	if (!cmd->data[CMD_ARG])
		printf(YELLOW"Argument(s) = unknow\n"N);
	else
		printf(GREEN"Argument(s) = %s\n"N, cmd->data[CMD_ARG]);
	if (!cmd->data[CMD_FLAG])
		printf(YELLOW"Flag(s) = unknow\n"N);
	else
		printf(GREEN"Option = %s\n"N, cmd->data[CMD_FLAG]);
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
		printf("\n\e[4;33m Command %d:\e[0m\n", i + 1);
		print_cmd1(&shell->cmd_array[i]);
	}
}
