/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 08:45:57 by mjuncker          #+#    #+#             */
/*   Updated: 2025/04/25 11:46:20 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "miniRT.h"
#include "raytracer.h"
#include "window.h"
#include <strings.h>
#include <sys/time.h>
#include "libft/vector.h"

long	get_current_time_ms(void)
{
	long long		time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	return (time);
}

void	apply_effect(t_win_scene *win)
{
	int	i;
	int	j;

	j = 0;
	while (j < win->height)
	{
		i = 0;
		while (i < win->width)
		{
			if (win->img_flags & INVERT)
				invert_effect(win, i, j);
			if (win->img_flags & DEPTH_OF_FIELD)
				depth_of_field(win, i, j);	
			if (win->img_flags & DEPTH_MAP)
				depth_effect(win, i, j);
			i++;
		}
		j++;
	}
}

void	run_pipeline(t_prog *prog)
{
	t_viewport	vp;
	long	last_frame = -1;

	last_frame = get_current_time_ms();
	update_cam(prog);
	prog->scene->sky_color = vec3_mult(prog->scene->ambient_light.color, prog->scene->ambient_light.ratio);
	vp = viewport(prog->win_scene, prog->scene);
	
	render(vp, prog->scene);
	apply_effect(prog->win_scene);

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
	bzero(prog->win_scene->depth_map, prog->win_scene->height * prog->win_scene->width * sizeof(t_vec3));
	static int a = 2;
	if (prog->win_scene->paused || a == 1)
		return (0);
	run_pipeline(prog);
	display_frame(prog->win_scene, prog->scene);
	show_stats(prog);
	a++;
	return (0);
}
