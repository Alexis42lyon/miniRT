/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 09:04:01 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/28 20:57:02 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include "libft/io.h"
#include "libft/memory.h"
#include "libft/string.h"
#include "miniRT.h"
#include "mlx.h"
#include <stdio.h>

extern t_sphere sphere;

#if SHOW_WIN

int	key_hook(int keycode, t_prog *prog)
{
	if (keycode == ESC)
		free_all(prog);
	if (keycode == 'e')
		sphere.radius += 0.1;
	if (keycode == 'f')
		sphere.radius -= 0.1;
	if (keycode == 'w')
		sphere.origin = vec3_add(sphere.origin, new_vec3(0, -0.1, 0));
	if (keycode == 's')
		sphere.origin = vec3_add(sphere.origin, new_vec3(0, 0.1, 0));
	if (keycode == 'a')
		sphere.origin = vec3_add(sphere.origin, new_vec3(0.1, 0, 0));
	if (keycode == 'd')
		sphere.origin = vec3_add(sphere.origin, new_vec3(-0.1, 0, 0));
	printf("sphere pos: ");
	print_vec(sphere.origin);
	printf("\nradius: %f\n", sphere.radius);

	render(prog->win, prog->scene);
	return (0);
}

int	window_close(void *param)
{
	(void)param;
	free_all(prog);
	exit(0);
}

void	init_win(t_win *win)
{
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
	mlx_hook(win->win_ptr, 17, 1L << 2, window_close, NULL);


}

#else

void	init_win(t_win *win)
{
	(void)win;
	ft_calloc(0, sizeof(t_win));
	return ;
}

#endif
