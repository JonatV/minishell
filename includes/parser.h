/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:32:16 by mcygan            #+#    #+#             */
/*   Updated: 2024/06/11 17:43:04 by mcygan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

enum
{
	VOID	= 0,
	CMD		= 1,
	STREAM	= 2,
	PIPE	= 3,
	END		= 4
};

typedef struct s_token
{
	int		type;
	char	*data;
}	t_token;

// core
int		token_count(char *input);
t_token	*tokens_init(char *input);
char	*get_token_data(char *str, int *idx);
void	set_token_type(t_token *tokens, int idx);

// utils
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int		ft_strncmp(const char *s1, const char *s2, int n);
int 	is_whitespace(const char c);
int		skip_whitespace(char *str, int *idx);
int		is_quote(const char c);
int		skip_quote(char *str, int *idx);

#endif