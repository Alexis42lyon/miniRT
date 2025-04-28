/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_assemble.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:50:40 by mjuncker          #+#    #+#             */
/*   Updated: 2025/04/25 12:23:10 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/string.h"

static void	free_strings(struct string_ass *strings)
{
	int		i;

	i = 0;
	while (strings[i].string)
	{
		if (strings[i].to_free)
			free(strings[i].string);
		i++;
	}
}

char *ft_strassemble(struct string_ass *strings)
{
	char	*result;
	int		i;

	result = NULL;
	i = 0;
	while (strings[i].string)
	{
		result = ft_strjoin_free(result, strings[i].string, FREE1);
		if (!result)
		{
			free_strings(strings);
			return (NULL);
		}
		i++;
	}
	free_strings(strings);
	return (result);
}