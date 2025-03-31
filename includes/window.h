/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:00:59 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/31 10:42:09 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

# include "miniRT.h"
# include <mlx.h>

# define HEIGHT 400
# define WIDTH 800

# define SHOW_WIN 1

/* ----------------------------------- MLX ---------------------------------- */
typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_win
{
	char	*name;
	int		width;
	int		height;

	int		view_width;
	int		view_height;
	int		aspect_ratio;

	void	*win_ptr;
	void	*mlx_ptr;
	t_data	img;
}	t_win;

// image.c
int		create_img(t_win *win);
void	set_pixel(t_data *data, int x, int y, int color);
int		create_trgb(int t, int r, int g, int b);

// window.c
void	init_win(t_prog *prog);
int		key_hook(int keycode, t_prog *prog);

void	render(t_win *win, t_scene *scene);

#endif
