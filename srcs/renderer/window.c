/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:18:24 by mjuncker          #+#    #+#             */
/*   Updated: 2025/05/07 08:58:06 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

void	reload(t_prog *prog)
{
	free_scene(prog);
	init(prog, NULL);
	reset_accumulation(prog);
}

int	key_hook2(int keycode, t_camera	*camera)
{
	if (keycode == LSHIFT)
		camera->origin = vec3_add(camera->origin, vec3_mult(camera->up, -0.5));
	else if (keycode == SPACE)
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
	else if (keycode == 'l')
		reload(prog);
	else if (key_hook2(keycode, camera))
		return (0);
	print_cam(&prog->scene->camera);
	reset_accumulation(prog);
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
	mlx_loop(win->mlx_ptr);
}
