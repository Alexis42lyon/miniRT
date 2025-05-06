/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:02:36 by mjuncker          #+#    #+#             */
/*   Updated: 2025/05/06 15:55:41 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

# include "miniRT.h"
# include <mlx.h>

# define WIDTH 480
# define HEIGHT 360

/* ----------------------------------- MLX ---------------------------------- */
typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_win_scene
{
	char	*name;
	int		width;
	int		height;

	int		view_width;
	int		view_height;
	double	aspect_ratio;

	t_vec3	*accumulation_data;

	void	*win_ptr;
	void	*mlx_ptr;
	t_data	img;
}	t_win_scene;

// image.c
int		create_img(t_win_scene *win);
void	set_pixel(t_data *data, int x, int y, int color);
int		create_trgb(int t, int r, int g, int b);

// window.c
void	init_win(t_prog *prog);
int		key_hook(int keycode, t_prog *prog);

void	run_pipeline(t_prog *prog);
int		new_frame(t_prog *prog);

// button.c
void	init_button_window(t_prog *prog);

#endif
