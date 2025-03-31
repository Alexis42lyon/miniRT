#include "window.h"

void	draw_button(t_win *win, int color)
{
	int x = 0;
	int y = 0;
	int width = 100;
	int height = 100;

	for (int i = x; i < x + width; i++)
		for (int j = y; j < y + height; j++)
			mlx_pixel_put(win->mlx_ptr, win->win_ptr, i, j, color);
	mlx_string_put(win->mlx_ptr, win->win_ptr, x + 10, y + 10, 0xFFFFFF, "Clique here !");
}

int	mouse_click(int butt, int x, int y, t_win *win)
{
	if (butt == 1 &&
		x >= win->button_x && x <= win->button_x + win->button_width &&
		y >= win->button_y && y <= win->button_y + win->button_height)
	{
		ft_printf("Button cliqued !\n");
		draw_button(win, 0xFF0000);
	}
	return (0);
}
