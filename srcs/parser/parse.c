#include "parser.h"
#include "camera.h"

static void	parse_light(t_prog *prog, char **tokens)
{
	if (ft_arrlen(tokens) != 4)
		print_exit(prog, "Invalid light format");
	parse_vector(prog, &prog->scene->light.origin, tokens[1]);
	prog->scene->light.ratio = check_atof(prog, tokens[2]);
	if (prog->scene->light.ratio < 0.0 || prog->scene->light.ratio > 1.0)
		print_exit(prog, "Light brightness must be in range [0.0, 1.0]");
	parse_color(prog, &prog->scene->light.material.albedo, tokens[3]);
}

static void	parse_camera(t_prog *prog, char **tokens)
{
	if (ft_arrlen(tokens) != 4)
		print_exit(prog, "Invalid camera format");
	parse_vector(prog, &prog->scene->camera.origin, tokens[1]);
	parse_vector(prog, &prog->scene->camera.forward, tokens[2]);
	prog->scene->camera.forward = vec3_normalize(prog->scene->camera.forward);
	prog->scene->camera.right = (t_vec3){1, 0, 0};
	prog->scene->camera.up = (t_vec3){0, 1, 0};
	prog->scene->camera.fov = check_atof(prog, tokens[3]);
	if (prog->scene->camera.fov < 0 || prog->scene->camera.fov > 180)
		print_exit(prog, "FOV must be in range [0, 180]");
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

void	parse(t_prog *prog)
{
	t_parser	*parser;
	t_list		*current;
	char		**tokens;

	parser = prog->parser;
	current = parser->map;
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
			parse_sphere(prog, prog->scene->spheres + parser->i_sphere++, tokens);
		else if (!ft_strcmp(tokens[0], "pl"))
			parse_plane(prog, prog->scene->planes + parser->i_plane++, tokens);
		else if (!ft_strcmp(tokens[0], "cy"))
			parse_cylinder(prog, prog->scene->cylinders + parser->i_cylinder++, tokens);
		current = current->next;
	}
}
