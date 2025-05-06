/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 09:48:40 by abidolet          #+#    #+#             */
/*   Updated: 2025/05/06 15:23:50 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUTTON_BONUS_H
# define BUTTON_BONUS_H

# include "window_bonus.h"

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
# define TEXT_Y_OFFSET 12

# define SLID_LIGHT_SELECT_H 40
# define SLID_LIGHT_RATIO_H 80
# define SLID_LIGHT_R_H 100
# define SLID_LIGHT_G_H 120
# define SLID_LIGHT_B_H 140

# define SLID_MAT_SELECT_H 40
# define SLID_MAT_RED_H 80
# define SLID_MAT_GREEN_H 100
# define SLID_MAT_BLUE_H 120
# define SLID_MAT_SHINI_H 140
# define SLID_MAT_ROUGH_H 160
# define SLID_MAT_SPEC_H 180
# define SLID_MAT_EMIS_H 200
# define SLID_MAT_CHECK_H 220
# define MAX_EMISSION_POWER 50.0f
# define MAX_MAT_SHININESS 1024

# define LIGHT_POS_BUTTON_WIDTH 20
# define LIGHT_POS_BUTTON_HEIGHT 15
# define LIGHT_POS_Y_POS 160
# define OFFSET_BUTTON 20

# define SPHERE_DIAM_Y_POS 180
# define SPHERE_COLOR_Y_POS 260
# define SPHERE_POS_Y_POS 100
# define SPHERE_BUTTON_WIDTH 20
# define SPHERE_BUTTON_HEIGHT 15
# define SPHERE_SLIDER_X_POS 120
# define SPHERE_MAT_SELEC_H 160
# define SLID_SPHERE_SELECT_H 70

# define PLANE_POS_Y_POS 100
# define PLANE_MAT_SELECT_H 160
# define SLID_PLANE_SELECT_H 70

# define CYLINDER_POS_Y_POS 100
# define CYLINDER_DIAMETER_Y_POS 180
# define CYLINDER_HEIGHT_Y_POS 200
# define CYLINDER_MAT_SELECT_H 160
# define SLID_CYLINDER_SELECT_H 70

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

typedef struct s_button
{
	int				x;
	int				y;
	int				width;
	int				height;
	t_button_func	func;
	bool			is_hovered;
}	t_button;

typedef struct s_sphere_buttons
{
	t_button	x_plus;
	t_button	x_minus;
	t_button	y_plus;
	t_button	y_minus;
	t_button	z_plus;
	t_button	z_minus;
	t_button	diameter_plus;
	t_button	diameter_minus;
}	t_sphere_buttons;

typedef struct s_plane_buttons
{
	t_button	x_plus;
	t_button	x_minus;
	t_button	y_plus;
	t_button	y_minus;
	t_button	z_plus;
	t_button	z_minus;
}	t_plane_buttons;

typedef struct s_cylinder_buttons
{
	t_button	x_plus;
	t_button	x_minus;
	t_button	y_plus;
	t_button	y_minus;
	t_button	z_plus;
	t_button	z_minus;
	t_button	diameter_plus;
	t_button	diameter_minus;
	t_button	height_plus;
	t_button	height_minus;
}	t_cylinder_buttons;

typedef struct s_cone_buttons
{
	t_button	x_plus;
	t_button	x_minus;
	t_button	y_plus;
	t_button	y_minus;
	t_button	z_plus;
	t_button	z_minus;
	t_button	diameter_plus;
	t_button	diameter_minus;
	t_button	height_plus;
	t_button	height_minus;
}	t_cone_buttons;

typedef struct s_light_button
{
	int		x;
	int		y;
	int		width;
	int		height;
	int		index;
	bool	is_selected;
}	t_light_button;

typedef struct s_tab_data
{
	enum e_tab	type;
	char		*name;
	t_button	*buttons;
	int			button_count;
	int			slider_count;
}	t_tab_data;

typedef struct s_light_pos_buttons
{
	t_button	x_plus;
	t_button	x_minus;
	t_button	y_plus;
	t_button	y_minus;
	t_button	z_plus;
	t_button	z_minus;
}	t_light_pos_buttons;

typedef struct s_win_button
{
	void				*win_ptr;
	void				*mlx_ptr;
	int					width;
	int					height;
	enum e_tab			current_tab;
	enum e_subtab		current_subtab;
	t_tab_data			tabs[TAB_COUNT];
	t_button			tab_buttons[TAB_COUNT];
	t_button			ratio_slider;
	int					is_dragging;
	t_light_pos_buttons	light_pos_buttons;
	t_sphere_buttons	sphere_buttons;
	t_plane_buttons		plane_buttons;
	t_cylinder_buttons	cylinder_buttons;
	t_cone_buttons		cone_buttons;
}	t_win_button;

// put_string_win.c
void	put_string_win(t_prog *prog, t_win_button *win_btn);

// draw_objects_controls.c
void	draw_objects_controls(t_prog *prog, t_win_button *win_btn, t_data img);

// put_string_objects.c
void	put_string_objects(t_prog *prog, t_win_button *win_btn);

// put_string_objects_utils.c
void	put_sphere_strings_utils(t_prog *prog, t_win_button *win_btn,
			t_sphere *sphere);
void	put_plane_string_utils(t_prog *prog, t_win_button *win_btn,
			t_plane *plane);
void	put_cylinder_strings_utils(t_prog *prog, t_win_button *win_btn,
			t_cylinder *cylinder);
void	put_cone_string_utils(t_prog *prog, t_win_button *win_btn,
			t_cylinder *cone);

// put_mat_info.c
void	put_mat_info(t_win_button *win_btn, t_mat *mat);

// handle_button_click.c
int		handle_button_click(int button, int x, int y, t_prog *prog);
bool	is_click_on_button(int x, int y, t_button *btn);

// handle_button_click_utils.c
void	handle_cylinder_click(int x, int y, t_prog *prog,
			t_win_button *win_btn);
void	handle_cone_click(int x, int y, t_prog *prog, t_win_button *win_btn);

// handle_mouse_move.c
int		handle_mouse_move(int x, int y, t_prog *prog);

// handle_mouse_move_utils.c
void	handle_mouse_move_objects(int y, float new_value,
			t_prog *prog, t_win_button *win_btn);

// handle_dragging_slider.c
void	handle_dragging_slider(int y, t_win_button *win_btn, t_prog *prog);

// draw.c
void	draw_button_window(t_prog *prog, t_win_button *win_btn);
void	draw_button(t_button *btn, t_data *img);
void	draw_slider(int y, float value, t_data *img);

// draw_utils.c
void	draw_light_pos_buttons(t_win_button *win_btn, t_data *img);
void	draw_tabs(t_data *img, t_win_button *win_btn);

// init_button.c
void	init_button(t_win_button *win_btn, t_button *btns[6]);
void	init_cylinder_buttons(t_win_button *win_btn);
void	init_cone_buttons(t_win_button *win_btn);

// init_button_utils.c
void	init_sphere_buttons(t_win_button *win_btn);
void	init_plane_buttons(t_win_button *win_btn);

// handle_tabs.c
void	handle_tabs(t_prog *prog, t_win_button *win_btn, int x, int y);

#endif
