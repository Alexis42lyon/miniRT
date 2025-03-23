/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 18:08:02 by abidolet          #+#    #+#             */
/*   Updated: 2025/03/23 23:49:02 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void	parse_cylinder(t_scene *scene, char *line)
{
	char	**tokens;
	t_vec3	origin;
	t_vec3	normal;

	tokens = ft_split(line, ' ');
	free(line);
	if (!tokens || ft_arrlen(tokens) != 6)
	{
		free_arr(tokens);
		free_all(scene, "Invalid cylinder format");
	}
	if (!parse_vector(&origin, tokens[1]))
		free_all(scene, "Invalid cylinder center");
	scene->cylinders->origin = origin;
	if (!parse_vector(&normal, tokens[2]))
		free_all(scene, "Invalid cylinder axis");
	if (!is_normalized(normal))
		free_all(scene, "Invalid cylinder axis");
	scene->cylinders->normal = normal;
	scene->cylinders->diameter = ft_atof(tokens[3]);
	if (scene->cylinders->diameter <= 0)
		free_all(scene, "Cylinder diameter must be positive");
	scene->cylinders->height = ft_atof(tokens[4]);
	if (scene->cylinders->height <= 0)
		free_all(scene, "Cylinder height must be positive");
	scene->cylinders->color = parse_color(tokens[5]);
	if (scene->cylinders->color == INVALID_COLOR)
		free_all(scene, "Invalid cylinder color format");
	free_arr(tokens);
}

void	parse_plane(t_scene *scene, char *line)
{
	char	**tokens;
	t_vec3	origin;
	t_vec3	normal;

	tokens = ft_split(line, ' ');
	free(line);
	if (!tokens || ft_arrlen(tokens) != 4)
	{
		free_arr(tokens);
		free_all(scene, "Invalid plane format");
	}
	if (!parse_vector(&origin, tokens[1]))
	{
		free_arr(tokens);
		free_all(scene, "Invalid plane origin");
	}
	scene->planes->origin = origin;
	if (!parse_vector(&normal, tokens[2]))
	{
		free_arr(tokens);
		free_all(scene, "Invalid plane normal");
	}
	if (!is_normalized(normal))
	{
		free_arr(tokens);
		free_all(scene, "Invalid plane normal");
	}
	scene->planes->normal = normal;
	scene->planes->color = parse_color(tokens[3]);
	if (scene->planes->color == INVALID_COLOR)
	{
		free_arr(tokens);
		free_all(scene, "Invalid plane color format");
	}
	free_arr(tokens);
}

void	parse_sphere(t_scene *scene, char *line)
{
	char	**tokens;
	t_vec3	origin;

	tokens = ft_split(line, ' ');
	free(line);
	if (!tokens || ft_arrlen(tokens) != 4)
	{
		free_arr(tokens);
		free_all(scene, "Invalid sphere format");
	}
	if (!parse_vector(&origin, tokens[1]))
	{
		free_arr(tokens);
		free_all(scene, "Invalid sphere center");
	}
	scene->spheres->origin = origin;
	scene->spheres->diameter = ft_atof(tokens[2]);
	if (scene->spheres->diameter <= 0)
	{
		free_arr(tokens);
		free_all(scene, "Sphere diameter must be positive");
	}
	scene->spheres->color = parse_color(tokens[3]);
	free_arr(tokens);
	if (scene->spheres->color == INVALID_COLOR)
		free_all(scene, "Invalid sphere color format");
}
