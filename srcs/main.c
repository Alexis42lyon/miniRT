/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:19:02 by abidolet          #+#    #+#             */
/*   Updated: 2025/04/18 08:41:54 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
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
	// ppm_image("/home/mjuncker/github/Milestone04/miniRT/assets/map.ppm", &prog);
	// return (0);
	init_win(&prog);
	free_all(&prog);
	return (0);
}
