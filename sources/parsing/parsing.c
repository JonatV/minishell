/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:21:39 by haroldsorel       #+#    #+#             */
/*   Updated: 2024/11/07 01:04:20 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool concatenate_tokens(t_token *parent, t_token *tmp)
{
	char	*content;
	char	*str_temp;
	t_token	*next_token;

	content = ft_strdup(parent->content);
	if (!content)
		return (false);
	while (tmp->next && (tmp->next->type == TOKEN_WORD || tmp->next->type == TOKEN_DOUBLE_QUOTE || tmp->next->type == TOKEN_SINGLE_QUOTE))
	{
		str_temp = ft_strjoin(content, tmp->next->content);
		free(content);
		if (!str_temp)
			return (false);
		content = str_temp;
		next_token = tmp->next->next;
		free(tmp->next->content);
		free(tmp->next);
		tmp->next = next_token;
	}
	free(parent->content);
	parent->content = content;
	return (true);
}

static bool	regroup_litteral_tokens(t_shell *shell)
{
	t_token	*parent;

	parent = shell->tokens_list;
	while (parent)
	{
		if (parent->type == TOKEN_WORD || parent->type == TOKEN_DOUBLE_QUOTE || parent->type == TOKEN_SINGLE_QUOTE)
		{
			if (!concatenate_tokens(parent, parent))
				return (false);
		}
		parent = parent->next;
	}
	return (true);
}

static bool handling_expander(t_shell *shell)
{
	t_token	*tmp;

	tmp = shell->tokens_list;
	while (tmp)
	{
		if (tmp->type == TOKEN_WORD || tmp->type == TOKEN_DOUBLE_QUOTE)
		{
			if (!expander(shell->env, &tmp->content))
			{
				if (shell->buf)
					free(shell->buf);
				return (false);
			}
		}
		tmp = tmp->next;
	}
	return (true);
}

bool	parsing(t_shell *shell)
{
	if (!handling_expander(shell))
		return (false);
	if (!regroup_litteral_tokens(shell))
	{
		printf("Error while regrouping litteral tokens\n");
		return (false);
	}
	if (!cmd_array_builder(shell))
	{
		if (shell->buf)
			free(shell->buf);//todo more free (free cmd array) i was checking to not have cmd number wrong when pipes are miss counted
		printf("Error while building cmd array\n");// todo refactor error msg
		return (false);
	}
	return (true);
}
