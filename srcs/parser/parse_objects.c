/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 10:22:34 by abidolet          #+#    #+#             */
/*   Updated: 2025/04/23 11:35:30 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft/vector.h"
#include <stdio.h>

static int	find_material_index(t_prog *prog, char *material_name)
{
	unsigned int	i;

	if (prog->scene->materials == NULL)
		print_exit(prog, "No materials loaded");
	i = 0;
	while (i < prog->parser->nb_id)
	{
		if (ft_strcmp(prog->scene->materials[i].name, material_name) == 0)
			return (i);
		i++;
	}
	print_exit(prog, "Material not found");
	return (-1);
}

void	parse_cylinder(t_prog *prog, t_cylinder *cylinder, char **tokens)
{
	if (ft_arrlen(tokens) != 6)
		print_exit(prog, "Invalid cylinder format");
	parse_vector(prog, &cylinder->origin, tokens[1]);
	parse_vector(prog, &cylinder->normal, tokens[2]);
	cylinder->normal = vec3_normalize(cylinder->normal);
	cylinder->radius = check_atof(prog, tokens[3]);
	if (cylinder->radius <= 0)
		print_exit(prog, "Cylinder radius must be positive");
	cylinder->height = check_atof(prog, tokens[4]);
	if (cylinder->height <= 0)
		print_exit(prog, "Cylinder height must be positive");
	cylinder->mat_idx = find_material_index(prog, tokens[5]);
	cylinder->material = prog->scene->materials[cylinder->mat_idx];
}

void	parse_plane(t_prog *prog, t_plane *plane, char **tokens)
{
	if (ft_arrlen(tokens) != 4)
		print_exit(prog, "Invalid plane format");
	parse_vector(prog, &plane->origin, tokens[1]);
	parse_vector(prog, &plane->normal, tokens[2]);
	plane->normal = vec3_normalize(plane->normal);
	// if (plane->normal.y < 0)
	// 	plane->normal = vec3_mult(plane->normal, -1.0);
	plane->mat_idx = find_material_index(prog, tokens[3]);
	plane->material = prog->scene->materials[plane->mat_idx];
}

void	parse_sphere(t_prog *prog, t_sphere *sphere, char **tokens)
{
	if (ft_arrlen(tokens) != 4)
		print_exit(prog, "Invalid sphere format");
	parse_vector(prog, &sphere->origin, tokens[1]);
	sphere->radius = check_atof(prog, tokens[2]);
	if (sphere->radius <= 0)
		print_exit(prog, "Sphere diameter must be positive");
	sphere->mat_idx = find_material_index(prog, tokens[3]);
	sphere->material = prog->scene->materials[sphere->mat_idx];
}
