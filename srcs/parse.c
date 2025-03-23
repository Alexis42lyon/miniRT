/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 18:05:22 by abidolet          #+#    #+#             */
/*   Updated: 2025/03/23 23:54:33 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

static void	parse_light(t_scene *scene, char *line)
{
	char	**tokens;
	t_vec3	origin;

	if (scene->light.is_set)
	{
		free(line);
		free_all(scene, "Light can only be declared once in the scene");
	}
	scene->light.is_set = true;
	tokens = ft_split(line, ' ');
	free(line);
	if (!tokens || ft_arrlen(tokens) != 4)
	{
		free_arr(tokens);
		free_all(scene, "Invalid light format");
	}
	if (!parse_vector(&origin, tokens[1]))
	{
		free_arr(tokens);
		free_all(scene, "Invalid light position");
	}
	scene->light.origin = origin;
	scene->light.ratio = ft_atof(tokens[2]);
	if (scene->light.ratio < 0.0 || scene->light.ratio > 1.0)
	{
		free_arr(tokens);
		free_all(scene, "Light brightness must be in range [0.0, 1.0]");
	}
	scene->light.color = parse_color(tokens[3]);
	free_arr(tokens);
	if (scene->light.color == INVALID_COLOR)
		free_all(scene, "Invalid light color format");
}

static void	parse_camera(t_scene *scene, char *line)
{
	char	**tokens;
	t_vec3	origin;
	t_vec3	direction;

	if (scene->camera.is_set)
	{
		free(line);
		free_all(scene, "Camera can only be declared once in the scene");
	}
	scene->camera.is_set = true;
	tokens = ft_split(line, ' ');
	free(line);
	if (!tokens || ft_arrlen(tokens) != 4)
	{
		if (tokens)
			free_arr(tokens);
		free_all(scene, "Invalid camera format");
	}
	if (!parse_vector(&origin, tokens[1]))
	{
		free_arr(tokens);
		free_all(scene, "Invalid camera position");
	}
	scene->camera.origin = origin;
	if (!parse_vector(&direction, tokens[2]))
	{
		free_arr(tokens);
		free_all(scene, "Invalid camera orientation");
	}
	if (!is_normalized(direction))
	{
		free_arr(tokens);
		free_all(scene, "Invalid camera orientation");
	}
	scene->camera.direction = direction;
	scene->camera.fov = ft_atoi(tokens[3]);
	free_arr(tokens);
	if (scene->camera.fov < 0 || scene->camera.fov > 180)
		free_all(scene, "FOV must be in range [0, 180]");
}

static void	parse_ambient_light(t_scene *scene, char *line)
{
	char	**tokens;

	if (scene->ambient_light.is_set)
	{
		free(line);
		free_all(scene, "Ambient lightning can only be declared once in the scene");
	}
	scene->ambient_light.is_set = true;
	tokens = ft_split(line, ' ');
	free(line);
	if (!tokens || ft_arrlen(tokens) != 3)
	{
		free_arr(tokens);
		free_all(scene, "Invalid ambient light format");
	}
	scene->ambient_light.ratio = ft_atof(tokens[1]);
	if (scene->ambient_light.ratio < 0.0 || scene->ambient_light.ratio > 1.0)
	{
		free_arr(tokens);
		free_all(scene, "Ambient ratio must be in range [0.0, 1.0]");
	}
	scene->ambient_light.color = parse_color(tokens[2]);
	free_arr(tokens);
	if (scene->ambient_light.color == INVALID_COLOR)
		free_all(scene, "Invalid ambient color format");
}

void	parse(t_scene *scene, int fd)
{
	char	*line;

	line = ft_get_next_line(fd);
	while (line)
	{
		if (!ft_strccmp(line, "A", ' '))
			parse_ambient_light(scene, line);
		else if (!ft_strccmp(line, "C", ' '))
			parse_camera(scene, line);
		else if (!ft_strccmp(line, "L", ' '))
			parse_light(scene, line);
		else if (!ft_strccmp(line, "sp", ' '))
			parse_sphere(scene, line);
		else if (!ft_strccmp(line, "pl", ' '))
			parse_plane(scene, line);
		else if (!ft_strccmp(line, "cy", ' '))
			parse_cylinder(scene, line);
		else if (!ft_strcmp(line, "\n") || !ft_strcmp(line, " "))
			free(line);
		else
		{
			free(line);
			free_all(scene, "Invalid identifier");
		}
		line = ft_get_next_line(fd);
	}
}
