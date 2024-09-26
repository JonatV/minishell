/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:35:16 by jveirman          #+#    #+#             */
/*   Updated: 2024/09/26 14:03:20 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "shell.h"
/*
#####################################################################
#							DEFINE									#
#####################################################################
*/
# define B_SIZE 8

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

/*----------------  chdir.c  ---------------*/
int		builtin_chdir(t_shell *shell, char *destination);

/*----------------  echo.c  ---------------*/
void	builtin_echo(char **data);

/*----------------  env.c  ---------------*/
void	builtin_env(t_shell *shell);

/*----------------  exit.c  ---------------*/
void	builtin_exit(t_shell *shell);

/*----------------  export.c  ---------------*/
void	update_export(t_shell *shell, char *str);// dev
void	builtin_export(t_shell *shell, int i);

/*----------------  export_utils.c  ---------------*/
int		check_var_name(char *str);
char	*ft_extract(char *str, char target, int extract_after);
void	print_export(char **array);

/*----------------  pwd.c  ---------------*/
void	builtin_pwd(t_shell *shell);

/*----------------  unset.c  ---------------*/
void	builtin_unset(t_shell *shell, char *to_remove);

/*----------------  utils.c  ---------------*/
int		is_builtin(char *to_find);
void	select_builtin(t_shell *shell, int i, int built_in_index);

#endif
