/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:19:02 by abidolet          #+#    #+#             */
/*   Updated: 2025/05/06 15:24:10 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include "parser.h"
#include "raytracer.h"
#include "libft/math.h"

#include <stdio.h>
#include <unistd.h>
#include "libft/vector.h"

#include <sys/wait.h>

int	main(int ac, char **av)
{
	t_prog			prog;
	t_parser		parser;
	t_scene			scene;
	t_win_scene		win_scene;

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
	ft_bzero(prog.win_scene, sizeof(t_win_scene));
	init(&prog, av);
	init_win(&prog);
	free_all(&prog);
	return (0);
}
