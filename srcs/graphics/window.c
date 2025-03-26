/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 09:04:01 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/25 15:14:51 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include "libft/io.h"
#include "libft/memory.h"
#include "libft/string.h"
#include "miniRT.h"
#include "mlx.h"
#include <stdio.h>

#if SHOW_WIN

static int	key_hook(int keycode, t_win *scene)
{
	(void)scene;
	if (keycode == ESC)
		free_all(NULL);
	return (0);
}

int	window_close(void *param)
{
	(void)param;
	free_all(NULL);
	exit(0);
}

void	init_win(t_win *win)
{
	ft_bzero(win, sizeof(t_win));
	win->height = HEIGHT;
	win->width = WIDTH;
	win->name = ft_strdup("miniRT");
	if (malloc_assert(win->name, __FILE__, __LINE__))
		free_all(NULL);
	win->mlx_ptr = mlx_init();
	if (!win->mlx_ptr)
		free_all(NULL);
	win->win_ptr = mlx_new_window(win->mlx_ptr, win->width,
			win->height, win->name);
	if (!win->win_ptr)
		free_all(NULL);
	if (create_img(win) == -1)
		free_all(NULL);
	mlx_hook(win->win_ptr, 17, 1L << 2, window_close, NULL);
	mlx_key_hook(win->win_ptr, key_hook, NULL);

}

#else

void	init_win(t_win *win)
{
	ft_bzero(win, sizeof(t_win));
	return ;
}

#endif
