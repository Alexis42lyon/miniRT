/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 18:08:02 by abidolet          #+#    #+#             */
/*   Updated: 2025/03/24 15:05:00 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void	parse_cylinder(t_scene *scene)
{
	t_vec3	origin;
	t_vec3	normal;

	if (ft_arrlen(scene->tokens) != 6)
		free_all(scene, "Invalid cylinder format");
	parse_vector(scene, &origin, scene->tokens[1]);
	scene->cylinders->origin = origin;
	parse_vector(scene, &normal, scene->tokens[2]);
	if (!is_normalized(normal))
		free_all(scene, "Invalid cylinder normal");
	scene->cylinders->normal = normal;
	scene->cylinders->diameter = ft_atof(scene->tokens[3]);
	if (scene->cylinders->diameter <= 0)
		free_all(scene, "Cylinder diameter must be positive");
	scene->cylinders->height = ft_atof(scene->tokens[4]);
	if (scene->cylinders->height <= 0)
		free_all(scene, "Cylinder height must be positive");
	parse_color(scene, &scene->cylinders->color, scene->tokens[5]);
}

void	parse_plane(t_scene *scene)
{
	t_vec3	origin;
	t_vec3	normal;

	if (ft_arrlen(scene->tokens) != 4)
		free_all(scene, "Invalid plane format");
	parse_vector(scene, &origin, scene->tokens[1]);
	scene->planes->origin = origin;
	parse_vector(scene, &normal, scene->tokens[2]);
	if (!is_normalized(normal))
		free_all(scene, "Invalid plane normal");
	scene->planes->normal = normal;
	parse_color(scene, &scene->planes->color, scene->tokens[3]);
}

void	parse_sphere(t_scene *scene)
{
	t_vec3	origin;

	if (ft_arrlen(scene->tokens) != 4)
		free_all(scene, "Invalid sphere format");
	parse_vector(scene, &origin, scene->tokens[1]);
	scene->spheres->origin = origin;
	scene->spheres->diameter = ft_atof(scene->tokens[2]);
	if (scene->spheres->diameter <= 0)
		free_all(scene, "Sphere diameter must be positive");
	parse_color(scene, &scene->spheres->color, scene->tokens[3]);
}
