#include "window.h"

static void	button_func2(t_prog *prog)
{
	free_scene(prog->scene);
	init(prog, NULL);
	run_pipeline(prog);
}

// frame time
// frame count
// cam pos

static t_button_func	get_button_func(int index)
{
	static t_button_func	funcs[] = {&run_pipeline, &button_func2};
	int						count;

	count = sizeof(funcs) / sizeof(funcs[0]);
	if (index < 0 || index >= count)
		return (NULL);
	return (funcs[index]);
}

static const t_button	*get_button_data(int index)
{
	static t_button	buttons[] = {{10, 10, 100, 50, 0xFF0000, "Btn1"},
	{120, 10, 100, 50, 0x00FF00, "Btn2"},
	{10, 70, 100, 50, 0x0000FF, "Btn3"},
	{120, 70, 100, 50, 0xFFFF00, "Btn4"}};
	int				count;

	count = sizeof(buttons) / sizeof(buttons[0]);
	if (index < 0 || index >= count)
		return (NULL);
	return (&buttons[index]);
}

void	draw_button(t_win *win, int btn_index)
{
	const t_button	*btn;
	int				i;
	int				j;

	if (!win || !win->mlx_ptr || !win->win_ptr)
		return ;
	btn = get_button_data(btn_index);
	if (!btn)
		return ;
	i = btn->x;
	while (i < btn->x + btn->width)
	{
		j = btn->y;
		while (j < btn->y + btn->height)
		{
			mlx_pixel_put(win->mlx_ptr, win->win_ptr, i, j, btn->color);
			j++;
		}
		i++;
	}
	mlx_string_put(win->mlx_ptr, win->win_ptr,
		btn->x + 10, btn->y + 20, 0xFFFFFF, btn->text);
}

int	mouse_click(int button, int x, int y, t_prog *prog)
{
	const t_button	*btn;
	t_button_func	func;
	int				i;

	if (button != 1 || !prog)
		return (0);
	i = 0;
	while (i < 2)
	{
		btn = get_button_data(i);
		if (!btn)
			continue ;
		if (x >= btn->x && x <= btn->x + btn->width
			&& y >= btn->y && y <= btn->y + btn->height)
		{
			func = get_button_func(i);
			if (func)
				func(prog);
			draw_button(prog->win, i);
			break ;
		}
		i++;
	}
	return (0);
}

void	init_buttons(t_win *prog)
{
	int	i;

	if (!prog)
		return ;
	i = 0;
	while (i < 2)
	{
		draw_button(prog, i);
		i++;
	}
}
