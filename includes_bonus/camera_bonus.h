/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:44:41 by mjuncker          #+#    #+#             */
/*   Updated: 2025/05/06 15:23:54 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_BONUS_H
# define CAMERA_BONUS_H

# include "libft/vector.h"
# include <stdint.h>

# define MOVE_FORWARD 0b000001
# define MOVE_BACKWARD 0b000010
# define MOVE_LEFT 0b000100
# define MOVE_RIGHT 0b001000
# define MOVE_UP 0b010000
# define MOVE_DOWN 0b100000

typedef struct s_prog		t_prog;
typedef struct s_win_scene	t_win_scene;

typedef struct camera
{
	t_vec3	origin;

	t_vec3	forward;
	t_vec3	up;
	t_vec3	right;

	float	sensibility;
	float	move_speed;

	int		fov;
	float	focal_length;

	int		movement_enable;
	int		last_x;
	int		last_y;

	t_uint	movekeys;

}	t_camera;

t_camera	new_camera(t_vec3 origin, t_vec3 forward, int fov);

void		turn_roll(t_camera *cam, float radian);
void		turn_pitch(t_camera *cam, float radian);
void		turn_yaw(t_camera *cam, float radian);

void		update_cam(t_prog *prog);

void		reset_cam_orientation(t_camera *cam);

void		print_cam(const t_camera *cam);

int			mouse_down(int button, int x, int y, t_prog *prog);
int			mouse_up(int button, int x, int y, t_prog *prog);

int			key_down(int keycode, t_prog *prog);
int			key_up(int keycode, t_prog *prog);

#endif
