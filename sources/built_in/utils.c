/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:29:56 by jveirman          #+#    #+#             */
/*   Updated: 2024/06/03 14:08:46 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/built_in.h"

int	is_builtin(char *to_find)
{
	int					i;
	const char *const	built_in[8] = {"echo", "env", "export", "unset", \
	"exit", "cd", "pwd", NULL};

	i = -1;
	ft_arrayfind((char **)built_in, to_find);
	return (i);
}
