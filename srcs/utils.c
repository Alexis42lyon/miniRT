/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 14:47:25 by abidolet          #+#    #+#             */
/*   Updated: 2025/03/24 15:52:13 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void	free_arr(char **arr)
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
	if (scene && scene->mlx)
	{
		if (scene->win)
			mlx_destroy_window(scene->mlx, scene->win);
		mlx_destroy_display(scene->mlx);
		free(scene->mlx);
	}
	exit(0);
}

void	free_all(t_scene *scene, const char *msg)
{
	if (msg)
		ft_dprintf(2, "%sError\n%s\n%s", RED, msg, RESET);
	free(scene->spheres);
	free(scene->planes);
	free(scene->cylinders);

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

void	*check_mem(t_scene *scene, void *mem, const char *message, t_info info)
{
	if (mem == NULL)
	{
		ft_dprintf(2, "%s%s:%d: %s%s in %s'%s'\n",
			GRAY, info.file, info.line, RED, message, RESET, info.function);
		free_all(scene, NULL);
	}
	return (mem);
}

void	check_bool(t_scene *scene, bool ok, const char *message, t_info info)
{
	if (ok == false)
	{
		ft_dprintf(2, "%s%s:%d: %sError\n%s in %s'%s'\n",
			GRAY, info.file, info.line, RED, message, RESET, info.function);
		free_all(scene, message);
	}
}
