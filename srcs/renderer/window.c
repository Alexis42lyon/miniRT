#include "window.h"
#include "libft/io.h"
#include "libft/memory.h"
#include "libft/string.h"
#include "miniRT.h"
#include "mlx.h"
#include <stdio.h>

int	key_hook(int keycode, t_prog *prog)
{
	t_camera	*camera;
	t_sphere	*sphere;

	camera = &prog->scene->camera;
	sphere = prog->scene->spheres;
	if (keycode == ESC)
		free_all(prog);
	else if (keycode == 'q')
		camera->origin = vec3_add(camera->origin, new_vec3(0, 0, 4));
	else if (keycode == 'e')
		camera->origin = vec3_add(camera->origin, new_vec3(0, 0, -4));
	else if (keycode == 'w')
		camera->origin = vec3_add(camera->origin, new_vec3(0, 0.4, 0));
	else if (keycode == 's')
		camera->origin = vec3_add(camera->origin, new_vec3(0, -0.4, 0));
	else if (keycode == 'a')
		camera->origin = vec3_add(camera->origin, new_vec3(-0.4, 0, 0));
	else if (keycode == 'd')
		camera->origin = vec3_add(camera->origin, new_vec3(0.4, 0, 0));
	else if (keycode == 'z')
		camera->fov++;
	else if (keycode == 'x')
		camera->fov--;
	else
		return (0);
	render(prog->win, prog->scene);
	return (0);
}

int	window_close(void *prog)
{
	free_all(prog);
	return (0);
}

void	init_win(t_prog *prog)
{
	t_win	*win;

	win = prog->win;
	ft_bzero(win, sizeof(t_win));
	win->height = HEIGHT;
	win->width = WIDTH;
	win->name = ft_strdup("miniRT");
	if (malloc_assert(win->name, __FILE__, __LINE__))
		free_all(prog);
	win->mlx_ptr = mlx_init();
	if (!win->mlx_ptr)
		free_all(prog);
	win->win_ptr = mlx_new_window(win->mlx_ptr, win->width,
			win->height, win->name);
	if (!win->win_ptr)
		free_all(prog);
	if (create_img(win) == -1)
		free_all(prog);
	win->button_x = 0;
	win->button_y = 0;
	win->button_width = 100;
	win->button_height = 50;
	mlx_hook(win->win_ptr, 17, 1L << 2, window_close, prog);
	mlx_mouse_hook(win->win_ptr, mouse_click, win);
}
