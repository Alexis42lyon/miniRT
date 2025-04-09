#include "window.h"

void	draw_controls(t_prog *prog)
{
	t_win_button	*win;
	int				x;
	int				y;

	win = prog->win_button;
	mlx_clear_window(win->mlx_ptr, win->win_ptr);
	x = 20;
	while (x < 20 + win->slider_width)
	{
		y = 80;
		while (y < 85)
			mlx_pixel_put(win->mlx_ptr, win->win_ptr, x, y++, 0xAAAAAA);
		x++;
	}
	x = win->slider_x - 5;
	while (x <= win->slider_x + 5)
	{
		y = 75;
		while (y < 90)
			mlx_pixel_put(win->mlx_ptr, win->win_ptr, x, y++, 0x0000FF);
		x++;
	}
	x = 20;
	while (x < 120)
	{
		y = 20;
		while (y < 50)
			mlx_pixel_put(win->mlx_ptr, win->win_ptr, x, y++, 0xFF0000);
		x++;
	}
	mlx_string_put(win->mlx_ptr, win->win_ptr, 40, 35, 0xFFFFFF, "Render");
}

int	handle_click(int button, int x, int y, t_prog *prog)
{
	t_win_button	*win;

	win = prog->win_button;
	if (button == 1)
	{
		if (x >= win->slider_x - 5 && x <= win->slider_x + 5
			&& y >= 75 && y <= 90)
			win->is_dragging = 1;
		else if (x >= 20 && x <= 120 && y >= 20 && y <= 50)
		{
			run_pipeline(prog);
			print_scene(prog->scene);
		}
	}
	return (0);
}

int	mouse_move(int x, int y, t_prog *prog)
{
	t_win_button	*win;

	(void)y;
	win = prog->win_button;
	if (win->is_dragging)
	{
		win->slider_x = x;
		if (win->slider_x < 20)
			win->slider_x = 20;
		if (win->slider_x > 20 + win->slider_width)
			win->slider_x = 20 + win->slider_width;
		prog->scene->camera.fov = (win->slider_x - 20) * 180
			/ win->slider_width;
		draw_controls(prog);
	}
	return (0);
}

int	button_release(int button, int x, int y, t_prog *prog)
{
	t_win_button	*win;

	(void)x;
	(void)y;
	win = prog->win_button;
	if (button == 1)
		win->is_dragging = 0;
	return (0);
}

int	window_button_close(void *param)
{
	t_prog	*prog;

	prog = (t_prog *)param;
	free_all(prog);
	return (0);
}

void	init_button_window(t_prog *prog)
{
	t_win_button	*win;

	if (!prog || !prog->win_scene || !prog->win_scene->mlx_ptr)
		return ;
	win = prog->win_button;
	win->mlx_ptr = prog->win_scene->mlx_ptr;
	win->win_ptr = mlx_new_window(win->mlx_ptr, 250, 150, "Controls");
	win->width = 400;
	win->height = 800;
	win->slider_width = 200;
	win->slider_x = 20 + (prog->scene->camera.fov * win->slider_width / 180);
	win->is_dragging = 0;
	draw_controls(prog);
	mlx_hook(win->win_ptr, 17, 1L << 2, window_button_close, prog);
	mlx_hook(win->win_ptr, 4, 1L << 2, handle_click, prog);
	mlx_hook(win->win_ptr, 5, 1L << 3, button_release, prog);
	mlx_hook(win->win_ptr, 6, 1L << 6, mouse_move, prog);
}
