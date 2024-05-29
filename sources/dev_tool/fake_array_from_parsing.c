/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fake_array_from_parsing.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:09:34 by jveirman          #+#    #+#             */
/*   Updated: 2024/05/28 17:18:18 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

/*
#####################################################################
#																	#
#							DEVELOPMENT								#
#																	#
#####################################################################
*/

void init_all_cmd(t_shell *shell)
{
	shell->cmd_number = 3;
	shell->cmd_array = malloc(shell->cmd_number * (sizeof(t_cmd)));
	if (shell->cmd_array == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	// Init. first command
	shell->cmd_array[0].fd_in = open("test_infile", O_RDONLY, 0777);
	shell->cmd_array[0].fd_out = -2;
	shell->cmd_array[0].data[0] = "sort";
	shell->cmd_array[0].data[1] = "-r";
	shell->cmd_array[0].data[2] = NULL;
	shell->cmd_array[0].path = "/usr/bin/sort";

	// Init. second command
	shell->cmd_array[1].fd_in = -2;
	shell->cmd_array[1].fd_out = open("outfile", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	shell->cmd_array[1].data[0] = "uniq";
	shell->cmd_array[1].data[1] = "-c";
	shell->cmd_array[1].data[2] = NULL;
	shell->cmd_array[1].path = "/usr/bin/uniq";
	
	// Init. third command
	shell->cmd_array[2].fd_in = -2;
	shell->cmd_array[2].fd_out = -2;
	shell->cmd_array[2].data[0] = "sort";
	shell->cmd_array[2].data[1] = "-r";
	shell->cmd_array[2].data[2] = NULL;
	shell->cmd_array[2].path = "/usr/bin/sort";

}

// void init_all_cmd(t_shell_dev_dev *shell_dev)
// {
// 	shell_dev->cmd_number = 3;
// 	shell_dev->current = 1;
// 	shell_dev->cmd_array = malloc(shell_dev->cmd_number * (sizeof(t_cmd)));
// 	if (shell_dev->cmd_array == NULL) {
// 		perror("malloc");
// 		exit(EXIT_FAILURE);
// 	}

// 	// Init. first command
// 	shell_dev->cmd_array[0].fd_in = open("file1", O_RDONLY, 0777);
// 	shell_dev->cmd_array[0].fd_out = -2;
// 	shell_dev->cmd_array[0].data[0] = "sort";
// 	shell_dev->cmd_array[0].data[1] = "-r";
// 	shell_dev->cmd_array[0].data[2] = NULL;
// 	shell_dev->cmd_array[0].path = "/usr/bin/sort";

// 	// // Init. first command
// 	// shell_dev->cmd_array[0].fd_in = -2;
// 	// shell_dev->cmd_array[0].fd_out = -2;
// 	// shell_dev->cmd_array[0].data[0] = "ls";
// 	// shell_dev->cmd_array[0].data[1] = "-la";
// 	// shell_dev->cmd_array[0].data[2] = NULL;
// 	// shell_dev->cmd_array[0].path = "/usr/bin/ls";

// 	// // Init. first command
// 	// shell_dev->cmd_array[1].fd_in = -2;
// 	// shell_dev->cmd_array[1].fd_out = -2;
// 	// shell_dev->cmd_array[1].data[0] = "sort";
// 	// shell_dev->cmd_array[1].data[1] = "-r";
// 	// shell_dev->cmd_array[1].data[2] = NULL;
// 	// shell_dev->cmd_array[1].path = "/usr/bin/sort";

// 	shell_dev->cmd_array[1].fd_in = -2;
// 	shell_dev->cmd_array[1].fd_out = open("outfile", O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	shell_dev->cmd_array[1].data[0] = "uniq";
// 	shell_dev->cmd_array[1].data[1] = "-c";
// 	shell_dev->cmd_array[1].data[2] = NULL;
// 	shell_dev->cmd_array[1].path = "/usr/bin/uniq";
	
// 	shell_dev->cmd_array[2].fd_in = -2;
// 	shell_dev->cmd_array[2].fd_out = -2;
// 	shell_dev->cmd_array[2].data[0] = "sort";
// 	shell_dev->cmd_array[2].data[1] = "-r";
// 	shell_dev->cmd_array[2].data[2] = NULL;
// 	shell_dev->cmd_array[2].path = "/usr/bin/sort";

// 	// Init. third command
// 	// shell_dev->cmd_array[2].fd_in = -2;
// 	// shell_dev->cmd_array[2].fd_out = -2;
// 	// shell_dev->cmd_array[2].data[0] = "head";
// 	// shell_dev->cmd_array[2].data[1] = "-3";
// 	// shell_dev->cmd_array[2].data[2] = NULL;
// 	// shell_dev->cmd_array[2].path = "/usr/bin/head";
// }
