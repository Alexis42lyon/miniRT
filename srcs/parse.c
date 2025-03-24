/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 18:05:22 by abidolet          #+#    #+#             */
/*   Updated: 2025/03/24 15:03:46 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

static void	parse_light(t_scene *scene)
{
	t_vec3	origin;

	if (scene->light.is_set)
		free_all(scene, "Light can only be declared once in the scene");
	scene->light.is_set = true;
	if (ft_arrlen(scene->tokens) != 4)
		free_all(scene, "Invalid light format");
	parse_vector(scene, &origin, scene->tokens[1]);
	scene->light.origin = origin;
	scene->light.ratio = ft_atof(scene->tokens[2]);
	if (scene->light.ratio < 0.0 || scene->light.ratio > 1.0)
		free_all(scene, "Light brightness must be in range [0.0, 1.0]");
	parse_color(scene, &scene->light.color, scene->tokens[3]);
}

static void	parse_camera(t_scene *scene)
{
	t_vec3	origin;
	t_vec3	direction;

	if (scene->camera.is_set)
		free_all(scene, "Camera can only be declared once in the scene");
	scene->camera.is_set = true;
	if (ft_arrlen(scene->tokens) != 4)
		free_all(scene, "Invalid camera format");
	parse_vector(scene, &origin, scene->tokens[1]);
	scene->camera.origin = origin;
	parse_vector(scene, &direction, scene->tokens[2]);
	if (!is_normalized(direction))
		free_all(scene, "Invalid camera orientation");
	scene->camera.direction = direction;
	scene->camera.fov = ft_atoi(scene->tokens[3]);
	if (scene->camera.fov < 0 || scene->camera.fov > 180)
		free_all(scene, "FOV must be in range [0, 180]");
}

static void	parse_ambient_light(t_scene *scene)
{
	if (scene->ambient_light.is_set)
		free_all(scene, "Ambient lightning can only be declared once in the scene");
	scene->ambient_light.is_set = true;
	if (ft_arrlen(scene->tokens) != 3)
		free_all(scene, "Invalid ambient light format");
	scene->ambient_light.ratio = ft_atof(scene->tokens[1]);
	if (scene->ambient_light.ratio < 0.0 || scene->ambient_light.ratio > 1.0)
		free_all(scene, "Ambient ratio must be in range [0.0, 1.0]");
	parse_color(scene, &scene->ambient_light.color, scene->tokens[2]);
}

void	parse(t_scene *scene, int fd)
{
	char	*line;

	line = ft_get_next_line(fd);
	while (line)
	{
		scene->tokens = ft_split(line, ' ');
		free(line);
		if (!scene->tokens)
			free_all(scene, "Malloc failed");
		if (!ft_strcmp(scene->tokens[0], "A"))
			parse_ambient_light(scene);
		else if (!ft_strcmp(scene->tokens[0], "C"))
			parse_camera(scene);
		else if (!ft_strcmp(scene->tokens[0], "L"))
			parse_light(scene);
		else if (!ft_strcmp(scene->tokens[0], "sp"))
			parse_sphere(scene);
		else if (!ft_strcmp(scene->tokens[0], "pl"))
			parse_plane(scene);
		else if (!ft_strcmp(scene->tokens[0], "cy"))
			parse_cylinder(scene);
		else if (ft_strcmp(scene->tokens[0], "\n"))
			free_all(scene, "Invalid identifier");
		free_arr(scene->tokens);
		line = ft_get_next_line(fd);
	}
}
