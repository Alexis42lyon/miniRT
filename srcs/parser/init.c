/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 10:22:15 by abidolet          #+#    #+#             */
/*   Updated: 2025/04/11 11:29:26 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "parser.h"
#include "window.h"

void	switch_identifier(t_prog *prog, t_parser *parser)
{
	if (!ft_strcmp(parser->tokens[0], "A") && parser->ambient_is_set)
		print_exit(prog, "Ambient light can only be declared once");
	else if (!ft_strcmp(parser->tokens[0], "A"))
		parser->ambient_is_set = true;
	else if (!ft_strcmp(parser->tokens[0], "C"))
	{
		if (parser->camera_is_set)
			print_exit(prog, "Camera can only be declared once");
		parser->camera_is_set = true;
	}
	else if (!ft_strcmp(parser->tokens[0], "L"))
	{
		if (parser->light_is_set)
			print_exit(prog, "Light can only be declared once");
		parser->light_is_set = true;
	}
	else if (!ft_strcmp(parser->tokens[0], "sp"))
		prog->scene->nb_spheres++;
	else if (!ft_strcmp(parser->tokens[0], "pl"))
		prog->scene->nb_planes++;
	else if (!ft_strcmp(parser->tokens[0], "cy"))
		prog->scene->nb_cylinders++;
	else if (parser->tokens[0])
		print_exit(prog, "Invalid identifier");
}

void	parse_map(t_prog *prog)
{
	t_parser	*parser;
	t_list		*new_node;

	parser = prog->parser;
	parser->line = ft_get_next_line(parser->fd);
	while (parser->line)
	{
		if (ft_strchr(parser->line, '\n'))
			parser->line[ft_strlen(parser->line) - 1] = '\0';
		check_mem((t_info){__FILE__, __LINE__, __func__},
			ft_split(parser->line, ' '),
			(void **)&parser->tokens, prog);
		switch_identifier(prog, parser);
		check_mem((t_info){__FILE__, __LINE__, __func__},
			ft_lstnew(parser->tokens), (void **)&new_node, prog);
		ft_lstadd_back(&parser->map, new_node);
		free(parser->line);
		parser->line = ft_get_next_line(parser->fd);
	}
	parser->tokens = NULL;
	if (parser->ambient_is_set == false
		|| parser->camera_is_set == false
		|| parser->light_is_set == false)
		print_exit(prog, "Missing mandatory elements");
}

void	init(t_prog *prog, char **av)
{
	ft_bzero(prog->parser, sizeof(t_parser));
	ft_bzero(prog->scene, sizeof(t_scene));
	ft_bzero(prog->win_scene, sizeof(t_win_scene));
	ft_bzero(prog->win_button, sizeof(t_win_button));
	prog->scene->camera.right = (t_vec3){1, 0, 0};
	prog->scene->camera.up = (t_vec3){0, 1, 0};
	prog->parser->fd = open(av[1], O_RDONLY);
	if (prog->parser->fd == -1)
		print_exit(prog, "File not found or cannot access to the file");
	parse_map(prog);
	check_mem((t_info){__FILE__, __LINE__, __func__},
		malloc(sizeof(t_sphere) * (prog->scene->nb_spheres + 1)),
		(void **)&prog->scene->spheres, prog);
	check_mem((t_info){__FILE__, __LINE__, __func__},
		malloc(sizeof(t_plane) * (prog->scene->nb_planes + 1)),
		(void **)&prog->scene->planes, prog);
	check_mem((t_info){__FILE__, __LINE__, __func__},
		malloc(sizeof(t_cylinder) * (prog->scene->nb_cylinders + 1)),
		(void **)&prog->scene->cylinders, prog);
	parse(prog);
	prog->scene->frame_count = 1;
	print_scene(prog->scene);
	ft_printf("%sNo error has been found\n%s", GREEN, RESET);
}
