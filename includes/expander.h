/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 21:16:19 by jveirman          #+#    #+#             */
/*   Updated: 2024/06/09 21:19:51 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef EXPANDER_H
# define EXPANDER_H

# include "shell.h"

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
// void	expander(char **array, char **str); //debug: use with the main for dev
void	expander(t_shell *shell, char **str);

#endif
