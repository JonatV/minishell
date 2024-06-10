/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fake_array_from_parsing.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:09:34 by jveirman          #+#    #+#             */
/*   Updated: 2024/06/10 12:50:04 by jveirman         ###   ########.fr       */
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

// void	dup_env(t_list **list_env, char **envp, t_shell *shell)
// {
// 	int		i;
// 	char	*temp;
// 	t_list	*new_node;

// 	temp = NULL;
// 	i = 0;
// 	while (envp[i] != NULL)
// 	{
// 		temp = ft_strdup(envp[i]);
// 		if (!temp)
// 			panic("Malloc dup_envp on ft_strdup", shell);
// 		new_node = ft_lstnew(temp);
// 		if (!new_node)
// 			panic("Malloc dup_envp on new_node", shell);
// 		ft_lstadd_back(list_env, new_node);
// 		i++;
// 	}
// }

void	init_all_cmd(t_shell *shell)
{
	shell->cmd_number = 1;
	shell->cmd_array = malloc(shell->cmd_number * (sizeof(t_cmd)));
	if (shell->cmd_array == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	// Init. first command
	shell->cmd_array[0].fd_in = DEFAULT_FD;
	shell->cmd_array[0].fd_out = DEFAULT_FD;
	shell->cmd_array[0].data[0] = "ls";
	shell->cmd_array[0].data[1] = "sources/built_in";
	shell->cmd_array[0].data[2] = NULL;
	shell->cmd_array[0].path = "/usr/bin/ls";
}
// void init_all_cmd(t_shell *shell)
// {
// 	shell->cmd_number = 1;
// 	shell->cmd_array = malloc(shell->cmd_number * (sizeof(t_cmd)));
// 	if (shell->cmd_array == NULL) {
// 		perror("malloc");
// 		exit(EXIT_FAILURE);
// 	}
// 	// Init. first command
// 	shell->cmd_array[0].fd_in = DEFAULT_FD;
// 	shell->cmd_array[0].fd_out = DEFAULT_FD;
// 	shell->cmd_array[0].data[0] = "export";
// 	shell->cmd_array[0].data[1] = "foo=bar";
// 	shell->cmd_array[0].data[2] = "no_equal";
// 	shell->cmd_array[0].data[3] = "no_value_only=";
// 	shell->cmd_array[0].data[4] = "ITSHOULDWORK=yes";
// 	shell->cmd_array[0].data[5] = NULL;
// 	shell->cmd_array[0].path = NULL;
// }

// void init_all_cmd(t_shell *shell)
// {
// 	shell->cmd_number = 3;
// 	shell->cmd_array = malloc(shell->cmd_number * (sizeof(t_cmd)));
// 	if (shell->cmd_array == NULL) {
// 		perror("malloc");
// 		exit(EXIT_FAILURE);
// 	}
// 	// Init. first command
// 	shell->cmd_array[0].fd_in = open("test_infile", O_RDONLY, 0777);
// 	shell->cmd_array[0].fd_out = -2;
// 	shell->cmd_array[0].data[0] = "sort";
// 	shell->cmd_array[0].data[1] = "-r";
// 	shell->cmd_array[0].data[2] = NULL;
// 	shell->cmd_array[0].path = "/usr/bin/sort";

// 	// Init. second command
// 	shell->cmd_array[1].fd_in = -2;
// 	shell->cmd_array[1].fd_out = open("outfile", O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	shell->cmd_array[1].data[0] = "uniq";
// 	shell->cmd_array[1].data[1] = "-c";
// 	shell->cmd_array[1].data[2] = NULL;
// 	shell->cmd_array[1].path = "/usr/bin/uniq";
	
// 	// Init. third command
// 	shell->cmd_array[2].fd_in = -2;
// 	shell->cmd_array[2].fd_out = -2;
// 	shell->cmd_array[2].data[0] = "sort";
// 	shell->cmd_array[2].data[1] = "-r";
// 	shell->cmd_array[2].data[2] = NULL;
// 	shell->cmd_array[2].path = "/usr/bin/sort";
// }

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
