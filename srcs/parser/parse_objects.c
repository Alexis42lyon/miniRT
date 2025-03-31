/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 18:08:02 by abidolet          #+#    #+#             */
/*   Updated: 2025/03/31 10:50:18 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	parse_cylinder(t_prog *prog, t_cylinder *cylinder, char **tokens)
{
	t_vec3	origin;
	t_vec3	normal;

	if (ft_arrlen(tokens) != 6)
		print_exit(prog, "Invalid cylinder format");
	parse_vector(prog, &origin, tokens[1]);
	cylinder->origin = origin;
	parse_vector(prog, &normal, tokens[2]);
	if (!is_normalized(normal))
		print_exit(prog, "Invalid cylinder normal");
	cylinder->normal = normal;
	cylinder->radius = ft_atof(tokens[3]);
	if (cylinder->radius <= 0)
		print_exit(prog, "Invalid cylinder diameter");
	cylinder->height = ft_atof(tokens[4]);
	if (cylinder->height <= 0)
		print_exit(prog, "Cylinder height must be positive");
	parse_color(prog, &cylinder->color, tokens[5]);
}

void	parse_plane(t_prog *prog, t_plane *plane, char **tokens)
{
	t_vec3	origin;
	t_vec3	normal;

	if (ft_arrlen(tokens) != 4)
		print_exit(prog, "Invalid plane format");
	parse_vector(prog, &origin, tokens[1]);
	plane->origin = origin;
	parse_vector(prog, &normal, tokens[2]);
	if (!is_normalized(normal))
		print_exit(prog, "Invalid plane normal");
	plane->normal = normal;
	parse_color(prog, &plane->color, tokens[3]);
}

void	parse_sphere(t_prog *prog, t_sphere *sphere, char **tokens)
{
	t_vec3	origin;

	if (ft_arrlen(tokens) != 4)
		print_exit(prog, "Invalid sphere format");
	parse_vector(prog, &origin, tokens[1]);
	sphere->origin = origin;
	sphere->radius = ft_atof(tokens[2]);
	if (sphere->radius <= 0)
		print_exit(prog, "Sphere diameter must be positive");
	parse_color(prog, &sphere->color, tokens[3]);
}
