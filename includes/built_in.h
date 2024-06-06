/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:35:16 by jveirman          #+#    #+#             */
/*   Updated: 2024/06/06 12:00:41 by jveirman         ###   ########.fr       */
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

/*----------------				ENV					---------------*/

/*----------------				CHDIR					---------------*/
int		builtin_chdir(t_shell *shell, char *destination);

/*----------------				PWD					---------------*/
void	builtin_pwd(t_shell *shell);

/*----------------				UNSET				---------------*/
void	builtin_unset(t_shell *shell, char *to_remove);

/*----------------				EXPORT				---------------*/
void	builtin_export(t_shell *shell);
int		check_var_name(char *str);
char	*ft_extract(char *str, char target);
void	print_export(char **array);

/*----------------				UTILS				---------------*/
int		is_builtin(char *to_find);

#endif
