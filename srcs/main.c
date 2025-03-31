#include "miniRT.h"
#include "mlx.h"
#include "window.h"

int	main(int ac, char **av)
{
	t_prog	prog;
	t_win	win;
	t_scene	scene;

	prog.scene = &scene;
	prog.win = &win;
	if (ac != 2)
	{
		print_error("Wrong number of arguments");
		return (1);
	}
	else if (!ft_strrchr(av[1], '.') || ft_strcmp(ft_strrchr(av[1], '.'), ".rt"))
	{
		print_error("File must have the .rt extension");
		return (1);
	}
	init(&prog, av);
	start_renderer(&prog);
	free_all(&prog);
	return (0);
}
