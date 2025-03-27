#include "miniRT.h"
#include "mlx.h"
#include "window.h"

int	main(int ac, char **av)
{
	t_prog	prog;

	if (ac != 2)
	{
		ft_dprintf(2, "%sError\n%s\n%s",
			RED, "Wrong number of arguments", RESET);
		return (1);
	}
	init(&prog, av);
	// start_renderer(&prog);
	free_all(&prog);
	return (0);
}
