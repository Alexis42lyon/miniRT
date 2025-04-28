/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:19:17 by abidolet          #+#    #+#             */
/*   Updated: 2025/04/25 11:46:31 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io.h"
#include "window.h"
#include "miniRT.h"
#include <stdio.h>

void	reset_accumulation(t_prog *prog)
{
	if (prog->scene->frame_count > 2)
		ft_log(WARNING, "accumulation restarting");
	ft_bzero(prog->win_scene->accumulation_data,
		prog->win_scene->height * prog->win_scene->width * sizeof(t_vec3));
	prog->scene->frame_count = 1;
	prog->scene->total_render_time = 0;
	prog->scene->max_render_time = 0;
	prog->scene->min_render_time = 0;
}

void	session_result(const t_scene *scene)
{
	printf(CYAN "\n\n-------------------------\nsession result:\n");
	printf(CYAN "\n[render times]:\n");
	printf(GRAY "\taverage:%ums    ",
		scene->total_render_time / (scene->frame_count - 1));
	printf(GRAY "min:%ums    ", scene->min_render_time);
	printf(GRAY "max:%ums\n", scene->max_render_time);
	printf(CYAN "\n[accumulation data]\n");
	printf(GRAY "\ttotal-render-time:%ums\n", scene->total_render_time);
	printf(GRAY "\ttotal-frame-count:%u\n", scene->frame_count);
	printf(CYAN "\n-------------------------\n\n");
}

void	check_mem(t_info info, void *mem, void **res, t_prog *prog)
{
	if (mem == NULL)
	{
		ft_dprintf(2, "%s%s:%d: %smalloc assertion failed in %s'%s'\n",
			GRAY, info.file, info.line, RED, RESET, info.function);
		if (prog)
			free_all(prog);
		else
			exit(1);
	}
	*res = mem;
}

void	show_progress(int current, int max, const char *name)
{
	int		i;
	float	progress;

	ft_printf(BLUE "[LOG]: " RESET);
	ft_printf(BOLD "%s: [", name);
	progress = ((double)current / (double)max) * 100;
	i = 0;
	while (i * 5 < progress)
	{
		ft_printf(RESET "=" RESET);
		i++;
	}
	while (i < 20)
	{
		ft_printf(GRAY "-");
		i++;
	}
	ft_printf(RESET BOLD "] " RESET "\033[?25h\r", (int)progress);
	if (current >= max)
		ft_printf("\n");
}
