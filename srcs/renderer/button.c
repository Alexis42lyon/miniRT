#include "window.h"
#include <math.h>

#define TAB_COUNT 5
#define TAB_HEIGHT 30
#define TAB_COLOR 0x444444
#define ACTIVE_TAB_COLOR 0x666666
#define SLIDER_COLOR 0x888888
#define SLIDER_HANDLE_COLOR 0xDDDDDD
#define SLIDER_HANDLE_WIDTH 10
#define BUTTON_COLOR 0x666666
#define BUTTON_HOVER_COLOR 0x888888
#define TEXT_COLOR 0xFFFFFF
#define CONTROL_WINDOW_WIDTH 200

#if SHOW_BUTTON

typedef int	(*t_button_func)(t_prog *);

enum e_tab
{
	TAB_AMBIENT = 0,
	TAB_CAMERA,
	TAB_OBJECTS,
	TAB_MATERIALS,
	TAB_SETTINGS
};

typedef struct s_button
{
	int				x;
	int				y;
	int				width;
	int				height;
	char			*text;
	t_button_func	func;
	bool			is_hovered;
}	t_button;

typedef struct s_slider
{
	int		x;
	int		y;
	int		width;
	int		height;
	float	min;
	float	max;
	float	*value;
	bool	is_dragging;
}	t_slider;

typedef struct s_tab_data
{
	enum e_tab	type;
	char		*name;
	t_button	*buttons;
	int			button_count;
	t_slider	*sliders;
	int			slider_count;
}	t_tab_data;

typedef struct s_win_button
{
	void		*win_ptr;
	void		*mlx_ptr;
	int			width;
	int			height;
	enum e_tab	current_tab;
	t_tab_data	tabs[TAB_COUNT];
	t_button	tab_buttons[TAB_COUNT];
	t_button	plus_buttons[3];
	t_button	minus_buttons[3];
	t_slider	ambient_slider;
	t_slider	fov_slider;
}	t_win_button;

static int	handle_button_release(int button, int x, int y, t_prog *prog)
{
	t_win_button	*win_btn;

	(void)button;
	(void)x;
	(void)y;
	win_btn = prog->win_button;
	win_btn->ambient_slider.is_dragging = false;
	win_btn->fov_slider.is_dragging = false;
	return (0);
}

static void	draw_button_window(t_prog *prog);

static int	handle_button_click(int button, int x, int y, t_prog *prog)
{
	t_win_button	*win_btn;
	int				i;

	(void)button;
	win_btn = prog->win_button;
	for (i = 0; i < TAB_COUNT; i++)
	{
		if (x >= win_btn->tab_buttons[i].x
			&& x <= win_btn->tab_buttons[i].x + win_btn->tab_buttons[i].width
			&& y >= win_btn->tab_buttons[i].y
			&& y <= win_btn->tab_buttons[i].y + win_btn->tab_buttons[i].height)
		{
			win_btn->current_tab = i;
			draw_button_window(prog);
			return (0);
		}
	}
	if (win_btn->current_tab == TAB_AMBIENT)
	{
		for (i = 0; i < 3; i++)
		{
			if (x >= win_btn->plus_buttons[i].x
				&& x <= win_btn->plus_buttons[i].x + win_btn->plus_buttons[i].width
				&& y >= win_btn->plus_buttons[i].y
				&& y <= win_btn->plus_buttons[i].y + win_btn->plus_buttons[i].height)
			{
				prog->scene->ambient_light.color.x = fmin(1.0, prog->scene->ambient_light.color.x + 0.1);
				prog->scene->ambient_light.color.y = fmin(1.0, prog->scene->ambient_light.color.y + 0.1);
				prog->scene->ambient_light.color.z = fmin(1.0, prog->scene->ambient_light.color.z + 0.1);
				draw_button_window(prog);
				return (0);
			}
			if (x >= win_btn->minus_buttons[i].x
				&& x <= win_btn->minus_buttons[i].x + win_btn->minus_buttons[i].width
				&& y >= win_btn->minus_buttons[i].y
				&& y <= win_btn->minus_buttons[i].y + win_btn->minus_buttons[i].height)
			{
				prog->scene->ambient_light.color.x = fmax(0.0, prog->scene->ambient_light.color.x - 0.1);
				prog->scene->ambient_light.color.y = fmax(0.0, prog->scene->ambient_light.color.y - 0.1);
				prog->scene->ambient_light.color.z = fmax(0.0, prog->scene->ambient_light.color.z - 0.1);
				draw_button_window(prog);
				return (0);
			}
		}
		if (x >= win_btn->ambient_slider.x
			&& x <= win_btn->ambient_slider.x + win_btn->ambient_slider.width
			&& y >= win_btn->ambient_slider.y - 10
			&& y <= win_btn->ambient_slider.y + win_btn->ambient_slider.height + 10)
		{
			win_btn->ambient_slider.is_dragging = true;
			float ratio = (float)(x - win_btn->ambient_slider.x) / win_btn->ambient_slider.width;
			ratio = fmaxf(0.0, fminf(1.0, ratio));
			*win_btn->ambient_slider.value = ratio;
			draw_button_window(prog);
		}
		if (x >= win_btn->fov_slider.x
			&& x <= win_btn->fov_slider.x + win_btn->fov_slider.width
			&& y >= win_btn->fov_slider.y - 10
			&& y <= win_btn->fov_slider.y + win_btn->fov_slider.height + 10)
		{
			win_btn->fov_slider.is_dragging = true;
			float ratio = (float)(x - win_btn->fov_slider.x) / win_btn->fov_slider.width;
			ratio = fmaxf(0.0, fminf(1.0, ratio));
			float new_fov = ratio * (win_btn->fov_slider.max - win_btn->fov_slider.min) + win_btn->fov_slider.min;
			if (*win_btn->fov_slider.value != new_fov)
			{
				*win_btn->fov_slider.value = new_fov;
				reset_accumulation(prog);
				draw_button_window(prog);
			}
		}
	}
	return (0);
}

static int	handle_slider_move(int x, int y, t_prog *prog)
{
	t_win_button	*win_btn;

	(void)y;
	win_btn = prog->win_button;
	if (win_btn->ambient_slider.is_dragging)
	{
		float ratio = (float)(x - win_btn->ambient_slider.x) / win_btn->ambient_slider.width;
		ratio = fmaxf(0.0, fminf(1.0, ratio));
		*win_btn->ambient_slider.value = ratio;
		draw_button_window(prog);
	}
	else if (win_btn->fov_slider.is_dragging)
	{
		float	ratio = (float)(x - win_btn->fov_slider.x) / win_btn->fov_slider.width;
		ratio = fmaxf(0.0, fminf(1.0, ratio));
		float new_fov = ratio * (win_btn->fov_slider.max - win_btn->fov_slider.min) + win_btn->fov_slider.min;
		if (*win_btn->fov_slider.value != new_fov)
		{
			*win_btn->fov_slider.value = new_fov;
			reset_accumulation(prog);
			draw_button_window(prog);
		}
	}
	return (0);
}

static void	draw_button_window(t_prog *prog)
{
	t_win_button	*win_btn;
	t_data			img;
	int				i, x, y;
	int				color;
	float			slider_pos;
	char			fov_str[20];

	win_btn = prog->win_button;
	img.img = mlx_new_image(win_btn->mlx_ptr, win_btn->width, win_btn->height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	for (i = 0; i < TAB_COUNT; i++)
	{
		color = (win_btn->current_tab == (enum e_tab)i) ? ACTIVE_TAB_COLOR : TAB_COLOR;
		for (x = win_btn->tab_buttons[i].x; x < win_btn->tab_buttons[i].x + win_btn->tab_buttons[i].width; x++)
			for (y = win_btn->tab_buttons[i].y; y < win_btn->tab_buttons[i].y + win_btn->tab_buttons[i].height; y++)
				*(int *)(img.addr + y * img.line_length + x * (img.bits_per_pixel / 8)) = color;
		mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
			win_btn->tab_buttons[i].x + 10,
			win_btn->tab_buttons[i].y + TAB_HEIGHT / 2 + 5,
			TEXT_COLOR, win_btn->tab_buttons[i].text);
	}
	if (win_btn->current_tab == TAB_AMBIENT)
	{
		for (x = win_btn->ambient_slider.x; x < win_btn->ambient_slider.x + win_btn->ambient_slider.width; x++)
			for (y = win_btn->ambient_slider.y; y < win_btn->ambient_slider.y + win_btn->ambient_slider.height; y++)
				*(int*)(img.addr + y * img.line_length + x * (img.bits_per_pixel / 8)) = SLIDER_COLOR;
		slider_pos = win_btn->ambient_slider.x + (*win_btn->ambient_slider.value) * win_btn->ambient_slider.width;
		for (x = slider_pos - SLIDER_HANDLE_WIDTH / 2; x <= slider_pos + SLIDER_HANDLE_WIDTH / 2; x++)
			for (y = win_btn->ambient_slider.y - 5; y <= win_btn->ambient_slider.y + win_btn->ambient_slider.height + 5; y++)
				if (x >= 0 && x < win_btn->width && y >= 0 && y < win_btn->height)
					*(int *)(img.addr + y * img.line_length + x * (img.bits_per_pixel / 8)) = SLIDER_HANDLE_COLOR;
		mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
			20, win_btn->fov_slider.y - 20,
			TEXT_COLOR, "FOV");
		mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
			win_btn->fov_slider.x + win_btn->fov_slider.width + 10,
			win_btn->fov_slider.y + win_btn->fov_slider.height / 2 - 5,
			TEXT_COLOR, fov_str);
		for (x = win_btn->fov_slider.x; x < win_btn->fov_slider.x + win_btn->fov_slider.width; x++)
			for (y = win_btn->fov_slider.y; y < win_btn->fov_slider.y + win_btn->fov_slider.height; y++)
				*(int *)(img.addr + y * img.line_length + x * (img.bits_per_pixel / 8)) = SLIDER_COLOR;
		float	fov_ratio = (*win_btn->fov_slider.value - win_btn->fov_slider.min) / (win_btn->fov_slider.max - win_btn->fov_slider.min);
		slider_pos = win_btn->fov_slider.x + fov_ratio * win_btn->fov_slider.width;
		for (x = slider_pos - SLIDER_HANDLE_WIDTH / 2; x <= slider_pos + SLIDER_HANDLE_WIDTH / 2; x++)
			for (y = win_btn->fov_slider.y - 5; y <= win_btn->fov_slider.y + win_btn->fov_slider.height + 5; y++)
				if (x >= 0 && x < win_btn->width && y >= 0 && y < win_btn->height)
					*(int *)(img.addr + y * img.line_length + x * (img.bits_per_pixel / 8)) = SLIDER_HANDLE_COLOR;
	}
	mlx_put_image_to_window(win_btn->mlx_ptr, win_btn->win_ptr, img.img, 0, 0);
	mlx_destroy_image(win_btn->mlx_ptr, img.img);
}

static int key_hook_btn(int keycode, t_prog *prog)
{
	if (keycode == ESC)
		free_all(prog);
	return (0);
}

void	init_button_window(t_prog *prog)
{
	t_win_button	*win_btn;
	int				i;

	win_btn = ft_calloc(1, sizeof(t_win_button));
	prog->win_button = win_btn;
	win_btn->width = CONTROL_WINDOW_WIDTH;
	win_btn->height = prog->win_scene->height;
	win_btn->mlx_ptr = prog->win_scene->mlx_ptr;
	win_btn->win_ptr = mlx_new_window(win_btn->mlx_ptr,
			win_btn->width, win_btn->height, "Controls");
	int	tab_width = win_btn->width / TAB_COUNT;
	for (i = 0; i < TAB_COUNT; i++)
	{
		win_btn->tab_buttons[i] = (t_button)
		{
			.x = i * tab_width,
			.y = 0,
			.width = tab_width,
			.height = TAB_HEIGHT,
			.text = (char *[]){"Ambient", "TODO", "TODO", "TODO", "TODO"}[i],
			.func = NULL,
			.is_hovered = false
		};
	}
	for (i = 0; i < 3; i++)
	{
		win_btn->plus_buttons[i] = (t_button)
		{
			.x = 50 + i * 40,
			.y = 100,
			.width = 30,
			.height = 25,
			.text = "+",
			.func = NULL,
			.is_hovered = false
		};
		win_btn->minus_buttons[i] = (t_button)
		{
			.x = 50 + i * 40,
			.y = 130,
			.width = 30,
			.height = 25,
			.text = "-",
			.func = NULL,
			.is_hovered = false
		};
	}
	win_btn->ambient_slider = (t_slider)
	{
		.x = 20,
		.y = 50,
		.width = win_btn->width - 40,
		.height = 15,
		.min = 0.0,
		.max = 1.0,
		.value = (float *)&prog->scene->ambient_light.ratio,
		.is_dragging = false
	};
	win_btn->fov_slider = (t_slider)
	{
		.x = 20,
		.y = 100,
		.width = win_btn->width - 40,
		.height = 15,
		.min = 30.0,
		.max = 120.0,
		.value = (float *)&prog->scene->camera.fov,
		.is_dragging = false
	};
	mlx_key_hook(win_btn->win_ptr, key_hook_btn, prog);
	mlx_hook(win_btn->win_ptr, 17, 0, window_close, prog);
	mlx_hook(win_btn->win_ptr, 4, 1L << 2, (int (*)())handle_button_click, prog);
	mlx_hook(win_btn->win_ptr, 5, 1L << 3, (int (*)())handle_button_release, prog);
	mlx_hook(win_btn->win_ptr, 6, 1L << 6, (int (*)())handle_slider_move, prog);
	draw_button_window(prog);
}

#else

void	init_button_window(t_prog *prog)
{
	(void)prog;
}

#endif
