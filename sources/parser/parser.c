/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 09:47:09 by mcygan            #+#    #+#             */
/*   Updated: 2024/06/12 13:30:09 by mcygan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

int	validate_cmd_order(t_token *tokens)
{
	int	i;

	i = 0;
	if (tokens[i].type == PIPE)
		return (1);
	while (tokens[++i].type != END)
	{
		if (tokens[i].type == PIPE && tokens[i - 1].type == PIPE)
			return (1);
	}
	if (tokens[i - 1].type == PIPE)
		return (1);
	return (0);
}

char	*strip_redir(char *path)
{
	int	i;

	i = 0;
	if (path[i] == '>')
	{
		i++;
		if (path[i] == '>')
			i++;
	}
	else if (path[i] == '<')
		i++;
	else
		return (NULL);
	skip_whitespace(path, &i);
	return (path + i);
}

int open_check(char *file_path, int option)
{
    int fd;

    if (0 == option)
        fd = open(file_path, O_RDONLY, 0777);
    else if (1 == option)
        fd = open(file_path, O_CREAT | O_WRONLY | O_TRUNC, \
        S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
    else
        fd = open(file_path, O_CREAT | O_WRONLY | O_APPEND, \
        S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
    return (fd);
}

int	word_count(t_token *tokens)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (tokens[i].type != PIPE && tokens[i].type != END)
	{
		if (tokens[i++].type == WORD)
			count++;
	}
	return (count);
}

int	expr_count(t_token *tokens)
{
	int	count;
	int	i;

	count = 1;
	i = 0;
	while (tokens[i].type != END)
	{
		if (tokens[i++].type == PIPE)
			count++;
	}
	return (count);
}

void	set_fd(t_cmd *cmd_info, t_token token)
{
	if (token.data[0] == '>')
	{
		if (token.data[1] == '>')
			cmd_info->fd_out = open_check(strip_redir(token.data), 2);
		else
			cmd_info->fd_out = open_check(strip_redir(token.data), 1);
	}
	else if (token.data[0] == '<')
		cmd_info->fd_in = open_check(strip_redir(token.data), 0);
	else
	{
		cmd_info->fd_out = -1;
		cmd_info->fd_out = -1;
	}
}

t_cmd	*fill_cmd_info(t_token *tokens)
{
	t_cmd	*cmd_info;
	int		ec;
	int		i;
	int		j;
	int		k;

	if (validate_cmd_order(tokens))
		return (NULL);
	ec = expr_count(tokens);
	cmd_info = malloc(sizeof(t_cmd) * (ec + 1));
	if (!cmd_info)
		return (NULL);
	i = -1;
	j = 0;
	while (++i < ec)
	{
		k = 0;
		cmd_info[i].data = malloc(sizeof(char *) * (word_count(tokens + j) + 1));
		if (!cmd_info[i].data)
			return (NULL);
		k = 0;
		while (tokens[j].type != PIPE && tokens[j].type != END)
		{
			if (tokens[j].type == STREAM)
				set_fd(&cmd_info[i], tokens[j]);
			else if (tokens[j].type == WORD)
				cmd_info[i].data[k++] = tokens[j].data;
			j++;
		}
		if (tokens[j].type == PIPE)
			j++;
	}
	cmd_info[i].data = NULL;
	return (cmd_info);
}
