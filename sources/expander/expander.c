/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 21:11:29 by jveirman          #+#    #+#             */
/*   Updated: 2024/10/21 17:57:31 by jveirman         ###   ########.fr       */
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
	int		seg0_l;
	int		seg1_l;
	int		seg2_l;

	seg0_l = ft_strlen(segments[0]);
	seg1_l = ft_strlen(segments[1]);
	seg2_l = ft_strlen(segments[2]);
	result = malloc(sizeof(char) * (seg0_l + seg1_l + seg2_l + 1));
	if (!result)
		return (free_all_segments(segments));
	ft_strlcpy(result, segments[0], seg0_l + 1);
	ft_strlcat(result, segments[1], ft_strlen(result) + seg1_l + 1);
	ft_strlcat(result, segments[2], ft_strlen(result) + seg2_l + 1);
	free_all_segments(segments);
	free(*str);
	*str = result;
	return (1);
}

static int	replace_dollar(char **array, int start, int end, char **str)
{
	int		pos;
	int		var_len;
	char	*var_name;
	char	*segments[3];

	var_name = ft_substr(*str + start + 1, 0, end - 1);
	if (!var_name)
		return (0);
	var_len = ft_strlen(var_name) + 1;
	pos = ft_arrayfind(array, var_name);
	if (pos == -1)
	{
		free(var_name);
		return (0);
	}
	segments[0] = ft_substr(*str, 0, start);
	segments[1] = ft_substr(array[pos], var_len, ft_strlen(array[pos]));
	segments[2] = ft_substr(*str, start + end, ft_strlen(*str));
	free(var_name);
	if (!segments[0] || !segments[1] || !segments[2])
		return (free_all_segments(segments));
	return (assemble_all_segments(segments, str));
}

static int	replace_var_manager(int *i, char **str, char **array)
{
	int	start;
	int	end;
	int	j;

	start = *i;
	j = 0;
	while ((*str)[*i + j])
	{
		if ((*str)[*i + j + 1] == '\0'
		|| (*str)[*i + j + 1] == '$' \
		|| ft_isspace((*str)[*i + j]))
		{
			if (!ft_isspace((*str)[*i + j]))
				j++;
			end = j;
			if (replace_dollar(array, start, end, str) == 0)
				return (0);
			*i = -1;
			break ;
		}
		j++;
	}
	return (1);
}

/*
* INFO:
*	This function processes an array, similar to the environment array,
*	and a string containing one or more variable names ($var_name). 
*	It replaces each variable name in the string 
*	with its corresponding value from the array."
*	@return : nothing, it changes the str directly, that's why it's send with a double pointer.
*/
int	expander(char **array, char **str)
{
	int	i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '$')
			if (!replace_var_manager(&i, str, array))
				return (0);
		i++;
	}
	return (1);
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
// 	content = "THX $ bye $END mais la dinguerie_$TUTUTUTU$ST";
// 	str = ft_strdup(content);
// 	if (expander(array, &str) == 0)
// 		printf("The expander failed.\n");
// 	else
// 		printf("END RESULT [%s]\n", str);
// 	i = 0;
// 	while (array[i])
// 		free(array[i++]);
// 	free(array);
// 	free(str);
// 	return (0);
// }
