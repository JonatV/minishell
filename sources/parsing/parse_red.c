/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_red.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:19:54 by haroldsorel       #+#    #+#             */
/*   Updated: 2024/10/22 16:59:31 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

int	get_redir_l(t_token *token)
{
	int	fd;

	fd = open(token->content, O_RDONLY);
	return (fd);
}


/*
TODO change this function to obtain all the delimiter and save it inside **here_doc_delimiter
*/
int	get_redir_dl(t_token *token)
{
	(void)token; //dev
	return (-19); //dev
}

int	get_redir_r(t_token *token)
{
	int	fd;

	fd = open(token->content, O_CREAT | O_RDWR | O_TRUNC, 0666);
	return (fd);
}

int	get_redir_dr(t_token *token)
{
	int	fd;

	fd = open(token->content, O_CREAT | O_RDWR | O_APPEND, 0666);
	return (fd);
}
