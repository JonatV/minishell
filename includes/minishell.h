#ifndef MINISHELL_H
# define MINISHELL_H

/*
#####################################################################
#								INCLUDE								#
#####################################################################
*/
# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <string.h>
# include <errno.h>
# include <stdbool.h>
# include <signal.h>

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

/*----------------					BUILT-IN				---------------*/
# define B_SIZE 8

/*----------------					DEV						---------------*/
# define DEV_COMMAND_START "\033[1;33m/*----------------				START COMMAND				---------------*/\033[0m"
# define DEV_COMMAND_END "\033[1;33m/*----------------				END COMMAND				---------------*/\033[0m"

/*----------------					EXEC					---------------*/
# define MSG_ERROR "\033[1;33mERROR\033[0m"


/*----------------					PARSING					---------------*/
# define CMD_NAME 0
# define CMD_FLAG 1
# define CMD_ARG 2
# define CMD_END 3

/*----------------					TOKEN					---------------*/
#define GREEN "\e[32m"
#define YELLOW "\033[0;33m"
#define N "\e[0m"

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
	TOKEN_ENV_VAR,
	TOKEN_BIG_QUOTES,
	TOKEN_SMALL_QUOTES,
}	t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	struct s_token		*next;
}	t_token;

/*
#####################################################################
#						FUNCTIONS PROTOTYPE							#
#####################################################################
*/

/*----------------  tokenizer.c  ---------------*/
void		handle_variables(t_token **tokens, t_shell *shell);
void		handle_special_chars(char **input, t_token **tokens);
void		handle_word(char **input, t_token **tokens);
t_token		*tokenize_input(t_shell *shell);

/*----------------  tokenizer_utils.c  ---------------*/
char		*ft_strndup(const char *src, size_t n);
size_t		ft_strnlen(const char *s, size_t maxlen);
const char	*get_token_type_name(t_token_type type);
void		display_tokens(t_token *tokens);
t_token		*new_token(t_token_type type, char *value);
void		add_token_to_list(t_token **tokens, t_token *new_token);
void		free_tokens(t_token *tokens);
void		update_quote_status(char c, int *in_quote, char *quote_char);
void		add_word_token_if_valid(char **start, char **input, t_token **tokens);

/*----------------  utils.c  ---------------*/
void		init_struct(t_cmd *cmd);
int			count_cmd(t_token *tokens_list);
int			get_type(char **str);
int			print_syntax_error(char *str, int i);
void		ft_free(char *str);

/*----------------  parse_token_word.c  ---------------*/
bool		handle_token_word(t_cmd *cmd, char *value);

/*----------------  parse_token_redirection.c  ---------------*/
bool		handle_token_redir_heredoc(t_cmd *cmd, t_token **tokens_list);
bool		handle_token_redir_append(t_cmd *cmd, t_token **tokens_list);
bool		handle_token_redir_out(t_cmd *cmd, t_token **tokens_list);
bool		handle_token_redir_in(t_cmd *cmd, t_token **tokens_list);

/*----------------  parsing.c  ---------------*/
int			parsing(t_shell *shell, t_token **tokens_list);

/*----------------  cmd_array_builder.c  ---------------*/
bool 		cmd_array_builder(t_shell *shell, t_token **tokens_list);

/*----------------  listener.c  ---------------*/
void		sigint_handler(int signal);
void		sigeof_handler(t_shell *shell);
void		signals_handler(void);

/*----------------  prompt.c  ---------------*/
void		prompt_msg(t_shell *shell);

/*----------------  check_cmd_line_structure.c  ---------------*/
bool		check_cmd_line_structure(t_shell *shell);

/*----------------  env_utils.c  ---------------*/
void		update_var_lastarg(t_shell *shell);
void		init_env(t_shell *shell, char **envp);

/*----------------  exit.c  ---------------*/
void		clean(char *str, t_shell *shell);
void		panic(char *str, t_shell *shell);

/*----------------  main.c  ---------------*/
void		shell_init(t_shell *shell, char **envp);
int			main(int ac, char **av, char **envp);

/*----------------  expander.c  ---------------*/
int			expander(char **array, char **str);

/*----------------  pwd.c  ---------------*/
void		builtin_pwd(t_shell *shell, char **data, t_builtin builtin_index);

/*----------------  unset.c  ---------------*/
void		builtin_unset(t_shell *shell, char *to_remove);

/*----------------  env.c  ---------------*/
void		builtin_env(t_shell *shell, char **data);

/*----------------  utils.c  ---------------*/
bool		check_data_validity(char **data, t_builtin builtin_index);
int			is_builtin(char *to_find);
void		select_builtin(t_shell *shell, int i, int built_in_index);

/*----------------  echo.c  ---------------*/
void		builtin_echo(char **data);

/*----------------  chdir.c  ---------------*/
int			builtin_chdir(t_shell *shell, char *destination);

/*----------------  export_utils.c  ---------------*/
int			check_var_name(char *str);
char		*ft_extract(char *str, char target, int extract_after);
void		print_export(char **array);

/*----------------  exit.c  ---------------*/
void		builtin_exit(t_shell *shell);

/*----------------  export.c  ---------------*/
void		update_export(t_shell *shell, char *str);
void		builtin_export(t_shell *shell, int i);

/*----------------  print_array_all_cmd.c  ---------------*/
void 		print_all_cmd(t_shell *shell);

/*----------------  command_call.c  ---------------*/
void		dev_cmd_call(t_shell *shell);

/*----------------  fake_array_from_parsing.c  ---------------*/
void		init_all_cmd(t_shell *shell);

/*----------------  fork.c  ---------------*/
void		forks_process(t_shell *shell);
void		waiting_for_children(t_shell *shell);

/*----------------  redirection.c  ---------------*/
void		fd_in_management(int i, int j, t_shell shell);
void		fd_out_management(int i, int j, t_shell shell);

/*----------------  exec.c  ---------------*/
void		shell_executor(t_shell *shell);
void		execution(int i, t_shell *shell);

/*----------------  here_doc_utils.c  ---------------*/
int			is_here_doc_available(t_shell *shell, int i);
char		*to_the_delimiter(char *to_find);

/*----------------  exec_utils.c  ---------------*/
char		*find_valid_path(char *cmd, char **env);

/*----------------  pipes.c  ---------------*/
void		pipes_init(t_shell *shell);
void		pipes_opening(t_shell *shell);
void		pipes_closing(t_shell *shell);

/*----------------  here_doc.c  ---------------*/
void		here_doc_management(t_shell *shell);
void		here_doc_exploit(t_shell *shell, int i);

/*----------------  error.c  ---------------*/
void		fd_error(t_shell *shell, int i);

#endif
