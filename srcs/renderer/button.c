#include "window.h"
#include "button.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

#if SHOW_BUTTON

static void	draw_slider(t_win_button *win_btn, int x, int y, float value)
{
	t_data	img;
	int		i;
	int		j;
	int		slider_x;

	img.img = mlx_new_image(win_btn->mlx_ptr, SLIDER_WIDTH, SLIDER_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	i = -1;
	while (++i < SLIDER_WIDTH)
	{
		j = -1;
		while (++j < SLIDER_HEIGHT)
			*(int *)(img.addr + j * img.line_length + i * (img.bits_per_pixel / 8)) = SLIDER_COLOR;
	}
	slider_x = (int)(value * (SLIDER_WIDTH - SLIDER_HANDLE_WIDTH));
	i = slider_x - 1;
	while (++i < slider_x + SLIDER_HANDLE_WIDTH)
	{
		j = -1;
		while (++j < SLIDER_HEIGHT)
			*(int *)(img.addr + j * img.line_length + i * (img.bits_per_pixel / 8)) = SLIDER_HANDLE_COLOR;
	}
	mlx_put_image_to_window(win_btn->mlx_ptr, win_btn->win_ptr, img.img, x, y);
	mlx_destroy_image(win_btn->mlx_ptr, img.img);
}

static void	draw_button_window(t_prog *prog, t_win_button *win_btn)
{
	t_data	img;
	size_t	i;
	int		j;
	int		k;
	char	ratio_str[32];

	img.img = mlx_new_image(win_btn->mlx_ptr, win_btn->width, win_btn->height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	i = -1;
	while (++i < TAB_COUNT)
	{
		j = win_btn->tab_buttons[i].x - 1;
		while (++j < win_btn->tab_buttons[i].x + win_btn->tab_buttons[i].width)
		{
			k = win_btn->tab_buttons[i].y - 1;
			while (++k < win_btn->tab_buttons[i].y + win_btn->tab_buttons[i].height)
			{
				if (win_btn->current_tab == (enum e_tab)i)
					*(int *)(img.addr + k * img.line_length + j * (img.bits_per_pixel / 8)) = ACTIVE_TAB_COLOR;
				else
					*(int *)(img.addr + k * img.line_length + j * (img.bits_per_pixel / 8)) = TAB_COLOR;
			}
		}
	}
	mlx_put_image_to_window(win_btn->mlx_ptr, win_btn->win_ptr, img.img, 0, 0);
	mlx_destroy_image(win_btn->mlx_ptr, img.img);
	i = -1;
	while (++i < TAB_COUNT)
	{
		mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
			win_btn->tab_buttons[i].x + 10 - i,
			win_btn->tab_buttons[i].y + TAB_HEIGHT / 2 + 5,
			TEXT_COLOR, win_btn->tab_buttons[i].text);
	}
	if (win_btn->current_tab == TAB_LIGHTS)
	{
		mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr, 25, 50,
			TEXT_COLOR, "Ambient Lightning:");
		snprintf(ratio_str, 32, "Ratio: %.2f", win_btn->ambient_ratio);
		mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr, 25, 70,
			TEXT_COLOR, ratio_str);
		draw_slider(win_btn, 25, 80, win_btn->ambient_ratio);
	}
	else if (win_btn->current_tab == TAB_OBJECTS)
	{
		const int stw = (win_btn->width - 30) / SUB_COUNT;
		int sx = 15;
		i = -1;
		while (++i < SUB_COUNT)
		{
			j = sx - 1;
			while (++j < sx + stw)
			{
				k = TAB_HEIGHT + 5;
				while (++k < TAB_HEIGHT + 25)
				{
					// if (win_btn->current_subtab == (enum e_subtab)i)
						// *(int *)(img.addr + k * img.line_length + j * (img.bits_per_pixel / 8)) = ACTIVE_TAB_COLOR;
					// else
						// *(int *)(img.addr + k * img.line_length + j * (img.bits_per_pixel / 8)) = TAB_COLOR;
				}
			}
			mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr, sx + 5, TAB_HEIGHT + 15,
				TEXT_COLOR, (char *[]){"Sphere", "Plane", "Cylinder", "Cone"}[i]);
			sx += stw + 5;
		}
		char *objects[4] =
		{
			"Sphere",
			"Plane",
			"Cylinder",
			"Cone"
		};
		while (++i < 3)
		{
			mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr, 25, 100 + i * 20, TEXT_COLOR, objects[i]);
		}
	}
	else if (win_btn->current_tab == TAB_MATERIALS)
	{
		i = -1;
		while (++i < prog->scene->nb_materials)
		{
			mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
				25, 50 + i * 20,
				TEXT_COLOR, prog->scene->materials[i].name);
		}
	}
}

static int	handle_mouse_move(int x, int y, t_prog *prog)
{
	t_win_button	*win_btn;
	float			new_ratio;

	(void)y;
	win_btn = prog->win_button;
	if (win_btn->is_dragging && win_btn->current_tab == TAB_LIGHTS)
	{
		x = fmax(15, fmin(x, 15 + SLIDER_WIDTH));
		new_ratio = (float)(x - 15) / SLIDER_WIDTH;
		new_ratio = fmaxf(0.0f, fminf(1.0f, new_ratio));
		win_btn->ambient_ratio = new_ratio;
		prog->scene->ambient_light.ratio = new_ratio;
		draw_button_window(prog, win_btn);
		reset_accumulation(prog);
	}
	return (0);
}

static int	handle_button_click(int button, int x, int y, t_prog *prog)
{
	t_win_button	*win_btn;
	int				i;

	win_btn = prog->win_button;
	if (button == 1)
	{
		i = -1;
		while (++i < TAB_COUNT)
		{
			if (x >= win_btn->tab_buttons[i].x
				&& x <= win_btn->tab_buttons[i].x + win_btn->tab_buttons[i].width
				&& y >= win_btn->tab_buttons[i].y
				&& y <= win_btn->tab_buttons[i].y + win_btn->tab_buttons[i].height)
			{
				win_btn->current_tab = i;
				draw_button_window(prog, win_btn);
				return (0);
			}
		}
		if (win_btn->current_tab == TAB_LIGHTS && x >= 25
			&& x <= 25 + SLIDER_WIDTH && y >= 80 && y <= 80 + SLIDER_HEIGHT)
			win_btn->is_dragging = 1;
	}
	if (win_btn->current_tab == TAB_OBJECTS && y > TAB_HEIGHT && y < TAB_HEIGHT + 30)
	{
		const int stw = (win_btn->width - 30) / SUB_COUNT;
		int sx = 15;
		i = -1;
		while (++i < SUB_COUNT)
		{
			if (x >= sx && x <= sx + stw)
			{
				win_btn->current_subtab = i;
				draw_button_window(prog, win_btn);
				return (0);
			}
			sx += stw + 5;
		}
	}
	return (0);
}

static int	handle_mouse_up(int button, int x, int y, t_prog *prog)
{
	(void)x;
	(void)y;
	(void)button;
	prog->win_button->is_dragging = 0;
	return (0);
}

static int	key_hook_btn(int keycode, t_prog *prog)
{
	if (keycode == ESC)
		free_all(prog);
	return (0);
}

void	init_button_window(t_prog *prog)
{
	t_win_button	*win_btn;
	int				i;
	const float		tab_width = CONTROL_WINDOW_WIDTH / TAB_COUNT;

	win_btn = prog->win_button;
	*win_btn = (t_win_button){
		.width = CONTROL_WINDOW_WIDTH,
		.height = prog->win_scene->height,
		.mlx_ptr = prog->win_scene->mlx_ptr,
		.win_ptr = mlx_new_window(prog->win_scene->mlx_ptr,
			CONTROL_WINDOW_WIDTH, prog->win_scene->height, "Control Panel"),
		.current_tab = TAB_LIGHTS,
		.ambient_ratio = prog->scene->ambient_light.ratio,
		.is_dragging = 0
	};
	i = -1;
	while (++i < TAB_COUNT)
	{
		win_btn->tab_buttons[i] = (t_button)
		{
			.x = i * tab_width,
			.y = 0,
			.width = tab_width,
			.height = TAB_HEIGHT,
			.text = (char *[]){"Lights", "Objects", "Materials"}[i]
		};
	}
	mlx_hook(win_btn->win_ptr, 2, 1L << 0, key_hook_btn, prog);
	mlx_hook(win_btn->win_ptr, 17, 0, window_close, prog);
	mlx_hook(win_btn->win_ptr, 4, 1L << 2, handle_button_click, prog);
	mlx_hook(win_btn->win_ptr, 6, 1L << 6, handle_mouse_move, prog);
	mlx_hook(win_btn->win_ptr, 5, 1L << 3, handle_mouse_up, prog);
	draw_button_window(prog, win_btn);
}

#else

void	init_button_window(t_prog *prog)
{
	(void)prog;
}

#endif
