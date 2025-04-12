/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 08:45:57 by mjuncker          #+#    #+#             */
/*   Updated: 2025/04/12 10:33:32 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"
#include "window.h"

void	run_pipeline(t_prog *prog)
{
	t_viewport	vp;

	prog->scene->sky_color = vec3_mult(prog->scene->ambient_light.color, prog->scene->ambient_light.ratio);
	vp = viewport(prog->win_scene, prog->scene);
	render(vp, prog->scene);
	// anti_aliaser(vp, prog->scene);
}

void	display_frame(t_win_scene *win, t_scene *scene)
{
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img.img, 0, 0);
	ft_printf("\nframe " CYAN BOLD "%d" RESET
		" finished!\n", scene->frame_count);
	scene->frame_count++;
}

// void	show_stats(t_prog *prog)
// {
	
// }

int	new_frame(t_prog *prog)
{
	ft_printf("\n");
	run_pipeline(prog);
	display_frame(prog->win_scene, prog->scene);
	// show_stats(prog);
	return (0);
}
