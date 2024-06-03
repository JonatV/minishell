/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:32:37 by jveirman          #+#    #+#             */
/*   Updated: 2024/06/03 12:00:20 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "shell.h"
/*
#####################################################################
#							DEFINE									#
#####################################################################
*/
# define MSG_ERROR "\033[1;33m ERROR\033[0m"

/*
#####################################################################
#							STRUCTURE								#
#####################################################################
*/
typedef struct s_shell	t_shell;
typedef struct s_cmd	t_cmd;

/*
#####################################################################
#						FUNCTIONS PROTOTYPE							#
#####################################################################
*/

/*----------------				EXECUTE				---------------*/
void	shell_executor(t_shell *shell, char **envp);
void	execution(int i, t_shell *shell, char **envp);

/*----------------				PIPES				---------------*/
void	pipes_init(t_shell *shell);
void	pipes_opening(t_shell *shell);
void	pipes_closing(t_shell *shell);

/*----------------				REDIRECTION			---------------*/
void	fd_in_management(int i, int j, t_shell shell);
void	fd_out_management(int i, int j, t_shell shell);

/*----------------				FORK				---------------*/
void	forks_process(t_shell *shell, char **envp);
void	waiting_for_children(t_shell shell);

/*----------------				ERROR				---------------*/
void	fd_error(t_shell *shell, int i);
void	panic(char *str, t_shell *shell);
void	clean(char *str, t_shell *shell);

/*----------------				DEV_TOOLS			---------------*/
void	init_all_cmd(t_shell *shell);

#endif
