/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:18:24 by mjuncker          #+#    #+#             */
/*   Updated: 2025/04/12 12:22:03 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include "libft/io.h"
#include "libft/memory.h"
#include "libft/string.h"
#include "libft/vector.h"
#include "miniRT.h"
#include "mlx.h"
#include <stdio.h>
#include <math.h>

int	key_hook2(int keycode, t_camera	*camera)
{
	if (keycode == 'q')
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
	else if (keycode == 'r')
		reset_cam_orientation(camera);
	else if (keycode == 'c')
		print_cam(camera);
	else
		return (1);
	return (0);
}

int	key_hook(int keycode, t_prog *prog)
{
	t_camera	*camera;

	camera = &prog->scene->camera;
	if (keycode == ESC)
		free_all(prog);
	else if (keycode == UP_ARR)
		turn_pitch(camera, -10 * (3.1415 / 180.0f));
	else if (keycode == DOWN_ARR)
		turn_pitch(camera, 10 * (3.1415 / 180.0f));
	else if (keycode == LEFT_ARR)
		turn_yaw(camera, -10 * (3.1415 / 180.0f));
	else if (keycode == RIGHT_ARR)
		turn_yaw(camera, 10 * (3.1415 / 180.0f));
	else if (keycode == PAGE_UP)
		turn_roll(camera, -10 * (3.1415 / 180.0f));
	else if (keycode == PAGE_DOWN)
		turn_roll(camera, 10 * (3.1415 / 180.0f));
	else if (key_hook2(keycode, camera))
		return (0);
	reset_accumulation(prog);
	return (0);
}

int	window_close(void *prog)
{
	free_all(prog);
	return (0);
}

int pressed(int button, int x, int y, t_prog *prog)
{
	if (button == 3)
	{
		prog->scene->camera.last_x = x;
		prog->scene->camera.last_y = y;
		prog->scene->camera.rotation_enable = !prog->scene->camera.rotation_enable;
		printf(CYAN BOLD "[LOG]: " RESET CYAN "camera rotation enable\n");
	}
	return (0);
}
int released(int button, int x, int y, t_prog *prog)
{
	if (button == 3)
	{
		prog->scene->camera.last_x = x;
		prog->scene->camera.last_y = y;
		prog->scene->camera.rotation_enable = !prog->scene->camera.rotation_enable;
		printf(CYAN BOLD "[LOG]: " RESET CYAN "camera rotation disable\n");
	}
	return (0);
}

int mouse_input(int button, int x, int y, t_prog *prog)
{
	(void)button;
	(void)prog;
// mlx_mouse_get_pos(prog->win_scene->mlx_ptr, prog->win_scene->win_ptr, &m_x, &m_y);
	// printf("x: %d | y: %d | b: %d\n", x, y, button);
	if (button == 3)
	{
		prog->scene->camera.last_x = x;
		prog->scene->camera.last_y = y;
		prog->scene->camera.rotation_enable = !prog->scene->camera.rotation_enable;
		if (prog->scene->camera.rotation_enable)
			printf(CYAN BOLD "[LOG]: " RESET CYAN "camera rotation enable\n");
		else
			printf(CYAN BOLD "[LOG]: " RESET CYAN "camera rotation disable\n");

	}
	return (0);
}

void	init_win(t_prog *prog)
{
	t_win_scene	*win;

	win = prog->win_scene;
	win->height = HEIGHT;
	win->width = WIDTH;
	win->aspect_ratio = (float)WIDTH / (float)HEIGHT;
	win->mlx_ptr = mlx_init();
	if (!win->mlx_ptr)
		print_exit(prog, "Mlx init failed");
	mlx_do_key_autorepeaton(prog->win_scene->mlx_ptr);
	win->win_ptr = mlx_new_window(win->mlx_ptr, win->width,
			win->height, "miniRT");
	if (!win->win_ptr)
		print_exit(prog, "Mlx new_window failed");
	if (create_img(win) == -1)
		print_exit(prog, "Mlx create img failed");
	mlx_loop_hook(prog->win_scene->mlx_ptr, new_frame, prog);
	mlx_hook(win->win_ptr, 17, 1L << 2, window_close, prog);
	check_mem((t_info){__FILE__, __LINE__, __func__},
		ft_calloc(win->height * win->width, sizeof(t_vec3)),
		(void **)&win->accumulation_data, prog);
	mlx_key_hook(win->win_ptr, key_hook, prog);
	// mlx_mouse_hook(win->win_ptr, mouse_input, prog);
	init_button_window(prog);
	mlx_hook(win->win_ptr, 4, (1L<<2), pressed, prog);
	mlx_hook(win->win_ptr, 5, (1L<<3), released, prog);
	mlx_loop(win->mlx_ptr);
}
