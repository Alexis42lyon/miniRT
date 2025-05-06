/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 10:22:26 by abidolet          #+#    #+#             */
/*   Updated: 2025/05/06 15:28:48 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_bonus.h"
#include "camera_bonus.h"

static void	parse_light(t_prog *prog, t_light_source *light, char **tokens)
{
	if (ft_arrlen(tokens) != 4)
		print_exit(prog, "Invalid light format");
	parse_vector(prog, &light->origin, tokens[1]);
	light->ratio = check_atof(prog, tokens[2]);
	if (light->ratio < 0.0 || light->ratio > 1.0)
		print_exit(prog, "Light brightness must be in range [0.0, 1.0]");
	parse_color(prog, &light->material.albedo, tokens[3]);
}

static void	parse_camera(t_prog *prog, char **tokens)
{
	if (ft_arrlen(tokens) != 4)
		print_exit(prog, "Invalid camera format");
	parse_vector(prog, &prog->scene->camera.origin, tokens[1]);
	parse_vector(prog, &prog->scene->camera.forward, tokens[2]);
	prog->scene->camera.fov = check_atof(prog, tokens[3]);
	if (prog->scene->camera.fov < 0 || prog->scene->camera.fov > 180)
		print_exit(prog, "FOV must be in range [0, 180]");
	prog->scene->camera = new_camera(prog->scene->camera.origin,
			prog->scene->camera.forward, prog->scene->camera.fov);
}

static void	parse_ambient_light(t_prog *prog, char **tokens)
{
	if (ft_arrlen(tokens) != 3)
		print_exit(prog, "Invalid ambient light format");
	prog->scene->ambient_light.ratio = check_atof(prog, tokens[1]);
	if (prog->scene->ambient_light.ratio < 0.0
		|| prog->scene->ambient_light.ratio > 1.0)
		print_exit(prog, "Ambient light ratio must be in range [0.0, 1.0]");
	parse_color(prog, &prog->scene->ambient_light.color, tokens[2]);
}

void	parse(t_prog *prog, t_parser *parser, t_scene *scene, t_list *current)
{
	char	**tokens;

	while (current)
	{
		tokens = (char **)current->content;
		if (!ft_strcmp(tokens[0], "A"))
			parse_ambient_light(prog, tokens);
		else if (!ft_strcmp(tokens[0], "C"))
			parse_camera(prog, tokens);
		else if (!ft_strcmp(tokens[0], "L"))
			parse_light(prog, scene->lights + parser->i_light++, tokens);
		else if (!ft_strcmp(tokens[0], "sp"))
			parse_sphere(prog, scene->spheres + parser->i_sphere++, tokens);
		else if (!ft_strcmp(tokens[0], "pl"))
			parse_plane(prog, scene->planes + parser->i_plane++, tokens);
		else if (!ft_strcmp(tokens[0], "cy"))
			parse_cylinder(prog, scene->cylinders + parser->i_cylinder++,
				tokens);
		else if (!ft_strcmp(tokens[0], "co"))
			parse_cylinder(prog, scene->cones + parser->i_cone++, tokens);
		current = current->next;
	}
}
