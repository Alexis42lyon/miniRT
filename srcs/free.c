/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:21:55 by abidolet          #+#    #+#             */
/*   Updated: 2025/05/06 17:11:25 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "window.h"
#include "parser.h"

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
	if (parser->fd > 0)
		close(parser->fd);
	free(parser->line);
	free_arr((void **)parser->tokens);
	ft_lstclear(&parser->map, (void *)free_arr);
}

void	free_scene(t_prog *prog)
{
	free(prog->scene->spheres);
	free(prog->scene->planes);
	free(prog->scene->cylinders);
	free_parser(prog->parser);
}

void	free_all(t_prog *prog)
{
	free_scene(prog);
	free_win_scene(prog->win_scene);
	exit(0);
}
