/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:53:31 by jveirman          #+#    #+#             */
/*   Updated: 2024/02/27 14:58:41 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int only)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	while (i > 0 && (char)only != str[i])
		i--;
	if (str[i] == (char)only)
		return ((char *)&str[i]);
	return (0);
}
