/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_transform.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:38:24 by mjuncker          #+#    #+#             */
/*   Updated: 2025/04/14 14:50:26 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include <math.h>

void	turn_yaw(t_camera *cam, float radian)
{
	t_vec3	new_forward;
	t_vec3	new_right;
	float	sin_angle;
	float	cos_angle;

	sin_angle = sinf(radian);
	cos_angle = cosf(radian);
	new_forward = (t_vec3){
		cam->forward.x * cos_angle + cam->forward.z * sin_angle,
		cam->forward.y,
		-cam->forward.x * sin_angle + cam->forward.z * cos_angle
	};

	new_right = (t_vec3){
		cam->right.x * cos_angle + cam->right.z * sin_angle,
		cam->right.y,
		-cam->right.x * sin_angle + cam->right.z * cos_angle
	};
	
	cam->forward = vec3_normalize(new_forward);
	cam->right = vec3_normalize(new_right);
	cam->up = vec3_normalize(vec3_cross(cam->right, cam->forward));
}

void	turn_pitch(t_camera *cam, float radian)
{
	t_vec3	new_forward;
	t_vec3	new_up;
	float	sin_angle;
	float	cos_angle;

	sin_angle = sinf(radian);
	cos_angle = cosf(radian);
	new_forward = (t_vec3){
		cam->forward.x,
		cam->forward.y * cos_angle - cam->forward.z * sin_angle,
		cam->forward.y * sin_angle + cam->forward.z * cos_angle
	};

	new_up = (t_vec3){
		cam->up.x,
		cam->up.y * cos_angle - cam->up.z * sin_angle,
		cam->up.y * sin_angle + cam->up.z * cos_angle
	};

	cam->forward = vec3_normalize(new_forward);
	cam->up = vec3_normalize(new_up);
	cam->right = vec3_normalize(vec3_cross(cam->forward, (t_vec3){0, 1, 0}));
}

void	turn_roll(t_camera *cam, float radian)
{
	t_vec3	new_right;
	t_vec3	new_up;

	new_right = vec3_add(
			vec3_mult(cam->up, -sin(radian)),
			vec3_mult(cam->right, cosf(radian))
			);
	new_up = vec3_add(
			vec3_mult(cam->up, cosf(radian)),
			vec3_mult(cam->right, sinf(radian))
			);
	cam->right = vec3_normalize(new_right);
	cam->up = vec3_normalize(new_up);
}
