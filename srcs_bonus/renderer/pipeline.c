/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 08:45:57 by mjuncker          #+#    #+#             */
/*   Updated: 2025/05/05 16:29:57 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "miniRT.h"
#include "raytracer.h"
#include "window.h"
#include <strings.h>
#include <sys/time.h>
#include "libft/vector.h"

void	anti_aliaser(t_win_scene *win);

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

	j = -1;
	while (++j < HEIGHT)
	{
		i = 0;
		while (i < WIDTH)
		{
			vp_filter(win, i, j);
			if (win->img_flags & GRAYSCALE)
				grayscale(win, i, j);
			if (win->img_flags & PIXEL)
				pixelate(win, i, j);
			if (win->img_flags & INVERT)
				invert_effect(win, i, j);
			if (win->img_flags & CHROMA)
				chromatic_aberation(win, i, j);
			if (win->img_flags & POSTERIZE)
				posterize(win, i, j);
			if (win->img_flags & DEPTH_OF_FIELD)
				depth_of_field(win, i, j);
			i++;
		}
	}
}

void	run_pipeline(t_prog *prog)
{
	t_viewport	vp;
	long		last_frame;

	last_frame = get_current_time_ms();
	update_cam(prog);
	vp = viewport(prog->win_scene, prog->scene);
	render(vp, prog->scene);
	anti_aliaser(prog->win_scene);
	apply_effect(prog->win_scene);
	prog->scene->total_render_time += get_current_time_ms() - last_frame;
}

void	new_pass(t_win_scene *win)
{
	int	i;
	int	j;

	j = 0;
	while (j < win->height)
	{
		i = 0;
		while (i < win->width)
		{
			ft_bzero(&win->pass[i + j * win->width], sizeof(t_render_pass));
			i++;
		}
		j++;
	}
}

int	new_frame(t_prog *prog)
{
	new_pass(prog->win_scene);
	if (prog->win_scene->paused)
		return (0);
	run_pipeline(prog);
	display_frame(prog->win_scene, prog->scene);
	show_stats(prog);
	return (0);
}
