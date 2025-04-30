#ifndef BUTTON_H
# define BUTTON_H

# include "window.h"

#define SHOW_BUTTON 1
#define TAB_COUNT 3
#define TAB_HEIGHT 30
#define TAB_COLOR 0x444444
#define ACTIVE_TAB_COLOR 0x666666
#define TEXT_COLOR 0xFFFFFF
#define CONTROL_WINDOW_WIDTH 300

#define SLIDER_WIDTH 150
#define SLIDER_HEIGHT 20
#define SLIDER_HANDLE_WIDTH 10
#define SLIDER_COLOR 0x888888
#define SLIDER_HANDLE_COLOR 0xFFFFFF
#define SLIDER_RATIO_AMBIENT_WIDTH 120
#define SLIDER_RATIO_AMBIENT_HEIGHT 75

typedef int	(*t_button_func)(t_prog *);

enum e_tab
{
	TAB_LIGHTS = 0,
	TAB_OBJECTS,
	TAB_MATERIALS,
};

enum e_subtab
{
	SUB_SPHERE,
	SUB_PLANE,
	SUB_CYLINDER,
	SUB_CONE,
	SUB_COUNT
};

typedef struct s_color_picker
{
	int		x;
	int		y;
	int		width;
	int		height;
	int		r;
	int		g;
	int		b;
	bool	is_dragging;
}	t_color_picker;

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

typedef struct s_tab_data
{
	enum e_tab	type;
	char		*name;
	t_button	*buttons;
	int			button_count;
	int			slider_count;
}	t_tab_data;

typedef struct s_win_button
{
	void			*win_ptr;
	void			*mlx_ptr;
	int				width;
	int				height;
	enum e_tab		current_tab;
	enum e_subtab	current_subtab;
	t_tab_data		tabs[TAB_COUNT];
	t_button		tab_buttons[TAB_COUNT];
	t_button		ratio_slider;
	int				is_dragging;
	int				index_color_picked_light;
}	t_win_button;

// button.c
void	init_button_window(t_prog *prog);
void	draw_button_window(t_prog *prog, t_win_button *win_btn);

// put_string_win.c
void	put_string_win(t_prog *prog, t_win_button *win_btn);

// slider.c
void	draw_slider(int x, int y, float value, t_data *img);
// tabs.c
void	handle_tabs(t_prog *prog, t_win_button *win_btn, int x, int y);

#endif
