/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:21:55 by abidolet          #+#    #+#             */
/*   Updated: 2025/04/17 16:05:17 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "window.h"
#include "parser.h"

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

void	print_exit(t_prog *prog, char *str)
{
	print_error(str);
	free_all(prog);
}

void	free_win_scene(t_win_scene *win)
{
	if (win->img.img)
		mlx_destroy_image(win->mlx_ptr, win->img.img);
	if (win->win_ptr)
		mlx_destroy_window(win->mlx_ptr, win->win_ptr);
	if (win->mlx_ptr)
	{
		mlx_destroy_display(win->mlx_ptr);
		free(win->mlx_ptr);
	}
	free(win->accumulation_data);
}

void	free_parser(t_parser *parser)
{
	if (parser->is_free == false)
	{
		if (parser->fd_mat > 0)
			close(parser->fd_mat);
		if (parser->fd > 0)
			close(parser->fd);
		free(parser->line);
		free_arr((void **)parser->tokens);
		ft_lstclear(&parser->map, (void *)free_arr);
		parser->is_free = true;
	}
}

void	free_all(t_prog *prog)
{
	free(prog->scene->materials);
	free(prog->scene->lights);
	free(prog->scene->spheres);
	free(prog->scene->planes);
	free(prog->scene->cylinders);
	free(prog->scene->cones);
	free_parser(prog->parser);
	if (prog->win_button->win_ptr)
		mlx_destroy_window(prog->win_button->mlx_ptr,
			prog->win_button->win_ptr);
	free_win_scene(prog->win_scene);
	exit(0);
}
