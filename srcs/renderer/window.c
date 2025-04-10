#include "window.h"
#include "libft/io.h"
#include "libft/memory.h"
#include "libft/string.h"
#include "libft/vector.h"
#include "miniRT.h"
#include "mlx.h"
#include <stdio.h>
#include <math.h>

void	print_cam(const t_camera *cam)
{
	ft_printf(GRAY "\n[LOG]: camera settings\n");
	ft_printf("\torigin:");
	print_vec(cam->origin);
	ft_printf("\tfoward:");
	print_vec(cam->forward);
	ft_printf("\tright:");
	print_vec(cam->right);
	ft_printf("\tup:");
	print_vec(cam->up);
	ft_printf("\tfov:%d%s\n", cam->fov, RESET);
}

void	turn_yaw(t_camera *cam, float radian)
{
	t_vec3	new_forward;
	t_vec3	new_right;

	new_forward = vec3_add(
		vec3_mult(cam->forward, cosf(radian)),
		vec3_mult(cam->right, sinf(radian))
	);

	new_right = vec3_add(
		vec3_mult(vec3_mult(cam->forward, -1), sinf(radian)),
		vec3_mult(cam->right, cosf(radian))
	);

	cam->forward = vec3_normalize(new_forward);
	cam->right = vec3_normalize(new_right);
	cam->up = vec3_normalize(vec3_cross(cam->right, cam->forward));

}

void	turn_pitch(t_camera *cam, float radian)
{
	t_vec3	new_forward;
	t_vec3	new_up;

	new_forward = vec3_add(
		vec3_mult(cam->forward, cosf(radian)),
		vec3_mult(cam->up, -sinf(radian))
	);

	new_up = vec3_add(
		vec3_mult(cam->forward, sinf(radian)),
		vec3_mult(cam->up, cosf(radian))
	);

	cam->forward = vec3_normalize(new_forward);
	cam->up = vec3_normalize(new_up);
	cam->right = vec3_normalize(vec3_cross(cam->forward, cam->up));

}

int	key_hook(int keycode, t_prog *prog)
{
	t_camera	*camera;

	camera = &prog->scene->camera;
	if (keycode == ESC)
		free_all(prog);
	else if (keycode == UP_ARR)
		turn_pitch(camera, 10 * (3.1415 / 180.0f));
	else if (keycode == DOWN_ARR)
		turn_pitch(camera, -10 * (3.1415 / 180.0f));
	else if (keycode == LEFT_ARR)
		turn_yaw(camera, -10 * (3.1415 / 180.0f));
	else if (keycode == RIGHT_ARR)
		turn_yaw(camera, 10 * (3.1415 / 180.0f));
	else if (keycode == 'q')
		camera->origin = vec3_add(camera->origin, vec3_mult(camera->up, -0.5));
	else if (keycode == 'e')
		camera->origin = vec3_add(camera->origin, vec3_mult(camera->up, 0.5));
	else if (keycode == 'w')
		camera->origin = vec3_add(camera->origin,
				vec3_mult(camera->forward, 0.5));
	else if (keycode == 's')
		camera->origin = vec3_add(camera->origin,
				vec3_mult(camera->forward, -0.5));
	else if (keycode == 'a')
		camera->origin = vec3_add(camera->origin,
				vec3_mult(camera->right, -0.5));
	else if (keycode == 'd')
		camera->origin = vec3_add(camera->origin,
				vec3_mult(camera->right, 0.5));
	else if (keycode == 'z')
		camera->fov++;
	else if (keycode == 'x')
		camera->fov--;
	else
		return (0);
	ft_bzero(prog->win_scene->accumulation_data,
		prog->win_scene->height * prog->win_scene->width * sizeof(t_vec3));
	prog->scene->frame_count = 1;
	prog->scene->total_render_time = 0;
	prog->scene->max_render_time = -1;
	prog->scene->min_render_time = -1;
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
	win->aspect_ratio = (float)WIDTH / (float)HEIGHT;
	printf("%f", win->aspect_ratio);
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
	mlx_loop_hook(prog->win_scene->mlx_ptr, new_frame, prog);
	mlx_hook(win->win_ptr, 17, 1L << 2, window_close, prog);
	check_mem((t_info){__FILE__, __LINE__, __func__},
		ft_calloc(win->height * win->width, sizeof(t_vec3)),
		(void **)&win->accumulation_data, prog);

	mlx_key_hook(win->win_ptr, key_hook, prog);
	if (win->mlx_ptr == NULL)
		return ;
	init_button_window(prog);
	mlx_loop(win->mlx_ptr);
}
