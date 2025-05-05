/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_string_win.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:20:06 by abidolet          #+#    #+#             */
/*   Updated: 2025/05/06 00:28:05 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "button.h"

#if SHOW_BUTTON

# include "window.h"
# include <math.h>
# include <stdio.h>
# include <string.h>

static void	put_sphere_strings_utils(t_prog *prog, t_win_button *win_btn,
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

static void	put_plane_string_utils(t_prog *prog, t_win_button *win_btn,
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

static void	put_cylinder_strings_utils(t_prog *prog, t_win_button *win_btn,
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

static void	put_cone_string_utils(t_prog *prog, t_win_button *win_btn,
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

static void	put_mat_info_utils(t_win_button *win_btn, t_mat *mat)
{
	if (mat->use_checker)
		mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr, TEXT_X_POS,
			SLID_MAT_CHECK_H + TEXT_Y_OFFSET, TEXT_COLOR,
			"Checker: ON");
	else
		mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr, TEXT_X_POS,
			SLID_MAT_CHECK_H + TEXT_Y_OFFSET, TEXT_COLOR,
			"Checker: OFF");
}

static void	put_mat_info(t_win_button *win_btn, t_mat *mat)
{
	char	buffer[50];

	snprintf(buffer, sizeof(buffer), "Red: %d", (int)(mat->albedo.x * 255));
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr, TEXT_X_POS,
		SLID_MAT_RED_H + TEXT_Y_OFFSET, TEXT_COLOR, buffer);
	snprintf(buffer, sizeof(buffer), "Green: %d", (int)(mat->albedo.y * 255));
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr, TEXT_X_POS,
		SLID_MAT_GREEN_H + TEXT_Y_OFFSET, TEXT_COLOR, buffer);
	snprintf(buffer, sizeof(buffer), "Blue: %d", (int)(mat->albedo.z * 255));
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
		TEXT_X_POS, SLID_MAT_BLUE_H + TEXT_Y_OFFSET, TEXT_COLOR, buffer);
	snprintf(buffer, sizeof(buffer), "Shininess: %d", mat->shyniness);
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr, TEXT_X_POS,
		SLID_MAT_SHINI_H + TEXT_Y_OFFSET, TEXT_COLOR, buffer);
	snprintf(buffer, sizeof(buffer), "Roughness: %.2f", mat->roughtness);
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr, TEXT_X_POS,
		SLID_MAT_ROUGH_H + TEXT_Y_OFFSET, TEXT_COLOR, buffer);
	snprintf(buffer, sizeof(buffer), "Spec Coef: %.2f", mat->spec_coef);
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr, TEXT_X_POS,
		SLID_MAT_SPEC_H + TEXT_Y_OFFSET, TEXT_COLOR, buffer);
	snprintf(buffer, sizeof(buffer), "Emission: %.2f", mat->emission_power);
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr, TEXT_X_POS,
		SLID_MAT_EMIS_H + TEXT_Y_OFFSET, TEXT_COLOR, buffer);
	put_mat_info_utils(win_btn, mat);
}

static void	put_string_materials(t_prog *prog, t_win_button *win_btn)
{
	char	buffer[50];
	t_mat	*mat;

	if (prog->scene->nb_materials == 0)
	{
		mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
			TEXT_X_POS, SLID_MAT_SELECT_H + TEXT_Y_OFFSET,
			TEXT_COLOR, "No materials");
		return ;
	}
	if (prog->scene->selected_material < prog->scene->nb_materials)
	{
		snprintf(buffer, sizeof(buffer), "%s",
			prog->scene->materials[prog->scene->selected_material].name);
		mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
			TEXT_X_POS, SLID_MAT_SELECT_H + TEXT_Y_OFFSET,
			TEXT_COLOR, buffer);
		mat = &prog->scene->materials[prog->scene->selected_material];
		put_mat_info(win_btn, mat);
	}
}

static void	put_string_tab_objects(t_win_button *win_btn)
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
}

static void	put_light_info(t_win_button *win_btn, t_light_source *light)
{
	char	buffer[50];

	snprintf(buffer, sizeof(buffer), "Red: %d",
		(int)(light->material.albedo.x * 255));
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
		TEXT_X_POS, SLID_LIGHT_R_H + TEXT_Y_OFFSET, TEXT_COLOR, buffer);
	snprintf(buffer, sizeof(buffer), "Green: %d",
		(int)(light->material.albedo.y * 255));
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
		TEXT_X_POS, SLID_LIGHT_G_H + TEXT_Y_OFFSET, TEXT_COLOR, buffer);
	snprintf(buffer, sizeof(buffer), "Blue: %d",
		(int)(light->material.albedo.z * 255));
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
		TEXT_X_POS, SLID_LIGHT_B_H + TEXT_Y_OFFSET, TEXT_COLOR, buffer);
	snprintf(buffer, sizeof(buffer), "x:% -14.2f  +   -", light->origin.x);
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
		TEXT_X_POS, SLID_LIGHT_B_H + 20 + TEXT_Y_OFFSET, TEXT_COLOR, buffer);
	snprintf(buffer, sizeof(buffer), "y:% -14.2f  +   -", light->origin.y);
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
		TEXT_X_POS, SLID_LIGHT_B_H + 40 + TEXT_Y_OFFSET, TEXT_COLOR, buffer);
	snprintf(buffer, sizeof(buffer), "z:% -14.2f  +   -", light->origin.z);
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
		TEXT_X_POS, SLID_LIGHT_B_H + 60 + TEXT_Y_OFFSET, TEXT_COLOR, buffer);
}

static void	put_ambient_info(t_ambient_light *light, t_win_button *win_btn)
{
	char	buffer[50];

	snprintf(buffer, sizeof(buffer), "Ratio: %.2f", light->ratio);
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
		TEXT_X_POS, SLID_LIGHT_RATIO_H + TEXT_Y_OFFSET, TEXT_COLOR, buffer);
	snprintf(buffer, sizeof(buffer), "Red: %d", (int)(light->color.x * 255));
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
		TEXT_X_POS, SLID_LIGHT_R_H + TEXT_Y_OFFSET, TEXT_COLOR, buffer);
	snprintf(buffer, sizeof(buffer), "Green: %d", (int)(light->color.y * 255));
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
		TEXT_X_POS, SLID_LIGHT_G_H + TEXT_Y_OFFSET, TEXT_COLOR, buffer);
	snprintf(buffer, sizeof(buffer), "Blue: %d", (int)(light->color.z * 255));
	mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
		TEXT_X_POS, SLID_LIGHT_B_H + TEXT_Y_OFFSET, TEXT_COLOR, buffer);
}

static void	put_string_lights(t_prog *prog, t_win_button *win_btn)
{
	char			buffer[50];
	t_light_source	*light;

	if (prog->scene->selected_light == 0)
	{
		mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
			TEXT_X_POS, SLID_LIGHT_SELECT_H + TEXT_Y_OFFSET,
			TEXT_COLOR, "Ambient Light");
		put_ambient_info(&prog->scene->ambient_light, win_btn);
	}
	else
	{
		snprintf(buffer, sizeof(buffer),
			"Light %ld", prog->scene->selected_light);
		mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
			TEXT_X_POS, SLID_LIGHT_SELECT_H + TEXT_Y_OFFSET,
			TEXT_COLOR, buffer);
		light = &prog->scene->lights[prog->scene->selected_light - 1];
		snprintf(buffer, sizeof(buffer), "Ratio: %.2f", light->ratio);
		mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
			TEXT_X_POS, SLID_LIGHT_RATIO_H + TEXT_Y_OFFSET, TEXT_COLOR, buffer);
		put_light_info(win_btn, light);
	}
}

void	put_string_objects(t_prog *prog, t_win_button *win_btn)
{
	put_string_tab_objects(win_btn);
	if (win_btn->current_subtab == SUB_SPHERE)
		put_sphere_strings(prog, win_btn);
	else if (win_btn->current_subtab == SUB_PLANE)
		put_plane_strings(prog, win_btn);
	else if (win_btn->current_subtab == SUB_CYLINDER)
		put_cylinder_strings(prog, win_btn);
	else if (win_btn->current_subtab == SUB_CONE)
		put_cone_strings(prog, win_btn);
}

void	put_string_win(t_prog *prog, t_win_button *win_btn)
{
	int	i;

	i = -1;
	while (++i < TAB_COUNT)
	{
		mlx_string_put(win_btn->mlx_ptr, win_btn->win_ptr,
			win_btn->tab_buttons[i].x + 30 - i * 2,
			win_btn->tab_buttons[i].y + TAB_HEIGHT / 2 + 5,
			TEXT_COLOR, win_btn->tab_buttons[i].text);
	}
	if (win_btn->current_tab == TAB_LIGHTS)
		put_string_lights(prog, win_btn);
	else if (win_btn->current_tab == TAB_OBJECTS)
		put_string_objects(prog, win_btn);
	else if (win_btn->current_tab == TAB_MATERIALS)
		put_string_materials(prog, win_btn);
}

#endif
