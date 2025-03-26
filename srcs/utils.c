/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 14:47:25 by abidolet          #+#    #+#             */
/*   Updated: 2025/03/25 09:55:49 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include <miniRT.h>
#include <stdio.h>

void	free_arr(void **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	free_win(t_win *win)
{
	free(win->name);
	
	
}

void	free_scene(t_scene *scene)
{
	close(scene->fd);
	free(scene->line);
	free(scene->spheres);
	free(scene->planes);
	free(scene->cylinders);
	ft_lstclear(&scene->map, (void *)free_arr);
}

void	free_all(t_prog *prog_set)
{
	static t_prog	*prog = NULL;

	if (prog_set)
	{
		prog = prog_set;
		return ;
	}
	free_scene(prog->scene);

	exit(0);
	//free_win(prog->win);
	//close_window(prog->scene);
}

t_info	get_info(const char *file, int line, const char *func)
{
	return ((t_info){
		.file = file,
		.line = line,
		.function = func,
	});
}

void	check_mem(t_info info, void *mem, void **res)
{
	if (mem == NULL)
	{
		ft_dprintf(2, "%s%s:%d: %smalloc assertion failed in %s'%s'\n",
			GRAY, info.file, info.line, RED, RESET, info.function);
		free_all(NULL);
	}
	*res = mem;
}
