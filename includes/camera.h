/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:44:41 by mjuncker          #+#    #+#             */
/*   Updated: 2025/04/12 11:59:25 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "libft/vector.h"

typedef struct s_prog	t_prog;

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

	int		rotation_enable;
	int		last_x;
	int		last_y;

}	t_camera;
typedef struct s_win_scene	t_win_scene;

t_camera	new_camera(t_vec3 origin, t_vec3 forward, int fov);

void		turn_roll(t_camera *cam, float radian);
void		turn_pitch(t_camera *cam, float radian);
void		turn_yaw(t_camera *cam, float radian);

void		update_cam(t_prog *prog);

void		reset_cam_orientation(t_camera *cam);

void		print_cam(const t_camera *cam);

#endif