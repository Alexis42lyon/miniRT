/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_string_objects_utils_bonus.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:43:47 by abidolet          #+#    #+#             */
/*   Updated: 2025/05/06 15:29:28 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "button_bonus.h"

#if SHOW_BUTTON

# include "window_bonus.h"
# include <math.h>
# include <stdio.h>
# include <string.h>

void	put_sphere_strings_utils(t_prog *prog, t_win_button *win_btn,
	t_sphere *sphere)
{
	char	buffer[50];

	snprintf(buffer, sizeof(buffer), "y:% -14.2f  +   -", sphere->origin.y);
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
		TEXT_X_POS, SPHERE_POS_Y_POS + OFFSET_BUTTON + TEXT_Y_OFFSET,
		TEXT_COLOR, buffer);
	snprintf(buffer, sizeof(buffer), "z:% -14.2f  +   -", sphere->origin.z);
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
		TEXT_X_POS, SPHERE_POS_Y_POS + OFFSET_BUTTON * 2 + TEXT_Y_OFFSET,
		TEXT_COLOR, buffer);
	snprintf(buffer, sizeof(buffer), "Mat: %s",
		prog->scene->materials[sphere->mat_idx].name);
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr, TEXT_X_POS,
		SPHERE_MAT_SELEC_H + TEXT_Y_OFFSET, TEXT_COLOR, buffer);
	snprintf(buffer, sizeof(buffer), "D:% -14.2f  +   -", sphere->radius * 2);
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
		TEXT_X_POS, SPHERE_DIAM_Y_POS + TEXT_Y_OFFSET, TEXT_COLOR, buffer);
}

void	put_plane_string_utils(t_prog *prog, t_win_button *win_btn,
	t_plane *plane)
{
	char	buffer[50];

	snprintf(buffer, sizeof(buffer), "z:% -14.2f  +   -", plane->origin.z);
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
		TEXT_X_POS, PLANE_POS_Y_POS + OFFSET_BUTTON * 2 + TEXT_Y_OFFSET,
		TEXT_COLOR, buffer);
	snprintf(buffer, sizeof(buffer), "Mat: %s",
		prog->scene->materials[plane->mat_idx].name);
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr, TEXT_X_POS,
		PLANE_MAT_SELECT_H + TEXT_Y_OFFSET, TEXT_COLOR, buffer);
}

void	put_cylinder_strings_utils(t_prog *prog, t_win_button *win_btn,
	t_cylinder *cylinder)
{
	char		buffer[50];

	snprintf(buffer, sizeof(buffer), "z:% -14.2f  +   -", cylinder->origin.z);
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
		TEXT_X_POS, CYLINDER_POS_Y_POS + OFFSET_BUTTON * 2 + TEXT_Y_OFFSET,
		TEXT_COLOR, buffer);
	snprintf(buffer, sizeof(buffer), "Mat: %s",
		prog->scene->materials[cylinder->mat_idx].name);
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr, TEXT_X_POS,
		CYLINDER_MAT_SELECT_H + TEXT_Y_OFFSET, TEXT_COLOR, buffer);
	snprintf(buffer, sizeof(buffer), "D:% -14.2f  +   -", cylinder->radius * 2);
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr, TEXT_X_POS,
		CYLINDER_DIAMETER_Y_POS + TEXT_Y_OFFSET, TEXT_COLOR, buffer);
	snprintf(buffer, sizeof(buffer), "H:% -14.2f  +   -", cylinder->height);
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
		TEXT_X_POS, CYLINDER_HEIGHT_Y_POS + TEXT_Y_OFFSET, TEXT_COLOR, buffer);
}

void	put_cone_string_utils(t_prog *prog, t_win_button *win_btn,
	t_cylinder *cone)
{
	char		buffer[50];

	snprintf(buffer, sizeof(buffer), "z:% -14.2f  +   -", cone->origin.z);
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
		TEXT_X_POS, CYLINDER_POS_Y_POS + OFFSET_BUTTON * 2 + TEXT_Y_OFFSET,
		TEXT_COLOR, buffer);
	snprintf(buffer, sizeof(buffer), "Mat: %s",
		prog->scene->materials[cone->mat_idx].name);
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr, TEXT_X_POS,
		CYLINDER_MAT_SELECT_H + TEXT_Y_OFFSET, TEXT_COLOR, buffer);
	snprintf(buffer, sizeof(buffer), "D:% -14.2f  +   -", cone->radius * 2);
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr, TEXT_X_POS,
		CYLINDER_DIAMETER_Y_POS + TEXT_Y_OFFSET, TEXT_COLOR, buffer);
	snprintf(buffer, sizeof(buffer), "H:% -14.2f  +   -", cone->height);
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
		TEXT_X_POS, CYLINDER_HEIGHT_Y_POS + TEXT_Y_OFFSET, TEXT_COLOR, buffer);
}

#endif
