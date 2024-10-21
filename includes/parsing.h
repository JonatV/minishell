#ifndef PARSING_H
# define PARSING_H

# include <sys/ioctl.h>
# include <termios.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include "../libft/libft.h"
# include "shell.h"
# include "../get_next_line/get_next_line.h"

typedef enum s_token_type
{
	literal,
	space,
	and,
	or,
	simple_redir_left,
	simple_redir_right,
	double_redir_left,
	double_redir_right,
	pipeline,
	single_quote,
	double_quote,
	variable,
	undesirable,
}	t_token_type;

typedef struct s_token
{
	char			*content;
	t_token_type	type;

}	t_token;

typedef struct s_lists
{
	t_token			*token;
	struct s_lists	*next;
	struct s_lists	*prev;
}	t_lists;

typedef struct s_cmd1
{
	int		fd_i; // ✅ // note: default = -2 
	int		fd_o; // ✅ // note: default = -2 
	char	**cmd; // ✅
	/* 
		todo : implement
			char	**here_doc_delimiter;
			char	*here_doc_in;
	*/
	int		type; // ✅
/*
-	int		pipe_i; //⛔
-	int		pipe_o; //⛔
-	int		saved_stdin;//⛔
-	int		saved_stdout;//⛔
-	int		f_redir; // ?
*/
}	t_cmd1;

typedef struct s_all_cmd
{
	struct s_cmd1	*cmds;
	int				nbrcmd; // ! cmd_number
	/*
	-int				**pipefd; //⛔
	- pid_t			*pids;
	*/
	int				status;
}	t_all_cmd;

char			**g_env;
//parsing
int				check_quote_occurence(char *str, int i);
int				check_quotes_op(char **input);
int				unclosed_quotes(char **input);
int				check_operator(char **input, int i);
int				unclosed_operator(char **input);
int				parse_command(t_lists *lst);
int				set_path(char **cmd);
int				set_path_2(char **cmd, char **tpm, int i);
int				check_cmd_2(char **cmd, t_token *token, int i);
int				set_cmd(t_all_cmd *all_cmd, t_lists *lst, int k);
int				parsing(t_all_cmd *all_cmd, char **input, t_lists **lst);
//void			free_cmds(t_all_cmd *all_cmd);
int				check_acces(char **str);
int				check_env(char *str);

int				get_redir_l(t_token *token);
int				get_redir_dl(t_token *token);
int				get_redir_r(t_token *token);
int				get_redir_dr(t_token *token);

//utils
void			init_struct(t_cmd1 *cmd);
int				count_cmd(t_lists *lst);
int				get_type(char **str);
int				print_syntax_error(char *str, int i);
void			ft_free(char *str);
void			input_signals(void);
void			set_sig_code(int err_code);
int				get_sig_code(void);

//token
int				main_token(char *input, t_lists **lst);
#endif
