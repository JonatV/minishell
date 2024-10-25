/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:23:45 by haroldsorel       #+#    #+#             */
/*   Updated: 2024/10/25 14:09:01 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	create_cmd(t_cmd *full_cmd, char *str, int k)
{
	int			i;
	int			j;
	char		**new;

	if (k > 0)
		return ;
	new = ft_split(str, -1);
	i = 0;
	j = 0;
	while (new[i] != NULL)
	{
		if (ft_strlen(new[i]) == 1)
		{
			if (new[i][0] == -2)
			{
				free(new[i]);
				new[i] = ft_strdup("");
			}
		}
		i++;
	}
	full_cmd->type = get_type(new);
	full_cmd->cmd = new;
}

t_lists	*move_lst(t_lists *lst, int i)
{
	int	count;

	if (i > 0)
	{
		count = 0;
		while (count < i)
		{
			if (lst->token->type == TOKEN_PIPE)
				count++;
			lst = lst->next;
		}
	}
	return (lst);
}

/*
	TODO
	here i need to know what's the cmd is. Is cmd is data? YES (not yet parsed)
*/
t_cmd	parse_cmds(t_lists *lst, int i, int k)
{
	t_cmd	full_cmd;

	init_struct(&full_cmd);
	while (lst)
	{
		lst = move_lst(lst, i);
		i = 0;
		if (lst->token->type == TOKEN_WORD)
			create_cmd(&full_cmd, lst->token->value, k++);
		else if (lst->token->type == TOKEN_REDIR_OUT)
			full_cmd.fd_in = get_redir_r(lst->token);
		else if (lst->token->type == TOKEN_REDIR_IN)
			full_cmd.fd_in = get_redir_l(lst->token);
		else if (lst->token->type == TOKEN_REDIR_APPEND)
			full_cmd.fd_out = get_redir_dr(lst->token);
		else if (lst->token->type == TOKEN_REDIR_HEREDOC)
			full_cmd.fd_in = get_redir_dl(lst->token);
		lst = lst->next;
	}
	return (full_cmd);
}

int	set_cmd(t_shell *shell, t_lists *lst, int k)
{
	int	i;

	shell->cmd_number = count_cmd(lst);
	shell->cmd_array = malloc(sizeof(t_cmd) * shell->cmd_number);
	if (!shell->cmd_array)
		return (0);
	i = 0;
	while (i < shell->cmd_number)
	{
		shell->cmd_array[i] = parse_cmds(lst, i, k);
		i++;
	}
	if (i == 1 && shell->cmd_array[0].type > 0)
		return (1);
	return (1); //todo check if return 1 ok
}
