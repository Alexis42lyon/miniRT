/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:19:02 by abidolet          #+#    #+#             */
/*   Updated: 2025/04/22 12:15:13 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "window.h"
#include "parser.h"
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>

int	main(int ac, char **av)
{
	t_prog			prog;
	t_parser		parser;
	t_scene			scene;
	t_win_scene		win_scene;
	t_win_button	win_button;

	if (ac != 2)
	{
		print_error("Wrong number of arguments");
		return (1);
	}
	else if (!ft_strrchr(av[1], '.')
		|| ft_strcmp(ft_strrchr(av[1], '.'), ".rt"))
	{
		print_error("File must have the .rt extension");
		return (1);
	}
	prog.parser = &parser;
	prog.scene = &scene;
	prog.win_scene = &win_scene;
	prog.win_button = &win_button;
	init(&prog, av[1]);
	prog.scene->bump_map = ppm_image("./assets/earthnormal.ppm", &prog);
	prog.scene->texture = ppm_image("./assets/earth.ppm", &prog);
	init_win(&prog);
	free_all(&prog);
	return (0);
}
