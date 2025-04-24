/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:02:36 by mjuncker          #+#    #+#             */
/*   Updated: 2025/04/24 23:16:33 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

# include "miniRT.h"
# include <mlx.h>

# define SHOW_BUTTON 0
# define SHOW_LOGGING 0

# define WIDTH 720
# define HEIGHT 480

/* ----------------------------------- MLX ---------------------------------- */

# define ON_KEYDOWN 2
# define ON_KEYUP 3
# define ON_MOUSEDOWN 4
# define ON_MOUSEUP 5
# define ON_MOUSEMOVE 6
# define ON_EXPOSE 12
# define ON_DESTROY 17

# define KEYDOWN_MASK 1L<<0
# define KEYUP_MASK 1L<<1
# define MOUSEDOWN_MASK 1L<<2
# define MOUSEUP_MASK 1L<<3

/* -------------------------------------------------------------------------- */
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
	int		half_width;
	int		half_height;

	int		view_width;
	int		view_height;
	double	aspect_ratio;

	t_vec3	*accumulation_data;

	void	*win_ptr;
	void	*mlx_ptr;

	t_data	img;

	bool	paused;
}	t_win_scene;

/* ------------------------------- END BUTTON ------------------------------ */

// image.c
int		create_img(t_win_scene *win);
void	set_pixel(t_data *data, int x, int y, int color);
int		create_trgb(int t, int r, int g, int b);

// window.c
void	init_win(t_prog *prog);
int		window_close(void *prog);
int		key_hook(int keycode, t_prog *prog);

void	run_pipeline(t_prog *prog);
int		new_frame(t_prog *prog);

// button.c
void	init_button_window(t_prog *prog);

#endif
