/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:48:36 by jveirman          #+#    #+#             */
/*   Updated: 2024/06/07 15:31:51 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/built_in.h"

static void	pwd_management(t_shell *shell, char *pwd)
{
	char	*temp;
	int		pwd_pos;

	pwd_pos = ft_arrayfind(shell->env, "PWD");
	temp = ft_strjoin("PWD=", pwd);
	if (!temp)
		panic("Malloc for pwd", shell);
	if (pwd_pos != -1) // info: if the element exist then enter the changement process otherwise jump the process
	{
		free(shell->env[pwd_pos]);
		shell->env[pwd_pos] = temp;
	}
	else
		free(temp);
}

static void	oldpwd_management(t_shell *shell, char *oldpwd)
{
	char	*temp;
	int		oldpwd_pos;

	oldpwd_pos = ft_arrayfind(shell->env, "OLDPWD");
	temp = ft_strjoin("OLDPWD=", oldpwd);
	if (!temp)
		panic("Malloc for oldpwd", shell);
	if (oldpwd_pos != -1)
	{
		free(shell->env[oldpwd_pos]);
		shell->env[oldpwd_pos] = temp;
	}
	else
		free(temp);
}

static void	update_pwd(t_shell *shell, char *pwd, char *oldpwd)
{
	pwd_management(shell, pwd);
	oldpwd_management(shell, oldpwd);
}

int	builtin_chdir(t_shell *shell, char *destination)
{
	char	pwd[1024]; //wip: check the limits
	char	oldpwd[1024]; //wip: check the limits

	if (getcwd(oldpwd, sizeof(oldpwd)) == NULL)
		perror("getcwd()"); // wip: change error management
	if (0 != chdir(destination))
		return (1); //wip: error management
	if (getcwd(pwd, sizeof(pwd)) == NULL)
		perror("getcwd()"); // wip: change error management
	update_pwd(shell, pwd, oldpwd);
	return (0);
}
