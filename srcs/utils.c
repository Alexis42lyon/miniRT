/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 14:47:25 by abidolet          #+#    #+#             */
/*   Updated: 2025/03/27 17:28:16 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
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
	if (win->img.img)
		mlx_destroy_image(win->mlx_ptr, win->img.img);
	if (win->win_ptr)
		mlx_destroy_window(win->mlx_ptr, win->win_ptr);
	if (win->mlx_ptr)
	{
		mlx_destroy_display(win->mlx_ptr);
		free(win->mlx_ptr);
	}
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
	free_win(prog->win);
	exit(0);
}

void	check_mem(t_info info, void *mem, void **res, t_prog *prog)
{
	if (mem == NULL)
	{
		ft_dprintf(2, "%s%s:%d: %smalloc assertion failed in %s'%s'\n",
			GRAY, info.file, info.line, RED, RESET, info.function);
		free_all(prog);
	}
	*res = mem;
}
