#include "mlx.h"
#include "window.h"
#include "miniRT.h"
#include "parser.h"
#include <stdio.h>

void	session_result(const t_scene *scene)
{
	printf(CYAN "\n\n-------------------------\nsession result:\n");
	printf(CYAN "\n[render times]:\n");
	printf(GRAY "\taverage:%ums    ",
		scene->total_render_time / (scene->frame_count - 1));
	printf(GRAY "min:%ums    ", scene->min_render_time);
	printf(GRAY "max:%ums\n", scene->max_render_time);
	printf(CYAN "\n[accumulation data]\n");
	printf(GRAY "\ttotal-render-time:%ums\n", scene->total_render_time);
	printf(GRAY "\ttotal-frame-count:%u\n", scene->frame_count);
	printf(CYAN "\n-------------------------\n\n");
}

void	free_arr(void **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	print_exit(t_prog *prog, char *str)
{
	print_error(str);
	free_all(prog);
}

void	free_win_scene(t_win_scene *win)
{
	if (win->img.img)
		mlx_destroy_image(win->mlx_ptr, win->img.img);
	if (win->win_ptr)
		mlx_destroy_window(win->mlx_ptr, win->win_ptr);
	if (win->mlx_ptr)
	{
		mlx_destroy_display(win->mlx_ptr);
		free(win->mlx_ptr);
	}
	free(win->accumulation_data);
}

void	free_parser(t_parser *parser)
{
	if (parser->fd > 0)
		close(parser->fd);
	free(parser->line);
	free_arr((void **)parser->tokens);
	ft_lstclear(&parser->map, (void *)free_arr);
	free(parser);
}

void	free_all(t_prog *prog)
{
	free(prog->scene->spheres);
	free(prog->scene->planes);
	free(prog->scene->cylinders);
	// session_result(prog->scene);
	free_parser(prog->parser);
	if (prog->win_button->win_ptr)
		mlx_destroy_window(prog->win_button->mlx_ptr,
			prog->win_button->win_ptr);
	free_win_scene(prog->win_scene);
	exit(0);
}

void	check_mem(t_info info, void *mem, void **res, t_prog *prog)
{
	if (mem == NULL)
	{
		ft_dprintf(2, "%s%s:%d: %smalloc assertion failed in %s'%s'\n",
			GRAY, info.file, info.line, RED, RESET, info.function);
		if (prog)
			free_all(prog);
		else
			exit(1);
	}
	*res = mem;
}
