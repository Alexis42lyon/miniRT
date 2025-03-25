/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 18:05:22 by abidolet          #+#    #+#             */
/*   Updated: 2025/03/25 08:44:32 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

static void	parse_light(t_scene *scene, char **tokens)
{
	t_vec3	origin;

	if (scene->light.is_set)
		free_all(scene, "Light can only be declared once in the scene");
	scene->light.is_set = true;
	if (ft_arrlen(tokens) != 4)
		free_all(scene, "Invalid light format");
	parse_vector(scene, &origin, tokens[1]);
	scene->light.origin = origin;
	scene->light.ratio = ft_atof(tokens[2]);
	if (scene->light.ratio < 0.0 || scene->light.ratio > 1.0)
		free_all(scene, "Light brightness must be in range [0.0, 1.0]");
	parse_color(scene, &scene->light.color, tokens[3]);
}

static void	parse_camera(t_scene *scene, char **tokens)
{
	t_vec3	origin;
	t_vec3	direction;

	if (scene->camera.is_set)
		free_all(scene, "Camera can only be declared once in the scene");
	scene->camera.is_set = true;
	if (ft_arrlen(tokens) != 4)
		free_all(scene, "Invalid camera format");
	parse_vector(scene, &origin, tokens[1]);
	scene->camera.origin = origin;
	parse_vector(scene, &direction, tokens[2]);
	if (!is_normalized(direction))
		free_all(scene, "Invalid camera orientation");
	scene->camera.direction = direction;
	scene->camera.fov = ft_atoi(tokens[3]);
	if (scene->camera.fov < 0 || scene->camera.fov > 180)
		free_all(scene, "FOV must be in range [0, 180]");
}

static void	parse_ambient_light(t_scene *scene, char **tokens)
{
	if (scene->ambient_light.is_set)
		free_all(scene, "Ambient lightning can only be declared once");
	scene->ambient_light.is_set = true;
	if (ft_arrlen(tokens) != 3)
		free_all(scene, "Invalid ambient light format");
	scene->ambient_light.ratio = ft_atof(tokens[1]);
	if (scene->ambient_light.ratio < 0.0 || scene->ambient_light.ratio > 1.0)
		free_all(scene, "Ambient ratio must be in range [0.0, 1.0]");
	parse_color(scene, &scene->ambient_light.color, tokens[2]);
}

void	parse_map(t_scene *scene)
{
	char	**tokens;
	t_list	*new_node;

	scene->line = ft_get_next_line(scene->fd);
	while (scene->line)
	{
		check_mem(get_info(__FILE__, __LINE__, __func__),
			scene, NULL, (void **)&tokens);
		if (!ft_strcmp(tokens[0], "sp"))
			scene->nb_spheres++;
		else if (!ft_strcmp(tokens[0], "pl"))
			scene->nb_planes++;
		else if (!ft_strcmp(tokens[0], "cy"))
			scene->nb_cylinders++;
		check_mem(get_info(__FILE__, __LINE__, __func__),
			scene, ft_lstnew(tokens), (void **)&new_node);
		ft_lstadd_back(&scene->map, new_node);
		free(scene->line);
		scene->line = ft_get_next_line(scene->fd);
	}
}

void	parse(t_scene *scene)
{
	t_list	*current;
	char	**tokens;

	parse_map(scene);
	init_malloc(scene);
	current = scene->map;
	while (current)
	{
		tokens = (char **)current->content;
		if (!ft_strcmp(tokens[0], "A"))
			parse_ambient_light(scene, tokens);
		else if (!ft_strcmp(tokens[0], "C"))
			parse_camera(scene, tokens);
		else if (!ft_strcmp(tokens[0], "L"))
			parse_light(scene, tokens);
		else if (!ft_strcmp(tokens[0], "sp"))
			parse_sphere(scene, tokens);
		else if (!ft_strcmp(tokens[0], "pl"))
			parse_plane(scene, tokens);
		else if (!ft_strcmp(tokens[0], "cy"))
			parse_cylinder(scene, tokens);
		else if (ft_strcmp(tokens[0], "\n"))
			free_all(scene, "Invalid identifier");
		current = current->next;
	}
}
