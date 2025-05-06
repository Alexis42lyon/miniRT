/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiaser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:32:28 by mjuncker          #+#    #+#             */
/*   Updated: 2025/05/05 16:57:03 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include "raytracer.h"

void	ssaa(t_win_scene *win, int i, int j)
{
	static pthread_mutex_t	image_mutex = PTHREAD_MUTEX_INITIALIZER;
	t_gaussien_dof			dof;

	if (SSAA_FACTOR <= 1)
	{
		set_pixel(&win->final_image, i, j, get_pixel(&win->img, i, j));
		return ;
	}
	dof = new_dof(win->scale_factor - 1);
	if (!dof.kernel)
		return ;
	create_blur_pixel(&dof, i, j, win);
	free(dof.kernel);
	dof.final = vec3_clamp(dof.final, 0, 1);
	pthread_mutex_lock(&image_mutex);
	set_pixel(&win->final_image, i / win->scale_factor,
		j / win->scale_factor, vec_to_int(dof.final));
	pthread_mutex_unlock(&image_mutex);
}

static void	*thread_routine(void *pcontext)
{
	t_thread_aliasing	*ctx;
	int					i;
	int					j;

	ctx = (t_thread_aliasing *)pcontext;
	j = ctx->start_row;
	while (j < ctx->end_row)
	{
		i = 0;
		while (i < ctx->win->width)
		{
			if (ctx->win->img_flags & ANTIALIASING)
				ssaa(ctx->win, i, j);
			else
				set_pixel(&ctx->win->final_image,
					i / ctx->win->scale_factor,
					j / ctx->win->scale_factor,
					get_pixel(&ctx->win->img, i, j));
			i++;
		}
		j++;
	}
	return (NULL);
}

void	anti_aliaser(t_win_scene *win)
{
	t_thread_aliasing	ctx[MAX_THREAD];
	int					row_per_th;
	size_t				i;

	i = 0;
	row_per_th = win->height / MAX_THREAD;
	while (i < MAX_THREAD)
	{
		ctx[i].id = i;
		ctx[i].start_row = i * row_per_th;
		ctx[i].end_row = (i + 1) * row_per_th;
		ctx[i].win = win;
		pthread_create(&ctx[i].th, NULL, thread_routine, (void *)&(ctx[i]));
		i++;
	}
	i = 0;
	while (i < MAX_THREAD)
	{
		pthread_join(ctx[i].th, NULL);
		i++;
	}
}
