/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 18:08:02 by abidolet          #+#    #+#             */
/*   Updated: 2025/03/24 09:57:00 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void	parse_cylinder(t_scene *scene)
{
	t_vec3	origin;
	t_vec3	normal;

	if (ft_arrlen(scene->tokens) != 6)
		free_all(scene, "Invalid cylinder format");
	if (!parse_vector(scene, &origin, scene->tokens[1]))
		free_all(scene, "Invalid cylinder center");
	scene->cylinders->origin = origin;
	if (!parse_vector(scene, &normal, scene->tokens[2]) || !is_normalized(normal))
		free_all(scene, "Invalid cylinder normal");
	scene->cylinders->normal = normal;
	scene->cylinders->diameter = ft_atof(scene->tokens[3]);
	if (scene->cylinders->diameter <= 0)
		free_all(scene, "Cylinder diameter must be positive");
	scene->cylinders->height = ft_atof(scene->tokens[4]);
	if (scene->cylinders->height <= 0)
		free_all(scene, "Cylinder height must be positive");
	if (parse_color(scene, &scene->cylinders->color, scene->tokens[5]) == false)
		free_all(scene, "Invalid cylinder color format");
}

void	parse_plane(t_scene *scene)
{
	t_vec3	origin;
	t_vec3	normal;

	if (ft_arrlen(scene->tokens) != 4)
		free_all(scene, "Invalid plane format");
	if (!parse_vector(scene, &origin, scene->tokens[1]))
		free_all(scene, "Invalid plane origin");
	scene->planes->origin = origin;
	if (!parse_vector(scene, &normal, scene->tokens[2]))
		free_all(scene, "Invalid plane normal");
	if (!is_normalized(normal))
		free_all(scene, "Invalid plane normal");
	scene->planes->normal = normal;
	if (parse_color(scene, &scene->planes->color, scene->tokens[3]) == false)
		free_all(scene, "Invalid plane color format");
}

void	parse_sphere(t_scene *scene)
{
	t_vec3	origin;

	if (ft_arrlen(scene->tokens) != 4)
		free_all(scene, "Invalid sphere format");
	if (!parse_vector(scene, &origin, scene->tokens[1]))
		free_all(scene, "Invalid sphere center");
	scene->spheres->origin = origin;
	scene->spheres->diameter = ft_atof(scene->tokens[2]);
	if (scene->spheres->diameter <= 0)
		free_all(scene, "Sphere diameter must be positive");
	if (parse_color(scene, &scene->spheres->color, scene->tokens[3]) == false)
		free_all(scene, "Invalid sphere color format");
}
