/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd_line_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:23:34 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/12 16:24:44 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool only_isspace_string(char *buffer)
{
	int	i;
	int	j;

	j = 0;
	i = ft_strlen(buffer);
	while (ft_isspace(buffer[j]))
		j++;
	if (j >= i)
		return (true);
	return (false);
}

static bool	is_quote_incomplete(char *buffer)
{
	int		i;
	bool	in_quote;
	int		quote_type;

	in_quote = false;
	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == 39 || buffer[i] == 34)
		{
			if (!in_quote)
			{
				in_quote = true;
				quote_type = buffer[i];
			}
			else if (quote_type == buffer[i])
				in_quote = false;
		}
		i++;
	}
	return (in_quote);
}

bool	is_incomplete_cmd_line(char *buffer)
{
	int	i;
	
	if (is_quote_incomplete(buffer))
		return (true);
	i = ft_strlen(buffer) - 1;
	while (i >= 0 && ft_isspace(buffer[i]))
		i--;
	if (buffer[i] == '|')
		return (true);
	return (false);
	// return (buffer[i] == '|'); //todo check if norminette ok
}

bool restore_stdin(int stdin_backup, t_shell *shell)
{
	if (dup2(stdin_backup, STDIN_FILENO) == -1)
		panic("dup2 failed", shell);
	if (close(stdin_backup) == -1)
		panic("close failed", shell);
	add_history(shell->buf);
	return (true);
}
