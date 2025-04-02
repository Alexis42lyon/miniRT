#include "window.h"

typedef void	(*t_button_func)(t_prog *);

static void	button_func2(t_prog *prog)
{
	free_scene(prog->scene);
	init(prog, NULL);
	run_pipeline(prog);
}

static t_button_func	get_button_func(int index)
{
	static t_button_func	funcs[] = {&run_pipeline, &button_func2};
	int						count;

	count = sizeof(funcs) / sizeof(funcs[0]);
	if (index < 0 || index >= count)
		return (NULL);
	return (funcs[index]);
}

static const t_win_button	*get_button_data(int index)
{
	static t_win_button	buttons[] = {
		{NULL, NULL, 10, 10, 100, 50, 0xFF0000, "Render"},
		{NULL, NULL, 120, 10, 100, 50, 0x00FF00, "ReParse"},
		{NULL, NULL, 10, 70, 100, 50, 0x0000FF, "Btn3"},
		{NULL, NULL, 120, 70, 100, 50, 0xFFFF00, "Btn4"}
	};
	int					count;

	count = sizeof(buttons) / sizeof(buttons[0]);
	if (index < 0 || index >= count)
		return (NULL);
	return (&buttons[index]);
}

void	draw_button_win(t_win_button *win_button, int btn_index)
{
	const t_win_button	*btn;
	int					i;
	int					j;

	if (!win_button || !win_button->mlx_ptr || !win_button->win_ptr)
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
			mlx_pixel_put(win_button->mlx_ptr, win_button->win_ptr, i, j, btn->color);
			j++;
		}
		i++;
	}
	mlx_string_put(win_button->mlx_ptr, win_button->win_ptr,
		btn->x + 10, btn->y + 20, 0xFFFFFF, btn->text);
}

int	button_window_click(int button, int x, int y, t_prog *prog)
{
	const t_win_button	*btn;
	t_button_func		func;
	int					i;

	if (button != 1 || !prog || !prog->win_button)
		return (0);
	i = 0;
	while (i < 4)
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
			draw_button_win(prog->win_button, i);
			break ;
		}
		i++;
	}
	return (0);
}

void	init_button_window(t_prog *prog)
{
	int	i;

	if (!prog || !prog->win_scene || !prog->win_scene->mlx_ptr)
		return ;
	ft_bzero(prog->win_button, sizeof(t_win_button));
	prog->win_button->mlx_ptr = prog->win_scene->mlx_ptr;
	prog->win_button->win_ptr = mlx_new_window(prog->win_button->mlx_ptr,
			250, 150, "Controls");
	prog->win_button->width = 250;
	prog->win_button->height = 150;
	prog->win_button->color = 0x333333;
	i = 0;
	while (i < 4)
	{
		draw_button_win(prog->win_button, i);
		i++;
	}
	mlx_mouse_hook(prog->win_button->win_ptr, button_window_click, prog);
}
