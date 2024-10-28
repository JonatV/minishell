/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd_line_structure.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:44:12 by jveirman          #+#    #+#             */
/*   Updated: 2024/10/28 14:02:51 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool only_isspace_string(char *buffer)
{
	int	i;
	int	j;

	j = 0;
	i = ft_strlen(buffer) - 1;
	while (ft_isspace(buffer[j]))
		j++;
	if (j >= i)
		return (true);
	return (false);
}

static bool	incomplete_cmd_line(char *buffer)
{
	int	i;
	
	i = ft_strlen(buffer) - 1;
	printf("[%s]\n", buffer);
	while (i >= 0 && ft_isspace(buffer[i]))
		i--;
	if (buffer[i] == '|')
		return (true);
	return (false);
}

static void	get_additionnal_cmd_line(t_shell *shell)
{
	char	*tmp;
	char	*additional_buffer;

	additional_buffer = readline("> ");
	if (!additional_buffer)
	{
		free(additional_buffer);
		add_history(shell->buf);
		sigeof_handler(shell);
	}
	tmp = ft_strjoin(shell->buf, additional_buffer);
	free(shell->buf);
	shell->buf = tmp;
	if (additional_buffer[0] == '\0' || only_isspace_string(additional_buffer) || incomplete_cmd_line(additional_buffer) )
		get_additionnal_cmd_line(shell); // recursive here to check again if the line is or isnt finished
	free(additional_buffer);
}

bool	check_cmd_line_structure(t_shell *shell)
{
	char	*buffer;

	buffer = readline(shell->prompt_msg);
	if (!buffer)
	{
		free(buffer);
		sigeof_handler(shell);
	}
	else if (buffer[0] == '\0' || only_isspace_string(buffer))
	{
		free(buffer);
		return (false);
	}
	else if (incomplete_cmd_line(buffer))
	{
		shell->buf = ft_strdup(buffer);
		free(buffer);
		get_additionnal_cmd_line(shell);
		return (true);
	}
	shell->buf = buffer;
	return (true);
}
