/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_mat_info_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:51:48 by abidolet          #+#    #+#             */
/*   Updated: 2025/05/06 15:29:28 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "button_bonus.h"

#if SHOW_BUTTON

# include "window_bonus.h"
# include <math.h>
# include <stdio.h>
# include <string.h>

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

void	put_mat_info(t_win_button *win_btn, t_mat *mat)
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

#endif
