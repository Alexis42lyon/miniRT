/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 14:47:25 by abidolet          #+#    #+#             */
/*   Updated: 2025/03/24 10:02:42 by abidolet         ###   ########.fr       */
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

void	free_all(t_scene *scene, char *msg)
{
	if (msg)
		ft_dprintf(2, "%sError\n%s\n%s", RED, msg, RESET);
	free_arr(scene->tokens);
	free(scene->spheres);
	free(scene->planes);
	free(scene->cylinders);
	close_window(scene);
}
