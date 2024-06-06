/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 11:53:12 by jveirman          #+#    #+#             */
/*   Updated: 2024/06/06 11:54:53 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/built_in.h"

int	check_var_name(char *str)
{
	if (ft_isdigit(str[0]))
	{
		ft_putendl_fd("Not a valid indentifier", 1);
		return (1);
	}
	return (0);
}

char	*ft_extract(char *str, char target)
{
	int	max;

	max = 0;
	while (str[max])
	{
		if (str[max] == target)
			break ;
		max++;
	}
	return (ft_substr(str, 0, (size_t)max));
}

static void	print_process(char *str)
{
	int	i;

	ft_putstr("declare -x ");
	i = 0;
	while (str[i])
	{
		ft_putchar_fd(str[i], 1);
		if (str[i++] == '=')
			break ;
	}
	ft_putchar_fd('"', 1);
	if (str[i])
		ft_putstr(str + i);
	ft_putchar_fd('"', 1);
	ft_putchar_fd('\n', 1);
}

void	print_export(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (ft_strchr(array[i], '=') == 0)
		{
			ft_putstr("declare -x ");
			ft_putendl_fd(array[i], 1);
		}
		else
			print_process(array[i]);
		i++;
	}
}
