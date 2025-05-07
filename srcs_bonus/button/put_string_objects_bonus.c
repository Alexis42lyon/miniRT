/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_string_objects_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:40:53 by abidolet          #+#    #+#             */
/*   Updated: 2025/05/07 09:03:45 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "button_bonus.h"

#if SHOW_BUTTON

# include <stdio.h>

static void	put_sphere_strings(t_prog *prog, t_win_button *win_btn)
{
	t_sphere	*sphere;
	char		buffer[50];

	if (prog->scene->nb_spheres == 0)
	{
		mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
			TEXT_X_POS, SPHERE_POS_Y_POS + TEXT_Y_OFFSET,
			TEXT_COLOR, "No spheres");
		return ;
	}
	snprintf(buffer, sizeof(buffer), "Sphere %ld/%ld",
		prog->scene->selected_sphere + 1, prog->scene->nb_spheres);
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
		TEXT_X_POS, SLID_SPHERE_SELECT_H + 10, TEXT_COLOR, buffer);
	sphere = &prog->scene->spheres[prog->scene->selected_sphere];
	snprintf(buffer, sizeof(buffer), "x:% -14.2f  +   -", sphere->origin.x);
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
		TEXT_X_POS, SPHERE_POS_Y_POS + TEXT_Y_OFFSET, TEXT_COLOR, buffer);
	put_sphere_strings_utils(prog, win_btn, sphere);
}

static void	put_plane_strings(t_prog *prog, t_win_button *win_btn)
{
	t_plane	*plane;
	char	buffer[50];

	if (prog->scene->nb_planes == 0)
	{
		mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
			TEXT_X_POS, PLANE_POS_Y_POS + TEXT_Y_OFFSET,
			TEXT_COLOR, "No planes");
		return ;
	}
	snprintf(buffer, sizeof(buffer), "Plane %ld/%ld",
		prog->scene->selected_plane + 1, prog->scene->nb_planes);
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
		TEXT_X_POS, SLID_PLANE_SELECT_H + 10, TEXT_COLOR, buffer);
	plane = &prog->scene->planes[prog->scene->selected_plane];
	snprintf(buffer, sizeof(buffer), "x:% -14.2f  +   -", plane->origin.x);
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
		TEXT_X_POS, PLANE_POS_Y_POS + TEXT_Y_OFFSET, TEXT_COLOR, buffer);
	snprintf(buffer, sizeof(buffer), "y:% -14.2f  +   -", plane->origin.y);
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
		TEXT_X_POS, PLANE_POS_Y_POS + OFFSET_BUTTON + TEXT_Y_OFFSET,
		TEXT_COLOR, buffer);
	put_plane_string_utils(prog, win_btn, plane);
}

static void	put_cylinder_strings(t_prog *prog, t_win_button *win_btn)
{
	t_cylinder	*cylinder;
	char		buffer[50];

	if (prog->scene->nb_cylinders == 0)
	{
		mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
			TEXT_X_POS, CYLINDER_POS_Y_POS + TEXT_Y_OFFSET,
			TEXT_COLOR, "No cylinders");
		return ;
	}
	snprintf(buffer, sizeof(buffer), "Cylinder %ld/%ld",
		prog->scene->selected_cylinder + 1, prog->scene->nb_cylinders);
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
		TEXT_X_POS, SLID_CYLINDER_SELECT_H + 10, TEXT_COLOR, buffer);
	cylinder = &prog->scene->cylinders[prog->scene->selected_cylinder];
	snprintf(buffer, sizeof(buffer), "x:% -14.2f  +   -", cylinder->origin.x);
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
		TEXT_X_POS, CYLINDER_POS_Y_POS + TEXT_Y_OFFSET, TEXT_COLOR, buffer);
	snprintf(buffer, sizeof(buffer), "y:% -14.2f  +   -", cylinder->origin.y);
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
		TEXT_X_POS, CYLINDER_POS_Y_POS + OFFSET_BUTTON + TEXT_Y_OFFSET,
		TEXT_COLOR, buffer);
	put_cylinder_strings_utils(prog, win_btn, cylinder);
}

static void	put_cone_strings(t_prog *prog, t_win_button *win_btn)
{
	t_cylinder	*cone;
	char		buffer[50];

	if (prog->scene->nb_cones == 0)
	{
		mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
			TEXT_X_POS, CYLINDER_POS_Y_POS + TEXT_Y_OFFSET,
			TEXT_COLOR, "No cones");
		return ;
	}
	snprintf(buffer, sizeof(buffer), "Cone %ld/%ld",
		prog->scene->selected_cone + 1, prog->scene->nb_cones);
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
		TEXT_X_POS, SLID_CYLINDER_SELECT_H + 10, TEXT_COLOR, buffer);
	cone = &prog->scene->cones[prog->scene->selected_cone];
	snprintf(buffer, sizeof(buffer), "x:% -14.2f  +   -", cone->origin.x);
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
		TEXT_X_POS, CYLINDER_POS_Y_POS + TEXT_Y_OFFSET, TEXT_COLOR, buffer);
	snprintf(buffer, sizeof(buffer), "y:% -14.2f  +   -", cone->origin.y);
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
		TEXT_X_POS, CYLINDER_POS_Y_POS + OFFSET_BUTTON + TEXT_Y_OFFSET,
		TEXT_COLOR, buffer);
	put_cone_string_utils(prog, win_btn, cone);
}

void	put_string_objects(t_prog *prog, t_win_button *win_btn)
{
	const int	stw = (win_btn->width - 30) / SUB_COUNT;
	int			sx;
	int			i;

	sx = 15;
	i = -1;
	while (++i < SUB_COUNT)
	{
		mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr, sx + 5,
			TAB_HEIGHT + 15, TEXT_COLOR,
			(char *[]){"Sphere", "Plane", "Cylinder", "Cone"}[i]);
		sx += stw + 5;
	}
	if (win_btn->current_subtab == SUB_SPHERE)
		put_sphere_strings(prog, win_btn);
	else if (win_btn->current_subtab == SUB_PLANE)
		put_plane_strings(prog, win_btn);
	else if (win_btn->current_subtab == SUB_CYLINDER)
		put_cylinder_strings(prog, win_btn);
	else if (win_btn->current_subtab == SUB_CONE)
		put_cone_strings(prog, win_btn);
}

#endif
