/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 14:46:34 by abidolet          #+#    #+#             */
/*   Updated: 2025/03/23 17:03:37 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

static int	key_hook(int keycode, t_scene *scene)
{
	if (keycode == ESC)
		close_window(scene);
	return (0);
}

void	start(t_scene *scene, char **av)
{
	scene->mlx = mlx_init();
	if (!scene->mlx)
	{
		error("mlx init failed");
		exit(1);
	}
	mlx_get_screen_size(scene->mlx, &scene->width, &scene->height);
	scene->width *= SIZE_WIN;
	scene->height *= SIZE_WIN;
	scene->win = mlx_new_window(scene->mlx, scene->width, scene->height, av[0]);
	if (!scene->win)
	{
		error("mlx window creation failed");
		close_window(scene);
	}
	mlx_key_hook(scene->win, key_hook, scene);
	mlx_hook(scene->win, 17, 0, close_window, scene);
	mlx_loop(scene->mlx);
}
