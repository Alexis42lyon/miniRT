/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 14:47:25 by abidolet          #+#    #+#             */
/*   Updated: 2025/03/25 08:53:08 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

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

int	close_window(void *mlx)
{
	t_scene	*scene;

	scene = (t_scene *)mlx;
	if (scene && scene->win->mlx)
	{
		if (scene->win)
			mlx_destroy_window(scene->win->mlx, scene->win);
		mlx_destroy_display(scene->win->mlx);
		free(scene->win->mlx);
	}
	exit(0);
}

void	free_all(t_scene *scene, const char *msg)
{
	if (msg)
		ft_dprintf(2, "%sError\n%s\n%s", RED, msg, RESET);
	close(scene->fd);
	free(scene->line);
	free(scene->spheres);
	free(scene->planes);
	free(scene->cylinders);
	ft_lstclear(&scene->map, (void *)free_arr);
	close_window(scene);
}

t_info	get_info(const char *file, int line, const char *func)
{
	return ((t_info){
		.file = file,
		.line = line,
		.function = func,
	});
}

void	check_mem(t_info info, t_scene *scene, void *mem, void **res)
{
	if (mem == NULL)
	{
		ft_dprintf(2, "%s%s:%d: %smalloc assertion failed in %s'%s'\n",
			GRAY, info.file, info.line, RED, RESET, info.function);
		free_all(scene, NULL);
	}
	*res = mem;
}
