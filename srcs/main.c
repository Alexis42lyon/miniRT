#include "window.h"
#include "parser.h"
#include "raytracer.h"
#include "libft/math.h"

#include <stdio.h>
#include <unistd.h>
#include "libft/vector.h"

int	main(int ac, char **av)
{
	t_prog			prog;
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
	prog.scene = &scene;
	prog.win_scene = &win_scene;
	prog.win_button = &win_button;
	ft_bzero(prog.win_scene, sizeof(t_win_scene));
	init(&prog, av);
	init_win(&prog);
	// start_renderer(&prog);
	free_all(&prog);
	return (0);
}
