/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 18:54:12 by abidolet          #+#    #+#             */
/*   Updated: 2025/03/25 09:25:57 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>
#include <math.h>

void	parse_vector(t_vec3 *vec, char *str)
{
	char	**tokens;

	tokens = ft_split(str, ',');
	if (!tokens)
		free_all(NULL);
	if (ft_arrlen(tokens) != 3)
	{
		free_arr((void **)tokens);
		free_all(NULL);
	}
	vec->x = ft_atof(tokens[0]);
	vec->y = ft_atof(tokens[1]);
	vec->z = ft_atof(tokens[2]);
	free_arr((void **)tokens);
}

void	parse_color(size_t *color, char *str)
{
	char	**tokens;
	int		r;
	int		g;
	int		b;

	tokens = ft_split(str, ',');
	if (!tokens)
		free_all(NULL);
	if (ft_arrlen(tokens) != 3)
	{
		free_arr((void **)tokens);
		free_all(NULL);
	}
	r = ft_atoi(tokens[0]);
	g = ft_atoi(tokens[1]);
	b = ft_atoi(tokens[2]);
	free_arr((void **)tokens);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		ft_dprintf(2, "Error\nColor values must be in range [0, 255]\n");
		free_all(NULL);
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

void	init_malloc(t_scene *scene)
{
	check_mem(get_info(__FILE__, __LINE__, __func__),
		malloc(sizeof(t_sphere) * (scene->nb_spheres + 1)),
		(void **)&scene->spheres);
	check_mem(get_info(__FILE__, __LINE__, __func__),
		malloc(sizeof(t_plane) * (scene->nb_planes + 1)),
		(void **)&scene->planes);
	check_mem(get_info(__FILE__, __LINE__, __func__),
		malloc(sizeof(t_cylinder) * (scene->nb_cylinders + 1)),
		(void **)&scene->cylinders);
}
