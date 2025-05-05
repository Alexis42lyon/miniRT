/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:19:02 by abidolet          #+#    #+#             */
/*   Updated: 2025/05/05 16:37:12 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "window.h"
#include "parser.h"
#include "button.h"
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>

void	pre_check(void)
{
	if (SSAA_FACTOR != (int)SSAA_FACTOR || SSAA_FACTOR < 1)
		print_exit(NULL, "SSAA_FACTOR is invalid");
	if (DEFAULT_BOUNCE != (int)DEFAULT_BOUNCE || DEFAULT_BOUNCE < 1)
		print_exit(NULL, "DEFAULT_BOUNCE is invalid");
}

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
	pre_check();
	prog.parser = &parser;
	prog.scene = &scene;
	prog.win_scene = &win_scene;
	prog.win_button = &win_button;
	init(&prog, av[1]);
	init_win(&prog);
	free_all(&prog);
}
