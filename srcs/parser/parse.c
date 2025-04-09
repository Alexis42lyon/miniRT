#include "parser.h"

static void	parse_light(t_prog *prog, char **tokens)
{
	t_vec3	origin;

	if (ft_arrlen(tokens) != 4)
		print_exit(prog, "Invalid light format");
	parse_vector(prog, &origin, tokens[1]);
	prog->scene->light.origin = origin;
	prog->scene->light.ratio = check_atof(prog, tokens[2]);
	if (prog->scene->light.ratio < 0.0 || prog->scene->light.ratio > 1.0)
		print_exit(prog, "Light brightness must be in range [0.0, 1.0]");
	parse_color(prog, &prog->scene->light.material.albedo, tokens[3]);
}

static void	parse_camera(t_prog *prog, char **tokens)
{
	t_vec3	origin;
	t_vec3	direction;

	if (ft_arrlen(tokens) != 4)
		print_exit(prog, "Invalid camera format");
	parse_vector(prog, &origin, tokens[1]);
	prog->scene->camera.origin = origin;
	parse_vector(prog, &direction, tokens[2]);
	prog->scene->camera.direction = direction;
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

void	parse_map(t_prog *prog)
{
	t_list	*new_node;

	prog->scene->line = ft_get_next_line(prog->scene->fd);
	while (prog->scene->line)
	{
		if (ft_strchr(prog->scene->line, '\n'))
			prog->scene->line[ft_strlen(prog->scene->line) - 1] = '\0';
		check_mem((t_info){__FILE__, __LINE__, __func__},
			ft_split(prog->scene->line, ' '),
			(void **)&prog->scene->tokens, prog);
		if (!ft_strcmp(prog->scene->tokens[0], "A"))
		{
			if (prog->scene->ambient_light.is_set)
				print_exit(prog, "Ambient light can only be declared once");
			prog->scene->ambient_light.is_set = true;
		}
		else if (!ft_strcmp(prog->scene->tokens[0], "C"))
		{
			if (prog->scene->camera.is_set)
				print_exit(prog, "Camera can only be declared once");
			prog->scene->camera.is_set = true;
		}
		else if (!ft_strcmp(prog->scene->tokens[0], "L"))
		{
			if (prog->scene->light.is_set)
				print_exit(prog, "Light can only be declared once");
			prog->scene->light.is_set = true;
		}
		else if (!ft_strcmp(prog->scene->tokens[0], "sp"))
			prog->scene->nb_spheres++;
		else if (!ft_strcmp(prog->scene->tokens[0], "pl"))
			prog->scene->nb_planes++;
		else if (!ft_strcmp(prog->scene->tokens[0], "cy"))
			prog->scene->nb_cylinders++;
		else if (prog->scene->tokens[0])
			print_exit(prog, "Invalid identifier");
		check_mem((t_info){__FILE__, __LINE__, __func__},
			ft_lstnew(prog->scene->tokens), (void **)&new_node, prog);
		ft_lstadd_back(&prog->scene->map, new_node);
		free(prog->scene->line);
		prog->scene->line = ft_get_next_line(prog->scene->fd);
	}
	prog->scene->tokens = NULL;
	if (prog->scene->ambient_light.is_set == false
		|| prog->scene->camera.is_set == false
		|| prog->scene->light.is_set == false)
		print_exit(prog, "Missing mandatory elements");
}

void	parse(t_prog *prog)
{
	t_list	*current;
	char	**tokens;
	int		i_sphere;
	int		i_plane;
	int		i_cylinder;

	parse_map(prog);
	init_malloc(prog);
	i_cylinder = 0;
	i_sphere = 0;
	i_plane = 0;
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
			parse_sphere(prog, prog->scene->spheres + i_sphere++, tokens);
		else if (!ft_strcmp(tokens[0], "pl"))
			parse_plane(prog, prog->scene->planes + i_plane++, tokens);
		else if (!ft_strcmp(tokens[0], "cy"))
			parse_cylinder(prog, prog->scene->cylinders + i_cylinder++, tokens);
		current = current->next;
	}
}
