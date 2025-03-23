/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:58:50 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/23 23:13:32 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/string.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*cs1;
	unsigned char	*cs2;

	cs1 = (unsigned char *)s1;
	cs2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (cs1[i] != cs2[i])
			return (cs1[i] - cs2[i]);
		if (!s1[i] || !s2[i])
			break ;
		i++;
	}
	return (0);
}

int	ft_strccmp(const char *s1, const char *s2, char c)
{
	size_t	i;
	size_t	j;

	j = 0;
	while (s1[j] == ' ')
		j++;
	i = 0;
	while (s1[i + j] && s2[i] && s1[i + j] == s2[i] && s1[i + j] != c)
		i++;
	if (s1[i + j] == c)
		return (0);
	return (s1[i + j] - s2[i]);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	if (!s1)
		return (-1);
	else if (!s2)
		return (1);
	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	if (s1[i] || s2[i])
		return (s1[i] - s2[i]);
	return (0);
}
