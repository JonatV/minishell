/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 11:53:12 by jveirman          #+#    #+#             */
/*   Updated: 2024/10/30 01:25:44 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_var_name(char *str)
{
	if (ft_isdigit(str[0]))
	{
		ft_putendl_fd("Not a valid indentifier", 1);
		return (1);
	}
	return (0);
}

char	*ft_extract(char *str, char target, int extract_after)
{
	int	target_pos;

	target_pos = 0;
	while (str[target_pos] != target)
		target_pos++;
	if (extract_after)
		return (ft_substr(str, ++target_pos, ft_strlen(str)));
	return (ft_substr(str, 0, (size_t)target_pos));
}

static void	print_process(char *str)
{
	int	i;

	// ft_putstr_fd("\n\e[1;31mhere\e[0m\n", STDIN_FILENO);
	// ft_putstr_fd("\n\e[1;31mhere user\e[0m\n", STDIN_FILENO);
	ft_putstr_fd("declare -x ", STDIN_FILENO); //wip stdin check
	i = 0;
	while (str[i])
	{
		ft_putchar_fd(str[i], STDIN_FILENO);
		if (str[i++] == '=')
			break ;
	}
	ft_putchar_fd('"', STDIN_FILENO);
	if (str[i])
		ft_putstr_fd(str + i, STDIN_FILENO);
	ft_putchar_fd('"', STDIN_FILENO);
	ft_putchar_fd('\n', STDIN_FILENO);
}

void	print_export(char **array)
{
	int	i;
	i = 0;
	while (array[i])
	{
		ft_putstr_fd(array[i], STDIN_FILENO);
		ft_putstr_fd(" ", STDIN_FILENO);
		i++;
	}
	i = 0;
	while (array[i])
	{
		if (ft_strchr(array[i], '=') == 0)
		{
			ft_putstr_fd("declare -x ", STDIN_FILENO);
			ft_putendl_fd(array[i], STDIN_FILENO);
		}
		else
			print_process(array[i]);
		i++;
	}
}
