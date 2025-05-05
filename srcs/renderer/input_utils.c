/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:27:36 by mjuncker          #+#    #+#             */
/*   Updated: 2025/05/05 16:54:30 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"

int	toggle_flag(int to_check, const int *options,
	const int *flags, t_uint *flag)
{
	int			i;

	i = 0;
	while (options[i])
	{
		if (to_check == options[i])
		{
			*flag ^= flags[i];
			return (flags[i]);
		}
		i++;
	}
	return (0);
}

int	toggle_effects(int keycode, t_prog *prog)
{
	const int	options[] = {'1', '2', '3', '4', '5', '6', '7', 0};
	const int	flags[] = {
		GRAYSCALE, PIXEL, INVERT,
		CHROMA, POSTERIZE, DEPTH_OF_FIELD, ANTIALIASING
	};

	return (toggle_flag(keycode, &options[0], &flags[0],
			&prog->win_scene->img_flags));
}

int	toggle_movement(int keycode, t_prog *prog)
{
	const int	options[] = {'w', 'a', 's', 'd', LSHIFT, SPACE, 0};
	const int	flags[] = {
		MOVE_FORWARD, MOVE_LEFT, MOVE_BACKWARD,
		MOVE_RIGHT, MOVE_DOWN, MOVE_UP
	};

	if (toggle_flag(keycode, &options[0], &flags[0],
			&prog->scene->camera.movekeys))
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
	int			flag;

	flag = toggle_flag(keycode, &options[0], &flags[0],
			&prog->win_scene->vp_flags);
	if (flag)
	{
		if (flag == AMBIENT || flag == DIFFUSE || flag == SPECULAR)
			reset_accumulation(prog);
		return (1);
	}
	return (0);
}

int	cam_input(int keycode, t_prog *prog)
{
	if (keycode == 65453 || keycode == 65451)
	{
		if (keycode == 65453)
			prog->scene->nb_bounces--;
		else
			prog->scene->nb_bounces++;
		ft_log(LOG, "bounce:%d", prog->scene->nb_bounces);
		reset_accumulation(prog);
		return (1);
	}
	else if (keycode == 'r')
	{
		reset_cam_orientation(&prog->scene->camera);
		reset_accumulation(prog);
		return (1);
	}
	return (0);
}
