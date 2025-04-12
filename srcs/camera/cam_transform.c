/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_transform.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:38:24 by mjuncker          #+#    #+#             */
/*   Updated: 2025/04/12 12:25:54 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include <math.h>

void	turn_yaw(t_camera *cam, float radian)
{
	t_vec3	new_forward;
	t_vec3	new_right;

	new_forward = vec3_add(
			vec3_mult(cam->forward, cosf(radian)),
			vec3_mult(cam->right, sinf(radian))
			);
	new_right = vec3_add(
			vec3_mult(vec3_mult(cam->forward, -1), sinf(radian)),
			vec3_mult(cam->right, cosf(radian))
			);
	cam->forward = vec3_normalize(new_forward);
	cam->right = vec3_normalize(new_right);
	cam->up = vec3_normalize(vec3_cross(cam->right, cam->forward));
}

void	turn_pitch(t_camera *cam, float radian)
{
	t_vec3	new_forward;
	t_vec3	new_up;

	new_forward = vec3_add(
			vec3_mult(cam->forward, cosf(radian)),
			vec3_mult(cam->up, -sinf(radian))
			);
	new_up = vec3_add(
			vec3_mult(cam->forward, sinf(radian)),
			vec3_mult(cam->up, cosf(radian))
			);
	cam->forward = vec3_normalize(new_forward);
	cam->up = vec3_normalize(new_up);
	cam->right = vec3_normalize(vec3_cross(cam->forward, cam->up));
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
