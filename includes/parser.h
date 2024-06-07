/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:32:16 by mcygan            #+#    #+#             */
/*   Updated: 2024/06/07 10:48:20 by mcygan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdlib.h>
# include <stdio.h>

enum
{
	VOID	= 0,
	CMD		= 1,
	ARG		= 2,
	FLAG	= 3,
	PIPE	= 4,
	RD_IN	= 5,
	RD_OUT	= 6,
	RD_APP	= 7,
	RD_HER	= 8,
	UFILE	= 9,
	END		= 10
};

typedef struct s_token
{
	int		type;
	char	*data;
}	t_token;

t_token	*tokens_init(char *input);

#endif