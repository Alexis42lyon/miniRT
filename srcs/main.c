/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:19:02 by abidolet          #+#    #+#             */
/*   Updated: 2025/04/18 00:01:41 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "window.h"
#include "parser.h"
#include "raytracer.h"
#include "libft/math.h"

#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include "libft/vector.h"

#include <sys/wait.h>

void	create_mat(t_mat mats[MAX_MAT])
{
	mats[0] = default_mat();

	mats[1].albedo = (t_vec3){0.5, 0.5, 0.5};
	mats[1].emission_power = 0;
	mats[1].roughtness = 0.03f;
	mats[1].shyniness = 256;
	mats[1].spec_coef = 0.8f;
	mats[1].use_checker = 0;

	mats[3].albedo = (t_vec3){1, 0, 0};
	mats[3].emission_power = 5;
	mats[3].roughtness = 0.5f;
	mats[3].shyniness = 32;
	mats[3].spec_coef = 0.6f;
	mats[3].use_checker = 0;

	mats[2].albedo = (t_vec3){1, 0.3, 0.1};
	mats[2].emission_power = 0;
	mats[2].roughtness = 1.0f;
	mats[2].shyniness = 12;
	mats[2].spec_coef = 0.8f;
	mats[2].use_checker = 0;

	mats[4].albedo = (t_vec3){0.0, 1, 0.5};
	mats[4].emission_power = 0;
	mats[4].roughtness = 0.1f;
	mats[4].shyniness = 256;
	mats[4].spec_coef = 0.9f;
	mats[4].use_checker = 0;
}

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
	// create_mat(scene.materials);
	init_win(&prog);
	free_all(&prog);
	return (0);
}
