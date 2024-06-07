/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:24:42 by jveirman          #+#    #+#             */
/*   Updated: 2024/06/07 15:32:22 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/built_in.h"

void	builtin_pwd(t_shell *shell)
{
	char	*pwd;
	char	*s;

	s = "PWD";
	pwd = shell->env[ft_arrayfind(shell->env, s)];
	ft_putendl_fd(pwd + ft_strlen(s), 1);
}
