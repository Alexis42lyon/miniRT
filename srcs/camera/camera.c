/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:46:23 by mjuncker          #+#    #+#             */
/*   Updated: 2025/04/14 16:33:45 by mjuncker         ###   ########.fr       */
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
	cam.movement_enable = 0;
	cam.movekeys = 0;
	cam.move_speed = 10;
	cam.focal_length = 1.0f;
	cam.sensibility = 0.2f;
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
	if (!cam->movement_enable)
		return ;
	mlx_mouse_get_pos(win->mlx_ptr, win->win_ptr, &x, &y);
	turn_yaw(cam, ((cam->last_x - x) * cam->sensibility) * (3.1415 / 180.0f));
	if (cam->forward.z < 0)
		turn_pitch(cam, ((cam->last_y - y) * cam->sensibility) * (3.1415 / 180.0f));
	else
		turn_pitch(cam, ((cam->last_y - y) * -cam->sensibility) * (3.1415 / 180.0f));
	if (cam->movekeys & MOVE_FORWARD)
		cam->origin = vec3_add(cam->origin, vec3_mult(cam->forward, 0.1));
	if (cam->movekeys & MOVE_BACKWARD)
		cam->origin = vec3_add(cam->origin, vec3_mult(cam->forward, -0.1));
	if (cam->movekeys & MOVE_RIGHT)
		cam->origin = vec3_add(cam->origin, vec3_mult(cam->right, 0.1));
	if (cam->movekeys & MOVE_LEFT)
		cam->origin = vec3_add(cam->origin, vec3_mult(cam->right, -0.1));
	if (cam->movekeys & MOVE_UP)
		cam->origin = vec3_add(cam->origin, vec3_mult(cam->up, 0.1));
	if (cam->movekeys & MOVE_DOWN)
		cam->origin = vec3_add(cam->origin, vec3_mult(cam->up, -0.1));

	reset_accumulation(prog);
		mlx_mouse_move(prog->win_scene->mlx_ptr, prog->win_scene->win_ptr, WIDTH / 2, HEIGHT / 2);
	mlx_mouse_get_pos(win->mlx_ptr, win->win_ptr, &x, &y);
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
	ft_printf(RED "\tfoward:\t");
	print_vec(cam->forward);
	ft_printf(GREEN "\tright:\t");
	print_vec(cam->right);
	ft_printf(BLUE "\tup:\t");
	print_vec(cam->up);
	ft_printf(GRAY "\tfov:%d%s\n", cam->fov, RESET);
}
