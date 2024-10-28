/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 13:44:21 by haroldsorel       #+#    #+#             */
/*   Updated: 2023/12/22 17:33:09 by hsorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef MAX_BUFFER_SIZE
#  define MAX_BUFFER_SIZE 2147483646
# endif

# if BUFFER_SIZE < 0
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 0
# endif

# if BUFFER_SIZE >= MAX_BUFFER_SIZE
#  undef BUFFER_SIZE
#  define BUFFER_SIZE MAX_BUFFER_SIZE
# endif
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <limits.h>

char	*ft_strjoin(const char *s1, const char *s2);
char	*strjoin_free(char *s1, char *s2);
int		find_nl(char *s);
char	*free_utils(char *s1, char *s2, int n);
char	*get_next_line(int fd);
size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dest, const char *source, size_t n);

#endif
