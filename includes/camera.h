/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:44:41 by mjuncker          #+#    #+#             */
/*   Updated: 2025/04/11 13:25:18 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "libft/vector.h"

typedef struct camera
{
	t_vec3	origin;

	t_vec3	forward;
	t_vec3	up;
	t_vec3	right;

	int		fov;
	float	focal_length;
}	t_camera;

t_camera	new_camera(t_vec3 origin, t_vec3 forward, int fov);

void		turn_pitch(t_camera *cam, float radian);
void		turn_yaw(t_camera *cam, float radian);
void		reset_cam_orientation(t_camera *cam);
void		print_cam(const t_camera *cam);

#endif