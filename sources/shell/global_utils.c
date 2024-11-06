/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 02:41:48 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/06 02:49:55 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	mini_printf(char *first_part, char *dynamic_info, char *last_part, int fd)
{
	ft_putstr_fd(first_part, fd);
	ft_putstr_fd(dynamic_info, fd);
	ft_putstr_fd(last_part, fd);
}
