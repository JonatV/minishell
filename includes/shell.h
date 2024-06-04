/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:57:45 by jveirman          #+#    #+#             */
/*   Updated: 2024/06/04 15:21:41 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H
# include "../libft/libft.h"
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "exec.h"
# include "signal.h"
# include "built_in.h"

/*
#####################################################################
#								DEFINE								#
#####################################################################
*/

# define DEFAULT_FD -2
# define PROMPT_MSG "\033[1;36mMinishell \033[32m$ \033[0m"

/*
#####################################################################
#							STRUCTURE								#
#####################################################################
*/

typedef struct s_cmd
{
	int		fd_in;
	int		fd_out;
	char	*data[3];
	char	*path;
}	t_cmd;

typedef struct s_shell
{
	int		cmd_number;
	t_cmd	*cmd_array;		// malloc
	int		*pipefds;		// malloc
	char	**env;			// malloc + inside malloc
	char	*prompt_msg;	// malloc
	char	*buf;			// malloc from readline, don't handle
	int		exit_status;
}	t_shell;

/*
#####################################################################
#						FUNCTIONS PROTOTYPE							#
#####################################################################
*/
/*----------------					PROMPT			---------------*/
void	prompt_msg(t_shell *shell);

/*----------------					MAIN			---------------*/
void	shell_init(t_shell *shell, char **envp);

/*----------------				EXIT				---------------*/
void	panic(char *str, t_shell *shell);
void	clean(char *str, t_shell *shell);

/*----------------				DEV_TOOLS			---------------*/
void	dev_cmd_call(t_shell *shell);

#endif
