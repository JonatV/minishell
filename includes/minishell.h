/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:55:09 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/14 22:23:04 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*
#####################################################################
#								INCLUDE								#
#####################################################################
*/
# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <string.h>
# include <errno.h>
# include <stdbool.h>
# include <signal.h>

extern int	g_exit_status;

/*
#####################################################################
#								DEFINE								#
#####################################################################
*/

# define NAME "minishell: "
# define DEFAULT_FD -2
# define USE_HEREDOC -3
# define PROMPT_MSG_START "[\033[1;31m"
# define PROMPT_MSG_END "\033[0m] \033[1;36mMinishell \033[32m$\033[0m "
# define PROMPT_DEFAULT_NAME "19"

/*----------------					BUILT-IN				---------------*/
# define B_SIZE 8
# define ERR_ECHO "minishell: echo: no options (but -n) allowed"
# define ERR_ENV "minishell: env: no options nor arguments allowed"
# define ERR_EXIT "minishell: exit: "
# define ERR_EXP "minishell: export: "
# define ERR_UNSET "minishell: unset: no options allowed\n"

/*----------------					EXEC					---------------*/
# define PIPE_WRITE_END 1
# define PIPE_READ_END 0
# define SKIP_EXIT true
# define NOSKIP_EXIT false

/*----------------					SIGNAL					---------------*/
# define SUBPROCESS_SIG -1919

/*----------------					PARSING					---------------*/
# define CMD_NAME 0
# define CMD_FLAG 1
# define CMD_ARG 2
# define CMD_END 3

/*----------------					TOKEN					---------------*/
# define N "\e[0m"
# define ERR_TKNSNTX "minishell: syntax error near unexpected token `"
# define ERR_TKNNL "syntax error near unexpected token `newline'"

/*----------------					ERR_MSG					---------------*/
# define ERR_MALLOC "malloc failed"
# define ERR_FIDIR ": No such file or directory\n"
# define ERR_NMRC ": numeric argument required\n"
# define ERR_IDNTFIR ": not a valid identifier\n"
# define ERR_NOCMD ": command not found\n"
# define ERR_SPCLVAR ": special variable not allowed\n"
# define ERR_EOF "minishell: syntax error: unexpected end of file"

/*
#####################################################################
#							STRUCTURE								#
#####################################################################
*/

typedef typeof(struct sigaction) \
			t_sigaction;
typedef typeof(struct stat) \
			t_stat;

typedef enum e_builtin
{
	BUILTIN_PWD,
	BUILTIN_ENV,
	BUILTIN_EXIT,
	BUILTIN_ECHO,
	BUILTIN_UNSET,
	BUILTIN_CD,
	BUILTIN_EXPORT,
	BUILTIN_NULL,
}	t_builtin;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_HEREDOC,
	TOKEN_DOUBLE_QUOTE,
	TOKEN_SINGLE_QUOTE,
	TOKEN_SPACE,
	TOKEN_SKIP,
	TOKEN_OR,
}	t_token_type;

typedef struct s_cmd
{
	int		fd_in;
	int		fd_out;
	int		builtin_return;
	int		num_arg;
	int		num_flag;
	char	*file_name_in;
	char	*file_name_out;
	char	*data[4];
	char	**here_doc_delimiter;
	char	*here_doc_input;
	char	**final_cmd_line;
}	t_cmd;

typedef struct s_token
{
	t_token_type		type;
	char				*content;
	struct s_token		*next;
}	t_token;

typedef struct s_shell
{
	int		current_fd_in;
	int		current_fd_out;
	int		cmd_number;
	pid_t	pid;
	pid_t	pid_array[1024];
	char	prompt_msg[1024];
	int		number_of_pipe;
	char	*buf;
	t_token	*tokens_list;
	t_cmd	*cmd_array;
	char	**env;
	int		**pipefds;
}	t_shell;

/*
#####################################################################
#						FUNCTIONS PROTOTYPE							#
#####################################################################
*/

// ========== token ==========
/*----------------  handle_all_token_types.c  ---------------*/
void	handle_redirections(t_shell *shell, int *i, t_token **tokens_list);
bool	handle_pipe(t_shell *shell, int *i, t_token **tokens_list);
void	handle_space(t_shell *shell, int *i, t_token **tokens_list);

/*----------------  token_utils.c  ---------------*/
void	free_tokens_list(t_token **tokens);
void	handle_word(t_shell *shell, int *i, t_token **tokens_list);

/*----------------  tokenizer.c  ---------------*/
bool	add_token(t_token **tokens_list, t_token *new_token);
t_token	*create_token(t_token_type type, char **content);
bool	tokenizer(t_shell *shell);

// ========== parser ==========
/*----------------  parse_token_redirection.c  ---------------*/
int		handle_token_redir_heredoc(t_cmd *cmd, t_token **tokens_list);
int		handle_token_redir_append(t_cmd *cmd, t_token **tokens_list);
int		handle_token_redir_out(t_cmd *cmd, t_token **tokens_list);
int		handle_token_redir_in(t_cmd *cmd, t_token **tokens_list);

/*----------------  parsing.c  ---------------*/
bool	parsing(t_shell *shell);

/*----------------  parse_utils.c  ---------------*/
void	init_struct(t_cmd *cmd);
bool	check_for_empty_cmd(t_shell *shell);
int		count_cmd(t_token *tokens_list);
int		get_type(char **str);

/*----------------  cmd_array_builder.c  ---------------*/
bool	cmd_array_builder(t_shell *shell);

/*----------------  parse_token_word.c  ---------------*/
int		handle_token_word(t_cmd *cmd, t_token **tokens_list);

// ========== signal ==========
/*----------------  listener.c  ---------------*/
void	signal_ctlc_on_subprocess(int sig);
void	sigint_handler(int signal);
void	sigeof_handler(t_shell *shell);
void	signal_ctlc_on_fork(int sig);
void	signals_handler(void);

// ========== shell ==========
/*----------------  check_cmd_line_structure.c  ---------------*/
bool	check_cmd_line_structure(t_shell *shell);

/*----------------  check_cmd_line_utils.c  ---------------*/
bool	only_isspace_string(char *buffer);
bool	is_incomplete_cmd_line(char *buffer);
bool	restore_stdin(int stdin_backup, t_shell *shell, bool add_to_history);

/*----------------  env_utils.c  ---------------*/
void	env_unset(t_shell *shell, char *to_remove);
void	init_env(t_shell *shell, char **envp);

/*----------------  exit.c  ---------------*/
void	clean(char *str, t_shell *shell, bool free_env);
void	panic(char *str, t_shell *shell);

/*----------------  free_helper.c  ---------------*/
void	free_shell_struct(t_shell *shell, bool free_env);
void	free_cmd_array_struct(t_shell *shell);

/*----------------  global_utils.c  ---------------*/
void	mini_printf(char *first_part, char *dynamic_info, \
	char *last_part, int fd);
bool	error_msg(char *msg);

/*----------------  init_shell.c  ---------------*/
void	set_default_current_fds(t_shell *shell);

/*----------------  main.c  ---------------*/
void	shell_init(t_shell *shell, char **envp);
int		main(int ac, char **av, char **envp);

/*----------------  prompt.c  ---------------*/
void	prompt_msg(t_shell *shell);

// ========== expander ==========
/*----------------  expander.c  ---------------*/
bool	free_all_segments(char **segments);
bool	assemble_all_segments(char **segments, char **str);
bool	expander(char **env, char **content, t_shell *shell);

/*----------------  special_variables.c  ---------------*/
bool	replace_double_dollar(char **str, int *i);
bool	replace_dollar_question_mark(char **str, int *i);
bool	block_special_variables(char *str, int i);

// ========== built-in ==========
/*----------------  chdir.c  ---------------*/
void	pwd_management(t_shell *shell, char *pwd);
int		builtin_chdir(t_shell *shell, char **data);

/*----------------  chdir_utils.c  ---------------*/
int		count_word(char *str);
char	*get_path_name(t_shell *shell, char **data);

/*----------------  echo.c  ---------------*/
int		builtin_echo(t_shell *shell, char **data);

/*----------------  export.c  ---------------*/
int		builtin_export(t_shell *shell, int cmd_num);

/*----------------  env.c  ---------------*/
int		builtin_env(t_shell *shell, char **data);

/*----------------  unset.c  ---------------*/
int		builtin_unset(t_shell *shell, int cmd_num, bool secu);

/*----------------  exit.c  ---------------*/
int		builtin_exit(t_shell *shell, int i);

/*----------------  pwd.c  ---------------*/
int		builtin_pwd(t_shell *shell, char **data);

/*----------------  export_utils.c  ---------------*/
char	*ft_extract(char *str, char target, int extract_after);
int		print_export(char **array, int fd_out);

/*----------------  utils.c  ---------------*/
bool	check_data_validity(char **data, t_builtin builtin_index);
int		is_builtin(char *to_find);
int		select_builtin(t_shell *shell, int i, \
	int built_in_index, bool skip_exit);

// ========== exec ==========
/*----------------  error.c  ---------------*/
void	fd_error(t_shell *shell, int i);

/*----------------  exec.c  ---------------*/
void	execution(int i, t_shell *shell);
void	shell_executor(t_shell *shell);
void	waiting_for_children(t_shell *shell);

/*----------------  exec_utils.c  ---------------*/
char	*find_valid_path(char *cmd, char **env, t_shell *shell);

/*----------------  exec_utils2.c  ---------------*/
bool	use_builtin_env_changer(t_shell *shell, \
	int *i, int built_in_index);
void	execute_builtin(t_shell *shell, int i, \
	int built_in_index);
bool	prepare_execve_data(t_cmd *cmd);
char	*ft_strjoin_free(char *s1, char *s2);

/*----------------  path_check.c  ---------------*/
bool	check_if_absolute(char *cmd, t_shell *shell);

/*----------------  here_doc.c  ---------------*/
bool	here_doc_management(t_shell *shell);
void	here_doc_exploit(t_shell *shell, int i);

/*----------------  here_doc_utils.c  ---------------*/
int		is_here_doc_available(t_shell *shell, int i);
char	*to_the_delimiter(char *to_find, t_shell *shell);

/*----------------  pipes.c  ---------------*/
void	pipes_init(t_shell *shell);
void	pipes_opening(t_shell *shell);
void	pipes_closing(t_shell *shell);
void	pipes_free(t_shell *shell);
void	parent_process_close_fds(t_shell *shell, int i);

/*----------------  redirection.c  ---------------*/
void	fd_in_management(t_shell *shell, int i);
void	fd_out_management(t_shell *shell, int i);

#endif
