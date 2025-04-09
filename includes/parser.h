#ifndef PARSER_H
# define PARSER_H

# include "miniRT.h"

typedef struct s_parser
{
	int				fd;
	char			*line;
	char			**tokens;
	bool 			ambient_is_set;
	bool			camera_is_set;
	bool			light_is_set;
	t_list			*map;
}	t_parser;

void	init(t_prog *prog, char **av);

// parse.c
void	parse(t_prog *prog);
void	parse_sphere(t_prog *prog, t_sphere *sphere, char **tokens);
void	parse_plane(t_prog *prog, t_plane *plane, char **tokens);
void	parse_cylinder(t_prog *prog, t_cylinder *cylinder, char **tokens);

// parse_utils.c
void	parse_vector(t_prog *prog, t_vec3 *vec, char *str);
void	parse_color(t_prog *prog, t_vec3 *color, char *str);
void	init_malloc(t_prog *prog);
void	print_scene(const t_scene *scene);
double	check_atof(t_prog *prog, const char *nptr);

#endif
