/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 18:08:02 by abidolet          #+#    #+#             */
/*   Updated: 2025/03/25 09:27:32 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void	parse_cylinder(t_scene *scene, char **tokens)
{
	t_vec3	origin;
	t_vec3	normal;

	if (ft_arrlen(tokens) != 6)
	{
		ft_dprintf(2, "Error\nInvalid cylinder format\n");
		free_all(NULL);
	}
	parse_vector(&origin, tokens[1]);
	scene->cylinders->origin = origin;
	parse_vector(&normal, tokens[2]);
	if (!is_normalized(normal))
	{
		ft_dprintf(2, "Error\nInvalid cylinder normal\n");
		free_all(NULL);
	}
	scene->cylinders->normal = normal;
	scene->cylinders->diameter = ft_atof(tokens[3]);
	if (scene->cylinders->diameter <= 0)
	{
		ft_dprintf(2, "Error\nCylinder diameter must be positive\n");
		free_all(NULL);
	}
	scene->cylinders->height = ft_atof(tokens[4]);
	if (scene->cylinders->height <= 0)
	{
		ft_dprintf(2, "Error\nCylinder height must be positive\n");
		free_all(NULL);
	}
	parse_color(&scene->cylinders->color, tokens[5]);
}

void	parse_plane(t_scene *scene, char **tokens)
{
	t_vec3	origin;
	t_vec3	normal;

	if (ft_arrlen(tokens) != 4)
	{
		ft_dprintf(2, "Error\nInvalid plane format\n");
		free_all(NULL);
	}
	parse_vector(&origin, tokens[1]);
	scene->planes->origin = origin;
	parse_vector(&normal, tokens[2]);
	if (!is_normalized(normal))
	{
		ft_dprintf(2, "Error\nInvalid plane normal\n");
		free_all(NULL);
	}
	scene->planes->normal = normal;
	parse_color(&scene->planes->color, tokens[3]);
}

void	parse_sphere(t_scene *scene, char **tokens)
{
	t_vec3	origin;

	if (ft_arrlen(tokens) != 4)
	{
		ft_dprintf(2, "Error\nInvalid sphere format\n");
		free_all(NULL);
	}
	parse_vector(&origin, tokens[1]);
	scene->spheres->origin = origin;
	scene->spheres->diameter = ft_atof(tokens[2]);
	if (scene->spheres->diameter <= 0)
	{
		ft_dprintf(2, "Error\nSphere diameter must be positive\n");
		free_all(NULL);
	}
	parse_color(&scene->spheres->color, tokens[3]);
}
