/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:33:51 by mjuncker          #+#    #+#             */
/*   Updated: 2025/04/14 16:34:20 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "libft/io.h"
#include "miniRT.h"
#include "raytracer.h"
#include "window.h"
#include "parser.h"

int mouse_down(int button, int x, int y, t_prog *prog)
{
	(void)x;
	(void)y;
	if (button == 4)
	{
		prog->scene->camera.fov += 5;
		reset_accumulation(prog);
	}
	if (button == 5)
	{
		prog->scene->camera.fov -= 5;
		reset_accumulation(prog);
	}
	prog->scene->camera.fov = ft_clamp(prog->scene->camera.fov, 0, 180);
	if (button == 3)
	{
		mlx_mouse_move(prog->win_scene->mlx_ptr, prog->win_scene->win_ptr, WIDTH / 2, HEIGHT / 2);
		mlx_mouse_hide(prog->win_scene->mlx_ptr, prog->win_scene->win_ptr);
		mlx_mouse_get_pos(prog->win_scene->mlx_ptr, prog->win_scene->win_ptr, &prog->scene->camera.last_x, &prog->scene->camera.last_y);
		prog->scene->camera.movement_enable = 1;
		prog->scene->nb_bounces = 1;
		ft_printf(CYAN BOLD "[LOG]:" RESET CYAN "camera rotation enable\n");
	}
	return (0);
}
int mouse_up(int button, int x, int y, t_prog *prog)
{
	(void)x;
	(void)y;
	if (button == 3)
	{
		mlx_mouse_show(prog->win_scene->mlx_ptr, prog->win_scene->win_ptr);
		prog->scene->nb_bounces = DEFAULT_BOUNCE;
		prog->scene->camera.movement_enable = 0;
		ft_printf(CYAN BOLD "[LOG]:" RESET CYAN "camera rotation disable\n");
	}
	return (0);
}

int key_down(int keycode, t_prog *prog)
{
	if (keycode == '1')
		prog->scene->vp_flags ^= DIFFUSE;
	else if (keycode == '2')
		prog->scene->vp_flags ^= AMBIENT;
	else if (keycode == '3')
		prog->scene->vp_flags ^= SPECULAR;
	else if (keycode == '4')
		prog->scene->vp_flags ^= NORMAL;
	else if (keycode == 'w')
		prog->scene->camera.movekeys |= MOVE_FORWARD;
	else if (keycode == 'a')
		prog->scene->camera.movekeys |= MOVE_LEFT;
	else if (keycode == 's')
		prog->scene->camera.movekeys |= MOVE_BACKWARD;
	else if (keycode == 'd')
		prog->scene->camera.movekeys |= MOVE_RIGHT;
	else if (keycode == SPACE)
		prog->scene->camera.movekeys |= MOVE_UP;
	else if (keycode == LSHIFT)
		prog->scene->camera.movekeys |= MOVE_DOWN;
	else if (keycode == ESC)
		free_all(prog);
	else if (keycode == 'r')
	{
		reset_cam_orientation(&prog->scene->camera);
		reset_accumulation(prog);
	}
	else if (keycode == 'c')
		print_cam(&prog->scene->camera);
	else if (keycode == 'x')
		print_scene(prog->scene);
	reset_accumulation(prog);
	return (0);
}

int key_up(int keycode, t_prog *prog)
{
	if (keycode == 'w')
		prog->scene->camera.movekeys ^= MOVE_FORWARD;
	else if (keycode == 'a')
		prog->scene->camera.movekeys ^= MOVE_LEFT;
	else if (keycode == 's')
		prog->scene->camera.movekeys ^= MOVE_BACKWARD;
	else if (keycode == 'd')
		prog->scene->camera.movekeys ^= MOVE_RIGHT;
	else if (keycode == SPACE)
		prog->scene->camera.movekeys ^= MOVE_UP;
	else if (keycode == LSHIFT)
		prog->scene->camera.movekeys ^= MOVE_DOWN;
	return (0);
}
