/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:02:11 by haroldsorel       #+#    #+#             */
/*   Updated: 2023/12/22 18:20:32 by hsorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

char	*strjoin_free(char *line, char *buffer)
{
	char	*temp;

	temp = line;
	line = ft_strjoin(line, buffer);
	if (line == NULL)
	{
		free(temp);
		free(buffer);
		return (NULL);
	}
	free(temp);
	return (line);
}

char	*line_trimmer(char *line)
{
	int		nl_index;
	char	*res;

	nl_index = find_nl(line);
	if (nl_index == -1)
	{
		nl_index = ft_strlen(line);
		res = malloc(nl_index + 1);
		if (res == NULL)
			return (NULL);
		ft_strlcpy(res, line, nl_index + 1);
	}
	else
	{
		res = malloc(nl_index + 2);
		if (res == NULL)
			return (NULL);
		ft_strlcpy(res, line, nl_index + 2);
	}
	return (res);
}

char	*line_after(char *line)
{
	int		nl_index;
	int		i;
	char	*res;

	nl_index = find_nl(line);
	i = 0;
	if (nl_index == -1)
	{
		res = malloc(1);
		if (res == NULL)
			return (NULL);
	}
	else
	{
		res = malloc(ft_strlen(line) - nl_index);
		if (res == NULL)
			return (NULL);
		while (line[nl_index + 1 + i] != '\0')
		{
			res[i] = line[nl_index + 1 + i];
			i++;
		}
	}
	res[i] = '\0';
	return (res);
}

char	*line_creator(int fd, char *rest)
{
	int			bytes;
	char		*line;
	char		*buffer;

	buffer = malloc(BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (NULL);
	line = free_utils(NULL, rest, 4);
	if (line == NULL || buffer == NULL)
		return (free_utils(buffer, NULL, 2));
	bytes = 1;
	while (bytes != 0)
	{
		if (find_nl(line) != -1)
			break ;
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
			return (free_utils(line, buffer, 3));
		buffer[bytes] = '\0';
		line = strjoin_free(line, buffer);
		if (line == NULL)
			return (NULL);
	}
	free(buffer);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	rest[BUFFER_SIZE + 1];
	char		*line;
	char		*return_line;
	char		*temp;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0
		|| BUFFER_SIZE >= INT_MAX)
		return (NULL);
	line = line_creator(fd, rest);
	if (line == NULL)
	{
		rest[0] = '\0';
		return (NULL);
	}
	if (line[0] == '\0')
		return (free_utils(line, NULL, 2));
	return_line = line_trimmer(line);
	if (return_line == NULL)
		return (free_utils(line, NULL, 2));
	temp = line_after(line);
	if (temp == NULL)
		return (free_utils(line, return_line, 3));
	free_utils(rest, temp, 1);
	free(line);
	return (return_line);
}
