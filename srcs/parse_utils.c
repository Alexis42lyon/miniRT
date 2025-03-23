/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 18:54:12 by abidolet          #+#    #+#             */
/*   Updated: 2025/03/23 23:47:28 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

bool	parse_vector(t_vec3 *vec, char *str)
{
	char	**tokens;

	tokens = ft_split(str, ',');
	if (!tokens || ft_arrlen(tokens) != 3)
	{
		if (tokens)
			free_arr(tokens);
		return (false);
	}
	vec->x = ft_atof(tokens[0]);
	vec->y = ft_atof(tokens[1]);
	vec->z = ft_atof(tokens[2]);
	free_arr(tokens);
	return (true);
}

int	parse_color(char *str)
{
	char	**tokens;
	int		r;
	int		g;
	int		b;

	tokens = ft_split(str, ',');
	if (!tokens || ft_arrlen(tokens) != 3)
	{
		if (tokens)
			free_arr(tokens);
		return (INVALID_COLOR);
	}
	r = ft_atoi(tokens[0]);
	g = ft_atoi(tokens[1]);
	b = ft_atoi(tokens[2]);
	free_arr(tokens);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (INVALID_COLOR);
	return ((r << 16) | (g << 8) | b);
}

int	is_normalized(t_vec3 vec)
{
	float	length;

	length = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	if (length == 0.0)
		return (0);
	return (fabs(length - 1.0) < 0.0001);
}
