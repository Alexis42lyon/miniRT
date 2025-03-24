/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 18:54:12 by abidolet          #+#    #+#             */
/*   Updated: 2025/03/24 15:05:24 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void	parse_vector(t_scene *scene, t_vec3 *vec, char *str)
{
	char	**tokens;

	tokens = ft_split(str, ',');
	if (!tokens)
		free_all(scene, "Malloc failed");
	if (ft_arrlen(tokens) != 3)
	{
		free_arr(tokens);
		free_all(scene, "Invalid vector format");
	}
	vec->x = ft_atof(tokens[0]);
	vec->y = ft_atof(tokens[1]);
	vec->z = ft_atof(tokens[2]);
	free_arr(tokens);
}

void	parse_color(t_scene *scene, size_t *color, char *str)
{
	char	**tokens;
	int		r;
	int		g;
	int		b;

	tokens = ft_split(str, ',');
	if (!tokens)
		free_all(scene, "Malloc failed");
	if (ft_arrlen(tokens) != 3)
	{
		free_arr(tokens);
		free_all(scene, "Invalid color format");
	}
	r = ft_atoi(tokens[0]);
	g = ft_atoi(tokens[1]);
	b = ft_atoi(tokens[2]);
	free_arr(tokens);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		free_all(scene, "Color values must be in range [0, 255]");
	}
	*color = (r << 16) + (g << 8) + b;
}

bool	is_normalized(t_vec3 vec)
{
	float	length;

	length = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	if (length == 0.0)
		return (0);
	return (fabs(length - 1.0) < 0.0001);
}
