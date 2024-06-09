/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 21:11:29 by jveirman          #+#    #+#             */
/*   Updated: 2024/06/09 21:31:21 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"

static int	free_all_segments(char **segments)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (segments[i])
			free(segments[i]);
		i++;
	}
	return (0);
}

static int	assemble_all_segments(char **segments, char **str)
{
	char	*result;

	result = malloc(sizeof(char) * (ft_strlen(segments[0]) + ft_strlen(segments[1]) + ft_strlen(segments[2]) + 1));
	if (!result)
		return (free_all_segments(segments));
	ft_strlcpy(result, segments[0], ft_strlen(segments[0]) + 1);
	ft_strlcat(result, segments[1], ft_strlen(result) + ft_strlen(segments[1]) + 1);
	ft_strlcat(result, segments[2], ft_strlen(result) + ft_strlen(segments[2]) + 1);
	free_all_segments(segments);
	free(*str);
	*str = result;
	return (1);
}

static int	replace_dollar(char **array, int start, int end, char **str)
{
	int		pos;
	char	*var_name;
	char	*segments[3];

	var_name = ft_substr(*str + start + 1, 0, end - 1);
	if (!var_name)
		return (0); // wip
	pos = ft_arrayfind(array, var_name);
	if (pos == -1)
	{
		free(var_name);
		return (0); // wip
	}
	segments[0] = ft_substr(*str, 0, start);
	segments[1] = ft_substr(array[pos], ft_strlen(var_name) + 1, ft_strlen(array[pos]));
	segments[2] = ft_substr(*str, start + end, ft_strlen(*str));
	free(var_name);
	if (!segments[0] || !segments[1] || !segments[2])
		return (free_all_segments(segments)); // wip
	return (assemble_all_segments(segments, str));
}

static void	replace_var_manager(int *i, char **str, char **array)
{
	int	start;
	int	end;
	int	j;

	start = *i;
	j = 0;
	while ((*str)[*i + j])
	{
		if ((*str)[*i + j + 1] == '\0' || (*str)[*i + j + 1] == '$' || ft_isspace((*str)[*i + j]))
		{
			if (!ft_isspace((*str)[*i + j]))
				j++;
			end = j;
			if (replace_dollar(array, start, end, str) == 0)
				exit(1); // wip: error management
			*i = -1;
			break ;
		}
		j++;
	}
}

void	expander(t_shell *shell, char **str)
{
	int	i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '$')
			replace_var_manager(&i, str, shell->env);
		i++;
	}
}
/*

void	expander(char **array, char **str);

int	main(void)
{
	int		i;
	char	**array;
	char	*content;
	char	*str;

	array = malloc((4 + 1) * sizeof(char *));
	array[0] = ft_strdup("ST=First Element");
	array[1] = ft_strdup("USER=JVEIRMAN");
	array[2] = ft_strdup("END=XOXO");
	array[3] = ft_strdup("TUTUTUTU=Je suis un magicien");
	array[4] = NULL;
	content = "THX $USER bye $END mais la dinguerie_$TUTUTUTU$ST";
	str = ft_strdup(content);
	expander(array, &str);
	while (array[i])
		free(array[i++]);
	free(array);
	free(str);
	return (0);
}
*/
