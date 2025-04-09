#include "parser.h"
#include "libft/vector.h"

void	parse_cylinder(t_prog *prog, t_cylinder *cylinder, char **tokens)
{
	t_vec3	origin;
	t_vec3	normal;

	if (ft_arrlen(tokens) != 6)
		print_exit(prog, "Invalid cylinder format");
	parse_vector(prog, &origin, tokens[1]);
	cylinder->origin = origin;
	parse_vector(prog, &normal, tokens[2]);
	cylinder->normal = normal;
	cylinder->radius = check_atof(prog, tokens[3]);
	if (cylinder->radius <= 0)
		print_exit(prog, "Invalid cylinder diameter");
	cylinder->height = check_atof(prog, tokens[4]);
	if (cylinder->height <= 0)
		print_exit(prog, "Cylinder height must be positive");
	cylinder->material = default_mat();
	parse_color(prog, &cylinder->material.albedo, tokens[5]);
}

void	parse_plane(t_prog *prog, t_plane *plane, char **tokens)
{
	t_vec3	origin;
	t_vec3	normal;

	if (ft_arrlen(tokens) != 4)
		print_exit(prog, "Invalid plane format");
	parse_vector(prog, &origin, tokens[1]);
	parse_vector(prog, &normal, tokens[2]);
	plane->origin = origin;
	plane->normal = vec3_normalize(normal);
	plane->material = default_mat();
	parse_color(prog, &plane->material.albedo, tokens[3]);
}

void	parse_sphere(t_prog *prog, t_sphere *sphere, char **tokens)
{
	t_vec3	origin;

	if (ft_arrlen(tokens) != 4)
		print_exit(prog, "Invalid sphere format");
	parse_vector(prog, &origin, tokens[1]);
	sphere->origin = origin;
	sphere->radius = check_atof(prog, tokens[2]);
	if (sphere->radius <= 0)
		print_exit(prog, "Sphere diameter must be positive");
	sphere->material = default_mat();
	parse_color(prog, &sphere->material.albedo, tokens[3]);
}
