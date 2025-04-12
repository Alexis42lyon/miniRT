/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:46:23 by mjuncker          #+#    #+#             */
/*   Updated: 2025/04/12 13:02:39 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "libft/io.h"
#include <math.h>
#include "window.h"

t_camera	new_camera(t_vec3 origin, t_vec3 forward, int fov)
{
	t_camera	cam;

	cam.fov = fov;
	cam.origin = origin;
	cam.forward = vec3_normalize(forward);
	cam.right = vec3_normalize(vec3_cross(cam.forward, (t_vec3){0, 1, 0}));
	cam.up = vec3_normalize(vec3_cross(cam.right, cam.forward));
	cam.rotation_enable = 0;
	cam.move_speed = 10;
	cam.sensibility = 0.3f;
	return (cam);
}

void	update_cam(t_prog *prog)
{
	int			x;
	int			y;
	t_camera	*cam;
	t_win_scene	*win;
	
	cam = &prog->scene->camera;
	win = prog->win_scene;
	if (!cam->rotation_enable)
		return ;
	mlx_mouse_get_pos(win->mlx_ptr, win->win_ptr, &x, &y);
	turn_yaw(cam, ((x - cam->last_x) * cam->sensibility) * (3.1415 / 180.0f));
	turn_pitch(cam, ((y - cam->last_y) * cam->sensibility) * (3.1415 / 180.0f));
	reset_accumulation(prog);
	// mlx_mouse_move(prog->win_scene->mlx_ptr, prog->win_scene->win_ptr, 0, 0);
	cam->last_x = x;
	cam->last_y = y;

}

void	reset_cam_orientation(t_camera *cam)
{
	cam->forward = (t_vec3){0, 0, -1};
	cam->up = (t_vec3){0, 1, 0};
	cam->right = (t_vec3){1, 0, 0};
}

void	print_cam(const t_camera *cam)
{
	ft_printf(GRAY "[LOG]: camera settings\n");
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
