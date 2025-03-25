/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:59:06 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/25 09:55:13 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "screen.h"

int	create_img(t_win *win)
{
	win->img.img = mlx_new_image(win->mlx, win->width, win->height);
	if (!win->img.img)
		return (-1);
	win->img.addr = mlx_get_data_addr(win->img.img, &win->img.bits_per_pixel,
			&win->img.line_length, &win->img.endian);
	if (!win->img.addr)
	{
		mlx_destroy_image(win->mlx, win->img.img);
		return (-1);
	}
	return (0);
}

void	set_pixel(t_data *data, int x, int y, int color)
{
	void	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}
