/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:42:03 by abidolet          #+#    #+#             */
/*   Updated: 2025/04/23 14:25:53 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "miniRT.h"

# define MATERIAL_FILE "scenes/material.rt"
# define SHOW_SRUCT 1

typedef struct s_parser
{
	int			fd;
	char		*line;
	char		**tokens;
	bool		ambient_is_set;
	bool		camera_is_set;
	int			i_light;
	int			i_sphere;
	int			i_plane;
	int			i_cylinder;
	int			i_cone;
	t_list		*map;
	bool		is_free;

	int			fd_mat;
	size_t		nb_id;
	t_list		*mat_chained;
}	t_parser;

void	init(t_prog *prog, char *file);

// parse.c
void	parse(t_prog *prog, t_parser *parser, t_scene *scene, t_list *current);

// parse_objects.c
void	parse_sphere(t_prog *prog, t_sphere *sphere, char **tokens);
void	parse_plane(t_prog *prog, t_plane *plane, char **tokens);
void	parse_cylinder(t_prog *prog, t_cylinder *cylinder, char **tokens);

// parse_utils.c
void	parse_vector(t_prog *prog, t_vec3 *vec, char *str);
void	parse_color(t_prog *prog, t_vec3 *color, char *str);
double	check_atof(t_prog *prog, const char *nptr);

// parse_albedo.c
void	parse_material(t_prog *prog, t_parser *parser);

// print_struct.c
void	print_scene(const t_scene *scene);

// print_struct_utils.c
void	print_spheres(const t_scene *scene);
void	print_planes(const t_scene *scene);
void	print_cylinders(const t_scene *scene);
void	print_cones(const t_scene *scene);

int	find_material_index(t_prog *prog, char *material_name);

// renderer/colors.c
t_uint	vec_to_int(const t_vec3 color);

#endif
