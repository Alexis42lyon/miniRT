/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:19:02 by abidolet          #+#    #+#             */
/*   Updated: 2025/05/06 14:03:40 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture_bonus.h"
#include "window_bonus.h"
#include "parser_bonus.h"
#include "button.h"
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
		print_exit(NULL, "Wrong number of arguments");
	else if (!ft_strrchr(av[1], '.')
		|| ft_strcmp(ft_strrchr(av[1], '.'), ".rt"))
		print_exit(NULL, "File must have the .rt extension");
	prog.parser = &parser;
	prog.scene = &scene;
	prog.win_scene = &win_scene;
	prog.win_button = &win_button;
	init(&prog, av[1]);
	init_win(&prog);
	free_all(&prog);
}
