/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dev.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:23:39 by jveirman          #+#    #+#             */
/*   Updated: 2024/10/22 14:28:21 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEV_H
# define DEV_H

# include "shell.h"
/*
#####################################################################
#							DEFINE									#
#####################################################################
*/
# define DEV_COMMAND_START "\033[1;33m/*----------------				START COMMAND				---------------*/\033[0m"
# define DEV_COMMAND_END "\033[1;33m/*----------------				END COMMAND				---------------*/\033[0m"

/*
#####################################################################
#							STRUCTURE								#
#####################################################################
*/
typedef struct s_shell	t_shell;
typedef struct s_cmd	t_cmd;
typedef struct s_all_cmd t_all_cmd;

/*
#####################################################################
#						FUNCTIONS PROTOTYPE							#
#####################################################################
*/

/*----------------				DEV_TOOLS			---------------*/
void	init_all_cmd(t_shell *shell);
void	print_all_cmd(t_shell *shell);

#endif
