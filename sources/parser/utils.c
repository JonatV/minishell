/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 11:09:36 by mcygan            #+#    #+#             */
/*   Updated: 2024/06/11 17:22:59 by mcygan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize > 0)
	{
		while (src[i] != 0 && i < (dstsize - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	while (src[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *str, int only)
{
	if (!str)
		return (0);
	while (*str != '\0' && (char)only != *str)
		str++;
	if (*str == (char)only)
		return ((char *)str);
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, int n)
{
	while (*s1 && *s2 && *s1 == *s2 && n-- > 0)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

int is_whitespace(const char c)
{
	return ((c > 8 && c < 14) || c == 32);
}

int	skip_whitespace(char *str, int *idx)
{
	int	i;

	i = -1;
	while (i++, is_whitespace(str[*idx]))
		(*idx)++;
	return (i);
}

int	is_quote(const char c)
{
	return (c == 39 || c == 34);
}

int	skip_quote(char *str, int *idx)
{
	char	a;
	int		i;

	i = 0;
	if (is_quote(str[*idx]))
	{
		a = str[(*idx)++];
		while (i++, str[*idx] && str[*idx] != a)
			(*idx)++;
		if (!str[*idx])
			return (-1);
	}
	return (i);
}
