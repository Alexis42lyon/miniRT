/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 18:05:22 by abidolet          #+#    #+#             */
/*   Updated: 2025/03/27 18:25:24 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

static void	parse_light(t_prog *prog, char **tokens)
{
	t_vec3	origin;

	if (prog->scene->light.is_set)
	{
		ft_dprintf(2, "Error\nLight can only be declared once in the scene\n");
		free_all(prog);
	}
	prog->scene->light.is_set = true;
	if (ft_arrlen(tokens) != 4)
	{
		ft_dprintf(2, "Error\nInvalid light format\n");
		free_all(prog);
	}
	parse_vector(prog, &origin, tokens[1]);
	prog->scene->light.origin = origin;
	prog->scene->light.ratio = ft_atof(tokens[2]);
	if (prog->scene->light.ratio < 0.0 || prog->scene->light.ratio > 1.0)
	{
		ft_dprintf(2, "Error\nLight brightness must be in range [0.0, 1.0]\n");
		free_all(prog);
	}
	parse_color(prog, &prog->scene->light.color, tokens[3]);
}

static void	parse_camera(t_prog *prog, char **tokens)
{
	t_vec3	origin;
	t_vec3	direction;

	if (prog->scene->camera.is_set)
	{
		ft_dprintf(2, "Error\nCamera can only be declared once in the scene\n");
		free_all(prog);
	}
	prog->scene->camera.is_set = true;
	if (ft_arrlen(tokens) != 4)
	{
		ft_dprintf(2, "Error\nInvalid camera format\n");
		free_all(prog);
	}
	parse_vector(prog, &origin, tokens[1]);
	prog->scene->camera.origin = origin;
	parse_vector(prog, &direction, tokens[2]);
	if (!is_normalized(direction))
	{
		ft_dprintf(2, "Error\nInvalid camera orientation\n");
		free_all(prog);
	}
	prog->scene->camera.direction = direction;
	prog->scene->camera.fov = ft_atoi(tokens[3]);
	if (prog->scene->camera.fov < 0 || prog->scene->camera.fov > 180)
	{
		ft_dprintf(2, "Error\nFOV must be in range [0, 180]\n");
		free_all(prog);
	}
}

static void	parse_ambient_light(t_prog *prog, char **tokens)
{
	if (prog->scene->ambient_light.is_set)
	{
		ft_dprintf(2, "Error\nAmbient lightning can only be declared once\n");
		free_all(prog);
	}
	prog->scene->ambient_light.is_set = true;
	if (ft_arrlen(tokens) != 3)
	{
		ft_dprintf(2, "Error\nInvalid ambient light format\n");
		free_all(prog);
	}
	prog->scene->ambient_light.ratio = ft_atof(tokens[1]);
	if (prog->scene->ambient_light.ratio < 0.0 || prog->scene->ambient_light.ratio > 1.0)
	{
		ft_dprintf(2, "Error\nAmbient ratio must be in range [0.0, 1.0]\n");
		free_all(prog);
	}
	parse_color(prog, &prog->scene->ambient_light.color, tokens[2]);
}

void	parse_map(t_prog *prog)
{
	char	**tokens;
	t_list	*new_node;

	tokens = NULL;
	new_node = NULL;
	prog->scene->line = ft_get_next_line(prog->scene->fd);
	while (prog->scene->line)
	{
		check_mem((t_info){__FILE__, __LINE__, __func__},
			ft_split(prog->scene->line, ' '), (void **)&tokens, prog);
		if (!ft_strcmp(tokens[0], "sp"))
			prog->scene->nb_spheres++;
		else if (!ft_strcmp(tokens[0], "pl"))
			prog->scene->nb_planes++;
		else if (!ft_strcmp(tokens[0], "cy"))
			prog->scene->nb_cylinders++;
		check_mem((t_info){__FILE__, __LINE__, __func__},
			ft_lstnew(tokens), (void **)&new_node, prog);
		ft_lstadd_back(&prog->scene->map, new_node);
		free(prog->scene->line);
		prog->scene->line = ft_get_next_line(prog->scene->fd);
	}
}

void	parse(t_prog *prog)
{
	t_list	*current;
	char	**tokens;

	parse_map(prog);
	init_malloc(prog);
	current = prog->scene->map;
	while (current)
	{
		tokens = (char **)current->content;
		if (!ft_strcmp(tokens[0], "A"))
			parse_ambient_light(prog, tokens);
		else if (!ft_strcmp(tokens[0], "C"))
			parse_camera(prog, tokens);
		else if (!ft_strcmp(tokens[0], "L"))
			parse_light(prog, tokens);
		else if (!ft_strcmp(tokens[0], "sp"))
			parse_sphere(prog, tokens);
		else if (!ft_strcmp(tokens[0], "pl"))
			parse_plane(prog, tokens);
		else if (!ft_strcmp(tokens[0], "cy"))
			parse_cylinder(prog, tokens);
		else if (ft_strcmp(tokens[0], "\n"))
		{
			ft_dprintf(2, "Error\nInvalid identifier\n");
			free_all(prog);
		}
		current = current->next;
	}
}
