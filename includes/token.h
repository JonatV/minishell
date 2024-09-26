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
# include "../get_next_line/get_next_line.h"

char			**g_env;

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
	int		type;
	char	**cmd;
	int		fd_i;
	int		fd_o;
	int		pipe_i;
	int		pipe_o;
	int		saved_stdin;
	int		saved_stdout;
	int		f_redir;
}	t_cmd1;

int				main_token(char *input, t_lists **lst);
t_token			*create_token(char *content, t_token_type type);
int				token(char *input, t_lists **lst);
t_lists			*newlst(t_token *token);
void			add_back(t_lists **lst, t_lists *new);
t_lists			*first_lst(t_lists *lst);
int				second_token(t_lists **lst);
int				third_token(t_lists **lst);
void			free_lst(t_lists **lst);
int				delete_quotes(t_lists **lst);
int				check_variable(t_lists **lst);
int				search_variable(char **str);
int				set_variable(t_lists **lst);
int				check_status(char **str);
t_token_type	check_double(char *content, t_token_type type);
char			*fill_content_literal(char	*content, t_lists **lst,
					char *split);
int				fill_content(t_lists **lst, t_lists **newlist,
					t_token_type type);
char			*set_split(char c);
char			*new_content_literal(t_lists **lst);
char			*new_content_redir(t_lists **lst);
void			set_sig_code(int err_code);
int				get_sig_code(void);

#endif