/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   denoising.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:26:14 by abidolet          #+#    #+#             */
/*   Updated: 2025/04/17 00:07:54 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "raytracer.h"
#include "window.h"
#include <math.h>

static void	process_pixel(t_win_scene *win, int *temp, int x, int y)
{
	int	rgb[3];
	int	idx;
	int	dx;
	int	dy;
	int	count;

	ft_memset(rgb, 0, sizeof(rgb));
	count = 0;
	dy = -1;
	while (++dy <= 1)
	{
		dx = -1;
		while (++dx <= 1)
		{
			if (x + dx < 0 || x + dx >= WIDTH
				|| y + dy < 0 || y + dy >= HEIGHT)
				continue ;
			idx = (y + dy) * WIDTH + (x + dx);
			rgb[0] += (win->img.addr[idx] >> 16) & 0xFF;
			rgb[1] += (win->img.addr[idx] >> 8) & 0xFF;
			rgb[2] += win->img.addr[idx] & 0xFF;
			count++;
		}
	}
	idx = y * WIDTH + x;
	temp[idx] = ((rgb[0] / count) << 16) | ((rgb[1] / count) << 8) | (rgb[2] / count);
}

void	denoiser(t_prog *prog, t_win_scene *win)
{
	int		*temp;
	int		x;
	int		y;

	if (!prog || !win)
		return ;
	temp = malloc(sizeof(int) * WIDTH * HEIGHT);
	if (!temp)
		return ;
	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			if (x == 0 || y == 0 || x == WIDTH - 1 || y == HEIGHT - 1)
				temp[y * WIDTH + x] = win->img.addr[y * WIDTH + x];
			else
				process_pixel(win, temp, x, y);
		}
	}
	ft_memcpy(win->img.addr, temp, sizeof(int) * WIDTH * HEIGHT);
	free(temp);
}
