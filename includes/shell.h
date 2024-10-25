/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:57:45 by jveirman          #+#    #+#             */
/*   Updated: 2024/10/25 14:18:32 by jveirman         ###   ########.fr       */
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
# include <stdbool.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "exec.h"
# include "signal.h"
# include "built_in.h"
# include "parsing.h"
# include "token.h"
# include "dev.h" //dev

/*
#####################################################################
#								DEFINE								#
#####################################################################
*/

# define DEFAULT_FD -2
# define PROMPT_MSG "\033[1;36mMinishell \033[32m$ \033[0m"

/*----------------				STATUSES CODE				---------------*/
# define SUCCESS		0
# define GEN_ERROR		1
# define MISUSE			2
# define NOT_EXEC		126
# define NOT_FOUND		127
# define INV_ARGUMENT	128
# define END_CTRL_C		130

/*
#####################################################################
#							STRUCTURE								#
#####################################################################
*/

typedef struct s_cmd
{
	int		fd_in;
	int		fd_out;
	char	*data[4];
	char	**here_doc_delimiter;
	char	*here_doc_input;
	char	**cmd; //wip will be replace by data

	// wip - merging
	int		type;
}	t_cmd;

typedef struct s_shell
{
	int		cmd_number;
	t_cmd	*cmd_array;		// malloc
	int		*pipefds;		// malloc
	char	**env;			// malloc + inside malloc
	char	*prompt_msg;	// malloc
	char	*buf;			// malloc form readline, don't handle
	int		exit_status;
	char	*last_arg;
	int		exit_code;

	// wip - merging
	int		status;
}	t_shell;

/*
#####################################################################
#						FUNCTIONS PROTOTYPE							#
#####################################################################
*/
/*----------------				PROMPT				---------------*/
void	prompt_msg(t_shell *shell);

/*----------------				MAIN				---------------*/
void	shell_init(t_shell *shell, char **envp);

/*----------------				EXIT				---------------*/
void	panic(char *str, t_shell *shell);
void	clean(char *str, t_shell *shell);

/*----------------				DEV_TOOLS			---------------*/
void	dev_cmd_call(t_shell *shell);

/*----------------				ENV					---------------*/
void	update_var_lastarg(t_shell *shell);
void	init_env(t_shell *shell, char **envp);

#endif
