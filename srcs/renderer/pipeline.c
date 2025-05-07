/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 08:45:57 by mjuncker          #+#    #+#             */
/*   Updated: 2025/05/07 08:55:57 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"
#include "window.h"

void	run_pipeline(t_prog *prog)
{
	t_viewport	vp;

	prog->scene->sky_color = (t_vec3){0.9, 0.976470588, 1};
	vp = viewport(prog->win_scene, prog->scene);
	render(vp, prog->scene);
}

void	display_frame(t_win_scene *win, t_scene *scene)
{
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img.img, 0, 0);
	ft_printf("\nframe " CYAN BOLD "%d" RESET
		" finished!\n", scene->frame_count);
	scene->frame_count++;
}

int	new_frame(t_prog *prog)
{
	ft_printf("\n");
	run_pipeline(prog);
	display_frame(prog->win_scene, prog->scene);
	return (0);
}
