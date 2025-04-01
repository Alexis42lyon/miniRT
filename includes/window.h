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

	int		button_x;
	int		button_y;
	int		button_width;
	int		button_height;

	void	*win_ptr;
	void	*mlx_ptr;
	t_data	img;
}	t_win;

typedef struct s_button
{
	int		x;
	int		y;
	int		width;
	int		height;
	int		color;
	char	*text;
}	t_button;

// image.c
int		create_img(t_win *win);
void	set_pixel(t_data *data, int x, int y, int color);
int		create_trgb(int t, int r, int g, int b);

// window.c
void	init_win(t_prog *prog);
int		mouse_click(int button, int x, int y, t_prog *prog);
void	draw_button(t_win *win, int color);
int		key_hook(int keycode, t_prog *prog);

void	run_pipeline(t_prog *prog);

// button.c
void	init_buttons(t_win *win);

#endif
