/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:58:56 by jveirman          #+#    #+#             */
/*   Updated: 2024/06/06 12:00:01 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
