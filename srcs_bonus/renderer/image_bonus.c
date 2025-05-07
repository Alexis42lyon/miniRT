/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:16:12 by mjuncker          #+#    #+#             */
/*   Updated: 2025/05/07 09:19:42 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "raytracer_bonus.h"

int	create_img(t_win_scene *win)
{
	win->img.img = mlx_new_image(win->mlx_ptr, win->width, win->height);
	if (!win->img.img)
		return (-1);
	win->img.addr = mlx_get_data_addr(win->img.img, &win->img.bits_per_pixel,
			&win->img.line_length, &win->img.endian);
	if (!win->img.addr)
		return (-1);
	win->final_image.img = mlx_new_image(win->mlx_ptr, WIDTH, HEIGHT);
	if (!win->final_image.img)
		return (-1);
	win->final_image.addr = mlx_get_data_addr(win->final_image.img,
			&win->final_image.bits_per_pixel,
			&win->final_image.line_length, &win->final_image.endian);
	if (!win->final_image.addr)
		return (-1);
	return (0);
}

void	set_pixel(t_data *data, int x, int y, int color)
{
	void	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

unsigned int	get_pixel(t_data *data, int x, int y)
{
	void			*dst;
	unsigned int	color;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	color = *(unsigned int *)dst;
	return (color);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	display_frame(t_win_scene *win, t_scene *scene)
{
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr,
		win->final_image.img, 0, 0);
	scene->frame_count++;
}
