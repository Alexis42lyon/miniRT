#ifndef WINDOW_H
# define WINDOW_H

# include "miniRT.h"
# include <mlx.h>

# define SHOW_BUTTON 0
# define WIDTH 600
# define HEIGHT 300

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

# define SLIDER_WIDTH 200
# define SLIDER_MIN 0
# define SLIDER_MAX 180

typedef struct s_win_button
{
	void	*win_ptr;
	void	*mlx_ptr;
	int		width;
	int		height;
	int		slider_x;
	int		slider_width;
	int		is_dragging;
}	t_win_button;

typedef void	(*t_button_func)(t_prog *);

// image.c
int		create_img(t_win_scene *win);
void	set_pixel(t_data *data, int x, int y, int color);
int		create_trgb(int t, int r, int g, int b);

// window.c
void	init_win(t_prog *prog);
int		key_hook(int keycode, t_prog *prog);

void	run_pipeline(t_prog *prog);
int		 new_frame(t_prog *prog);

// button.c
void	free_scene(t_scene *scene);
void	init(t_prog *prog, char **av);
void	init_button_window(t_prog *prog);
void	start_renderer(t_prog *prog);
void	print_scene(const t_scene *scene);

#endif
