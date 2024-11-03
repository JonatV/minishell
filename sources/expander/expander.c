/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 21:11:29 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/03 23:05:03 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	free_all_segments(char **segments)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (segments[i])
			free(segments[i]);
		i++;
	}
	return (false);
}

static bool	assemble_all_segments(char **segments, char **str)
{
	char	*result;
	int		seg0_len;
	int		seg1_len;
	int		seg2_len;

	seg0_len = ft_strlen(segments[0]);
	seg1_len = ft_strlen(segments[1]);
	seg2_len = ft_strlen(segments[2]);
	result = malloc(sizeof(char) * (seg0_len + seg1_len + seg2_len + 1));
	if (!result)
		return (free_all_segments(segments));
	ft_strlcpy(result, segments[0], seg0_len + 1);
	ft_strlcat(result, segments[1], ft_strlen(result) + seg1_len + 1);
	ft_strlcat(result, segments[2], ft_strlen(result) + seg2_len + 1);
	free_all_segments(segments);
	free(*str);
	*str = result;
	return (true);
}

static bool	replace_dollar(char **array, char **str, int *i, int *start_end)
{
	int		pos;
	int		var_len;
	char	*var_name;
	char	*segments[3];

	var_name = ft_substr(*str + start_end[0] + 1, 0, start_end[1] - 1);
	if (!var_name)
		return (false);
	var_len = ft_strlen(var_name) + 1;
	pos = ft_arrayfind(array, var_name);
	segments[0] = ft_substr(*str, 0, start_end[0]);
	if (pos == -1)
		segments[1] = ft_strdup("");
	else
		segments[1] = ft_substr(array[pos], var_len, ft_strlen(array[pos]));
	segments[2] = ft_substr(*str, start_end[0] + start_end[1] , ft_strlen(*str));
	free(var_name);
	if (!segments[0] || !segments[1] || !segments[2])
		return (free_all_segments(segments));
	*i = ft_strlen(segments[0]) + ft_strlen(segments[1]);
	return (assemble_all_segments(segments, str));
}

static bool	replace_double_dollar(char **str, int *i)
{
	char	*segments[3];

	segments[0] = ft_substr(*str, 0, *i);
	segments[1] = ft_itoa(getpid());
	segments[2] = ft_substr(*str, *i + 2, ft_strlen(*str));
	if (!segments[0] || !segments[1] || !segments[2])
		return (free_all_segments(segments));
	*i = ft_strlen(segments[0]) + ft_strlen(segments[1]);
	return (assemble_all_segments(segments, str));
}


/*
* INFO:
*		- first check if there's a dollar sign after the first one -> $$
*		- then check if the dollar sign is followed by a space
*		- finally check if the dollar sign is followed by a variable name
*			if all the conditions are met, we replace the variable name with its value
*	@return : true if the variable was replaced, false otherwise
*/
static bool	replace_var_manager(int *i, char **content, char **env)
{
	int start_end[2];
	int	j;

	if ((*content)[*i + 1] && (*content)[*i + 1] == '$')
		return (replace_double_dollar(content, i));
	// * Then check if the dollar sign is followed by a space
	if ((*content)[*i + 1] == '\0' || ft_isspace((*content)[*i + 1]))
		return (*i += 1, true);
	j = 0;
	start_end[0] = *i;
	// * finally check if the dollar sign is followed by a variable name
	while ((*content)[*i + j])
	{
		if ((*content)[*i + j + 1] == '\0' || (*content)[*i + j + 1] == '$' || ft_isspace((*content)[*i + j]))
		{
			if (!ft_isspace((*content)[*i + j]))
				j++;
			start_end[1] = j;
			return (replace_dollar(env, content, i, start_end));
		}
		j++;
	}
	return (true);
}

/*
* INFO:
*	This function processes an array, similar to the environment array,
*	and a string containing one or more variable names ($var_name). 
*	It replaces each variable name in the string 
*	with its corresponding value from the array."
*	@return : nothing, it changes the str directly, that's why it's send with a double pointer.
*/
bool	expander(char **env, char **content)
{
	int	i;

	i = 0;
	while ((*content)[i])
	{
		if ((*content)[i] == '$')
		{
			if (!replace_var_manager(&i, content, env))
				return (printf("Error while replacing the variable\n"), false);
			else
				continue ;
		}
		i++;
	}
	return (true);
}

// int	main(void)
// {
// 	int		i;
// 	char	**array;
// 	char	*content;
// 	char	*str;

// 	array = malloc((4 + 1) * sizeof(char *));
// 	array[0] = ft_strdup("ST=First Element");
// 	array[1] = ft_strdup("USER=JVEIRMAN");
// 	array[2] = ft_strdup("END=XOXO");
// 	array[3] = ft_strdup("TUTUTUTU=Je suis un magicien");
// 	array[4] = NULL;
// 	// content = "THX bye $END mais la dinguerie_$TUTUTUTU$ST";
// 	content = "Hey There $$ $$$USER";
// 	str = ft_strdup(content);
// 	if (expander(array, &str) == 0)
// 		printf("The expander failed.\n");
// 	else
// 		printf("END RESULT -> \e[1:33m[%s]\e[0m\n", str);
// 	i = 0;
// 	while (array[i])
// 		free(array[i++]);
// 	free(array);
// 	free(str);
// 	return (0);
// }
