/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:33:51 by mjuncker          #+#    #+#             */
/*   Updated: 2025/05/01 13:35:30 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "libft/io.h"
#include "miniRT.h"
#include "raytracer.h"
#include "window.h"
#include "parser.h"
#include "texture.h"

int	toggle_flag(int to_check, const int *options, const int *flags, t_uint *flag);

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
		mlx_mouse_get_pos(prog->win_scene->mlx_ptr, prog->win_scene->win_ptr, &prog->scene->camera.last_x, &prog->scene->camera.last_y);
		prog->scene->camera.movement_enable = 1;
		prog->scene->nb_bounces = 1;
		ft_log(LOG, "camera rotation enable");
	}
	return (0);
}
int mouse_up(int button, int x, int y, t_prog *prog)
{
	(void)x;
	(void)y;
	if (button == 3)
	{
		prog->scene->nb_bounces = DEFAULT_BOUNCE;
		prog->scene->camera.movement_enable = 0;
		ft_log(LOG, "camera rotation disable");
	}
	return (0);
}

int	toggle_effects(int keycode, t_prog *prog)
{
	const int	options[] = {'1', '2', '3', '4', '5', 0};
	const int	flags[] = {INVERT, PIXEL, CHROMA, DEPTH_OF_FIELD};

	return (toggle_flag(keycode, &options[0], &flags[0], &prog->win_scene->img_flags));
}

int	toggle_movement(int keycode, t_prog *prog)
{
	const int	options[] = {'w', 'a', 's', 'd', LSHIFT, SPACE, 0};
	const int	flags[] = {MOVE_FORWARD, MOVE_LEFT, MOVE_BACKWARD, MOVE_RIGHT, MOVE_DOWN, MOVE_UP};

	if (toggle_flag(keycode, &options[0], &flags[0], &prog->scene->camera.movekeys))
	{
		reset_accumulation(prog);
		return (1);
	}
	return (0);
}

int	toggle_pass(int keycode, t_prog *prog)
{
	const int	options[] = {'z', 'x', 'c', 'v', 'b', 'n', 0};
	const int	flags[] = {AMBIENT, DIFFUSE, SPECULAR, UV, NORMAL, DEPTH_MAP};

	if (toggle_flag(keycode, &options[0], &flags[0], &prog->win_scene->vp_flags))
	{
		reset_accumulation(prog);
		return (1);
	}
	return (0);
}

int	toggle_flag(int to_check, const int *options, const int *flags, t_uint *flag)
{
	int			i;

	i = 0;
	while (options[i])
	{
		if (to_check == options[i])
		{
			*flag ^= flags[i];
			return (1);
		}
		i++;
	}
	return (0);
}


int key_down(int keycode, t_prog *prog)
{
	if (toggle_effects(keycode, prog))
		return (0);
	if (toggle_movement(keycode, prog))
		return (0);
	if (toggle_pass(keycode, prog))
		return (0);
	if (keycode == 65453)
	{
		prog->scene->nb_bounces--;
		ft_log(LOG, "bounce:%d", prog->scene->nb_bounces);
	}
	else if (keycode == 65451)
	{
		prog->scene->nb_bounces++;
		ft_log(LOG, "bounce:%d", prog->scene->nb_bounces);
	}
	else if (keycode == ESC)
		free_all(prog);
	else if (keycode == 'r')
	{
		reset_cam_orientation(&prog->scene->camera);
		reset_accumulation(prog);
	}
	else if (keycode == 'n')
		print_cam(&prog->scene->camera);
	else if (keycode == 'm')
		print_scene(prog->scene);
	else if (keycode == 'f')
		prog->win_scene->vp_flags ^= SHOW_FRAME;
	else if (keycode == 'g')
		save_image_to_ppm(prog->win_scene);
	return (0);
}

int key_up(int keycode, t_prog *prog)
{
	if (toggle_movement(keycode, prog))
		return (0);
	
	return (0);
}
