#include <fcntl.h>
#include "parser.h"

void	init(t_prog *prog, char **av)
{
	static char	**av2 = NULL;

	if (!av2)
		av2 = av;
	check_mem((t_info){__FILE__, __LINE__, __func__},
		ft_calloc(sizeof(t_scene), 1), (void **)&prog->scene, NULL);
	prog->scene->fd = open(av2[1], O_RDONLY);
	if (prog->scene->fd == -1)
		print_exit(prog, "File not found or cannot access to the file");
	parse(prog);
	prog->scene->frame_count = 1;
	print_scene(prog->scene);
	ft_printf("%sNo error has been found\n%s", GREEN, RESET);
}
