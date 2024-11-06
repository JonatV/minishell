/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:48:36 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/06 02:56:42 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_word(char *str)
{
	int	i;
	int word_count;

	if (!str)
		return (0);
	word_count = 1;
	i = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]) && str[i + 1])
			word_count++;
		i++;
	}
	return (word_count);
}

static char	*get_path_name(t_shell *shell, char **data)
{
	int		i;
	char	*path_name;

	if (!data[CMD_ARG])
	{
		i = ft_arrayfind(shell->env, "HOME");
		if (i == -1)
			panic("Env var not found", shell);
		path_name = ft_strchr(shell->env[i], '=');
		return (path_name + 1);
	}
	return (data[CMD_ARG]);
}

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

bool	builtin_chdir(t_shell *shell, char **data)
{
	char	pwd[1024]; //wip: check the limits
	char	oldpwd[1024]; //wip: check the limits

	if (!check_data_validity(data, BUILTIN_CD))
	{
		ft_putstr_fd("Minishell: cd: no options allowed\n", STDERR_FILENO);
		return (false);
	}
	if (count_word(data[CMD_ARG]) > 1)
	{
		ft_putstr_fd("Minishell: cd: too many arguments\n", STDERR_FILENO);
		return (false);
	}
	if (getcwd(oldpwd, sizeof(oldpwd)) == NULL)
		perror("getcwd()"); // wip: change error management
	if (0 != chdir(get_path_name(shell, data)))
	{
		mini_printf("Minishell: cd: ", data[CMD_ARG], ": No such file or directory\n", STDERR_FILENO);
		return (false); //wip: error management
	}
	if (getcwd(pwd, sizeof(pwd)) == NULL)
		perror("getcwd()"); // wip: change error management
	update_pwd(shell, pwd, oldpwd);
	return (true);
}
