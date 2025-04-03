#include "window.h"
#include "libft/io.h"
#include "libft/memory.h"
#include "libft/string.h"
#include "libft/vector.h"
#include "miniRT.h"
#include "mlx.h"
#include <stdio.h>

void	print_cam(const t_camera *cam)
{
	ft_printf(GRAY "[LOG]: camera settings\n");
	ft_printf("\torigin:");
	print_vec(cam->origin);
	ft_printf("\tdirection:");
	print_vec(cam->direction);
	ft_printf("\tfov:%d%s\n\n", cam->fov, RESET);
}

int	key_hook(int keycode, t_prog *prog)
{
	t_camera	*camera;
	t_sphere	*sphere;

	camera = &prog->scene->camera;
	sphere = prog->scene->spheres;
	if (keycode == ESC)
		free_all(prog);
	else if (keycode == UP_ARR)
		camera->direction = vec3_add(camera->direction, new_vec3(0, -0.05, 0));
	else if (keycode == DOWN_ARR)
		camera->direction = vec3_add(camera->direction, new_vec3(0, 0.05, 0));
	else if (keycode == LEFT_ARR)
		camera->direction = vec3_add(camera->direction, new_vec3(0.05, 0, 0));
	else if (keycode == RIGHT_ARR)
		camera->direction = vec3_add(camera->direction, new_vec3(-0.05, 0, 0));

	else if (keycode == 'q')
		camera->origin = vec3_add(camera->origin, vec3_mult(camera->up, 0.5));
	else if (keycode == 'e')
		camera->origin = vec3_add(camera->origin, vec3_mult(camera->up, -0.5));
	else if (keycode == 'w')
		camera->origin = vec3_add(camera->origin, vec3_mult(camera->foward, -0.5));
	else if (keycode == 's')
		camera->origin = vec3_add(camera->origin, vec3_mult(camera->foward, 0.5));
	else if (keycode == 'a')
		camera->origin = vec3_add(camera->origin, vec3_mult(camera->right, -0.5));
	else if (keycode == 'd')
		camera->origin = vec3_add(camera->origin, vec3_mult(camera->right, 0.5));
	else if (keycode == 'z')
		camera->fov++;
	else if (keycode == 'x')
		camera->fov--;
	else
		return (0);
	run_pipeline(prog);
	return (0);
}

int	window_close(void *prog)
{
	free_all(prog);
	return (0);
}

void	init_win(t_prog *prog)
{
	t_win_scene	*win;

	prog->win_button->mlx_ptr = NULL;
	prog->win_button->win_ptr = NULL;
	win = prog->win_scene;
	ft_bzero(win, sizeof(t_win_scene));
	win->height = HEIGHT;
	win->width = WIDTH;
	win->mlx_ptr = mlx_init();
	if (!win->mlx_ptr)
		free_all(prog);
	mlx_do_key_autorepeaton(prog->win_scene->mlx_ptr);
	win->win_ptr = mlx_new_window(win->mlx_ptr, win->width,
			win->height, "miniRT");
	if (!win->win_ptr)
		free_all(prog);
	if (create_img(win) == -1)
		free_all(prog);
	mlx_hook(win->win_ptr, 17, 1L << 2, window_close, prog);
}
