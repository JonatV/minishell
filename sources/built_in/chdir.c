/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:48:36 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/12 02:04:27 by jveirman         ###   ########.fr       */
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
		{
			error_msg("cd: HOME not set");
			return (NULL);
		}
		path_name = ft_strchr(shell->env[i], '=');
		return (path_name + 1);
	}
	return (data[CMD_ARG]);
}

void	pwd_management(t_shell *shell, char *pwd)
{
	char	*temp;
	int		pwd_pos;

	pwd_pos = ft_arrayfind(shell->env, "PWD");
	temp = ft_strjoin("PWD=", pwd);
	if (!temp)
		panic(ERR_MALLOC, shell);
	if (pwd_pos != -1)
	{
		free(shell->env[pwd_pos]);
		shell->env[pwd_pos] = temp;
	}
	else
	{
		if (!ft_arraypush(&shell->env, temp))
		{
			free(temp);
			panic(ERR_MALLOC, shell);
		}
		free(temp);
	}
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
	{
		if (!ft_arraypush(&shell->env, temp))
			panic(ERR_MALLOC, shell);
		free(temp);
	}
}

static void	update_pwd(t_shell *shell, char *pwd, char *oldpwd)
{
	pwd_management(shell, pwd);
	oldpwd_management(shell, oldpwd);
}

int	builtin_chdir(t_shell *shell, char **data)
{
	char	pwd[1024];
	char	oldpwd[1024];
	char	*path_name;

	path_name = NULL;
	if (!check_data_validity(data, BUILTIN_CD))
	{
		error_msg("cd: no options allowed");
		return (2);
	}
	if (count_word(data[CMD_ARG]) > 1)
	{
		error_msg("cd: too many arguments");
		return (1);
	}
	if (getcwd(oldpwd, sizeof(oldpwd)) == NULL)
		panic("getcwd failed", shell);
	path_name = get_path_name(shell, data);
	if (!path_name)
		return (1);
	if (0 != chdir(path_name))
	{
		mini_printf("minishell: cd: ", data[CMD_ARG], ": No such file or directory\n", STDERR_FILENO);
		return (1);
	}
	if (getcwd(pwd, sizeof(pwd)) == NULL)
		panic("getcwd failed", shell);
	update_pwd(shell, pwd, oldpwd);
	return (0);
}
