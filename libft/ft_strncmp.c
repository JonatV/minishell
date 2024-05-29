/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:03:49 by jveirman          #+#    #+#             */
/*   Updated: 2023/10/16 14:28:02 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t count)
{
	while ((count > 0) && (*str1 == *str2) && (*str1 != '\0'))
	{
		str1++;
		str2++;
		count--;
	}
	if (count == 0)
		return (0);
	return ((unsigned char)*str1 - (unsigned char)*str2);
}
