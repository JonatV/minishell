/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:23:45 by haroldsorel       #+#    #+#             */
/*   Updated: 2024/10/21 18:04:28 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

/*
- This wont be necessary, the parser doesnt handle error in commands call
- t_cmd1	close_cmd(t_cmd1 cmd, t_token *token)
- {
- 	if (token->type == pipeline)
- 		cmd.pipe_o = 1;
- 	if (cmd.fd_i == -1 || cmd.fd_o == -1)
- 		cmd.f_redir = 1;
- 	return (cmd);
- }
*/

void	create_cmd(t_cmd1 *full_cmd, char *str, int k)
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
			if (lst->token->type == pipeline)
				count++;
			lst = lst->next;
		}
	}
	return (lst);
}

t_cmd1	parse_cmds(t_lists *lst, int i, int k)
{
	t_cmd1	full_cmd;

	init_struct(&full_cmd);
	while (lst)
	{
		lst = move_lst(lst, i);
		i = 0;
		if (lst->token->type == literal)
			create_cmd(&full_cmd, lst->token->content, k++);
		else if (lst->token->type == simple_redir_right)
			full_cmd.fd_o = get_redir_r(lst->token);
		else if (lst->token->type == simple_redir_left)
			full_cmd.fd_i = get_redir_l(lst->token);
		else if (lst->token->type == double_redir_right)
			full_cmd.fd_o = get_redir_dr(lst->token);
		else if (lst->token->type == double_redir_left)
			full_cmd.fd_i = get_redir_dl(lst->token);
/*
-		else if (lst->token->type == pipeline || lst->token->type == and
-			|| lst->token->type == or)
-			return (close_cmd(full_cmd, lst->token));
*/
		lst = lst->next;
	}
	return (full_cmd);
}

int	set_cmd(t_all_cmd *all_cmd, t_lists *lst, int k)
{
	int	i;

	all_cmd->nbrcmd = count_cmd(lst);
	all_cmd->cmds = malloc(sizeof(t_cmd1) * all_cmd->nbrcmd);
	if (!all_cmd->cmds)
		return (0);
	i = 0;
	while (i < all_cmd->nbrcmd)
	{
		all_cmd->cmds[i] = parse_cmds(lst, i, k);
/*
-		if (all_cmd->cmds[i].f_redir)
-			return (0);
-		if (i > 0)
-			all_cmd->cmds[i].pipe_i = all_cmd->cmds[i - 1].pipe_o;
*/
		i++;
	}
	if (i == 1 && all_cmd->cmds[0].type > 0)
		return (1);
/*
-	else
-	{
-		all_cmd->pids = malloc(sizeof(pid_t) * i);
-		return (1);
-	}
*/
}
