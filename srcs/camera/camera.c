/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:46:23 by mjuncker          #+#    #+#             */
/*   Updated: 2025/04/11 16:08:55 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "libft/io.h"
#include <math.h>

t_camera	new_camera(t_vec3 origin, t_vec3 forward, int fov)
{
	t_camera	cam;

	cam.fov = fov;
	cam.origin = origin;
	cam.forward = vec3_normalize(forward);
	cam.right = vec3_normalize(vec3_cross(cam.forward, (t_vec3){0, 1, 0}));
	cam.up = vec3_normalize(vec3_cross(cam.right, cam.forward));
	return (cam);
}

void	reset_cam_orientation(t_camera *cam)
{
	cam->forward = (t_vec3){0, 0, -1};
	cam->up = (t_vec3){0, 1, 0};
	cam->right = (t_vec3){1, 0, 0};
}

void	print_cam(const t_camera *cam)
{
	ft_printf(GRAY "\n[LOG]: camera settings\n");
	ft_printf("\torigin:");
	print_vec(cam->origin);
	ft_printf("\tfoward:");
	print_vec(cam->forward);
	ft_printf("\tright:");
	print_vec(cam->right);
	ft_printf("\tup:");
	print_vec(cam->up);
	ft_printf("\tfov:%d%s\n", cam->fov, RESET);
}
