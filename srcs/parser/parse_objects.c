/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 18:08:02 by abidolet          #+#    #+#             */
/*   Updated: 2025/03/27 17:44:26 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void	parse_cylinder(t_prog *prog, char **tokens)
{
	t_vec3	origin;
	t_vec3	normal;

	if (ft_arrlen(tokens) != 6)
	{
		ft_dprintf(2, "Error\nInvalid cylinder format\n");
		free_all(prog);
	}
	parse_vector(prog, &origin, tokens[1]);
	prog->scene->cylinders->origin = origin;
	parse_vector(prog, &normal, tokens[2]);
	if (!is_normalized(normal))
	{
		ft_dprintf(2, "Error\nInvalid cylinder normal\n");
		free_all(prog);
	}
	prog->scene->cylinders->normal = normal;
	prog->scene->cylinders->radius = ft_atof(tokens[3]);
	if (prog->scene->cylinders->radius <= 0)
	{
		ft_dprintf(2, "Error\nCylinder diameter must be positive\n");
		free_all(prog);
	}
	prog->scene->cylinders->height = ft_atof(tokens[4]);
	if (prog->scene->cylinders->height <= 0)
	{
		ft_dprintf(2, "Error\nCylinder height must be positive\n");
		free_all(prog);
	}
	parse_color(prog, &prog->scene->cylinders->color, tokens[5]);
}

void	parse_plane(t_prog *prog, char **tokens)
{
	t_vec3	origin;
	t_vec3	normal;

	if (ft_arrlen(tokens) != 4)
	{
		ft_dprintf(2, "Error\nInvalid plane format\n");
		free_all(prog);
	}
	parse_vector(prog, &origin, tokens[1]);
	prog->scene->planes->origin = origin;
	parse_vector(prog, &normal, tokens[2]);
	if (!is_normalized(normal))
	{
		ft_dprintf(2, "Error\nInvalid plane normal\n");
		free_all(prog);
	}
	prog->scene->planes->normal = normal;
	parse_color(prog, &prog->scene->planes->color, tokens[3]);
}

void	parse_sphere(t_prog *prog, char **tokens)
{
	t_vec3	origin;

	if (ft_arrlen(tokens) != 4)
	{
		ft_dprintf(2, "Error\nInvalid sphere format\n");
		free_all(prog);
	}
	parse_vector(prog, &origin, tokens[1]);
	prog->scene->spheres->origin = origin;
	prog->scene->spheres->radius = ft_atof(tokens[2]);
	if (prog->scene->spheres->radius <= 0)
	{
		ft_dprintf(2, "Error\nSphere diameter must be positive\n");
		free_all(prog);
	}
	parse_color(prog, &prog->scene->spheres->color, tokens[3]);
}
