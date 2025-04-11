/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:19:17 by abidolet          #+#    #+#             */
/*   Updated: 2025/04/11 12:24:21 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "window.h"
#include "miniRT.h"
#include "parser.h"
#include <stdio.h>

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
