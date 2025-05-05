/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 09:48:40 by abidolet          #+#    #+#             */
/*   Updated: 2025/05/05 08:38:23 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUTTON_H
# define BUTTON_H

# include "window.h"

# define SHOW_BUTTON 1
# define TAB_COUNT 3
# define TAB_HEIGHT 30
# define TAB_COLOR 0x444444
# define ACTIVE_TAB_COLOR 0x666666
# define TEXT_COLOR 0xFFFFFF
# define CONTROL_WINDOW_WIDTH 300

# define SLIDER_WIDTH 150
# define SLIDER_HEIGHT 15
# define SLIDER_HANDLE_WIDTH 10
# define SLIDER_COLOR 0x888888
# define SLIDER_HANDLE_COLOR 0xFFFFFF
# define SLIDER_X_POS 120
# define TEXT_X_POS 20
# define TEXT_Y_OFFSET 11

# define SLIDER_AMBIENT_RATIO_HEIGHT 40
# define SLIDER_AMBIENT_RED_HEIGHT 60
# define SLIDER_AMBIENT_GREEN_HEIGHT 80
# define SLIDER_AMBIENT_BLUE_HEIGHT 100

# define LIGHT_BUTTON_WIDTH 90
# define LIGHT_BUTTON_HEIGHT 20
# define LIGHT_BUTTON_MARGIN 5
# define LIGHTS_PER_COLUMN 3
# define AMBIENT_LIGHT_HEIGHT 40
# define LIGHTS_START_HEIGHT 120
# define LIGHT_SELECTED_COLOR 0xAAAAAA
# define LIGHT_UNSELECTED_COLOR 0x666666

# define SLIDER_LIGHT_SELECTOR_HEIGHT 40
# define MAX_LIGHT_SELECTOR_WIDTH 150
# define SLIDER_LIGHT_RATIO_HEIGHT 80
# define SLIDER_LIGHT_RED_HEIGHT 100
# define SLIDER_LIGHT_GREEN_HEIGHT 120
# define SLIDER_LIGHT_BLUE_HEIGHT 140

# define SLIDER_MAT_SELECTOR_HEIGHT 40
# define SLIDER_MAT_RED_HEIGHT 80
# define SLIDER_MAT_GREEN_HEIGHT 100
# define SLIDER_MAT_BLUE_HEIGHT 120
# define SLIDER_MAT_SHININESS_HEIGHT 140
# define SLIDER_MAT_ROUGHNESS_HEIGHT 160
# define SLIDER_MAT_SPEC_COEF_HEIGHT 180
# define SLIDER_MAT_EMISSION_HEIGHT 200
# define SLIDER_MAT_CHECKER_HEIGHT 220
# define MAX_MAT_SHININESS 1000

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

typedef struct s_light_button
{
	int		x;
	int		y;
	int		width;
	int		height;
	int		index;
	bool	is_selected;
}	t_light_button;

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
}	t_win_button;

void	init_button_window(t_prog *prog);
void	draw_button_window(t_prog *prog, t_win_button *win_btn);
void	put_string_win(t_prog *prog, t_win_button *win_btn);
void	draw_slider(int y, float value, t_data *img);
void	handle_tabs(t_prog *prog, t_win_button *win_btn, int x, int y);
void	draw_light_button(t_data *img, t_light_button light_btn);
void	draw_light_selector_slider(t_prog *prog, t_data *img);

#endif
