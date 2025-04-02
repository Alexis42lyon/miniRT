#ifndef PARSER_H
# define PARSER_H

# include "miniRT.h"

void	init(t_prog *prog, char **av);

// parse.c
void	parse(t_prog *prog);
void	parse_sphere(t_prog *prog, t_sphere *sphere, char **tokens);
void	parse_plane(t_prog *prog, t_plane *plane, char **tokens);
void	parse_cylinder(t_prog *prog, t_cylinder *cylinder, char **tokens);

// parse_utils.c
void	parse_vector(t_prog *prog, t_vec3 *vec, char *str);
void	parse_color(t_prog *prog, t_vec3 *color, char *str);
bool	is_normalized(t_vec3 vec);
void	init_malloc(t_prog *prog);
void	print_scene(const t_scene *scene);

#endif
