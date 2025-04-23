/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 08:45:57 by mjuncker          #+#    #+#             */
/*   Updated: 2025/04/17 00:40:49 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "raytracer.h"
#include "window.h"
#include <stdlib.h>
#include <sys/time.h>

static long	get_current_time_ms(void)
{
	long long		time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	return (time);
}

void	run_pipeline(t_prog *prog)
{
	t_viewport	vp;
	static long	last_frame = -1;

	if (last_frame == -1)
		last_frame = get_current_time_ms();
	update_cam(prog);
	prog->scene->sky_color = vec3_mult(prog->scene->ambient_light.color, prog->scene->ambient_light.ratio);
	vp = viewport(prog->win_scene, prog->scene);
	render(vp, prog->scene);
	prog->scene->total_render_time += get_current_time_ms() - last_frame;
	last_frame = get_current_time_ms();
}

void	display_frame(t_win_scene *win, t_scene *scene)
{
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img.img, 0, 0);
	scene->frame_count++;
}

void	show_stats(t_prog *prog)
{
	if ((prog->scene->vp_flags & SHOW_FRAME) == 0)
		return ;
	ft_log(LOG, "frame " CYAN BOLD "%d" RESET
		" render in" CYAN BOLD " %ums" RESET, prog->scene->frame_count -1, prog->scene->total_render_time / prog->scene->frame_count -1);
}

int	new_frame(t_prog *prog)
{
	static int a = 2;
	if (prog->win_scene->paused || a == 1)
		return (0);
	run_pipeline(prog);
	display_frame(prog->win_scene, prog->scene);
	show_stats(prog);
	a++;
	return (0);
}
