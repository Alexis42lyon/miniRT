/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 14:46:34 by abidolet          #+#    #+#             */
/*   Updated: 2025/03/25 08:47:51 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

static int	key_hook(int keycode, t_scene *scene)
{
	if (keycode == ESC)
		free_all(scene, NULL);
	return (0);
}

int	window_close(void *param)
{
	t_scene	*scene;

	scene = (t_scene *)param;
	free_all(scene, NULL);
	exit(0);
}

void	start(t_scene *scene, char **av)
{
	scene->win->mlx = mlx_init();
	if (!scene->win->mlx)
	{
		error("mlx init failed");
		free_all(scene, NULL);
	}
	mlx_get_screen_size(scene->win->mlx, &scene->win->width, &scene->win->height);
	// scene->win->width *= SIZE_WIN;
	// scene->win->height *= SIZE_WIN;
	scene->win->width = WIDTH;
	scene->win->height = HEIGHT;
	scene->win = mlx_new_window(scene->win->mlx, scene->win->width, scene->win->height, av[0]);
	if (!scene->win)
	{
		//! MLX ptr pas free ?
		error("mlx window creation failed");
		free_all(scene, NULL);
	}
	mlx_key_hook(scene->win, key_hook, scene);
	mlx_hook(scene->win, 17, 0, window_close, scene);
	mlx_loop(scene->win->mlx);
}
