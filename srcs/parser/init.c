/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 14:47:16 by abidolet          #+#    #+#             */
/*   Updated: 2025/03/24 23:44:38 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>
#include <fcntl.h>

void	init(t_scene *scene, char **av)
{
	scene->map = NULL;
	scene->mlx = NULL;
	scene->ambient_light.is_set = false;
	scene->camera.is_set = false;
	scene->light.is_set = false;
	scene->nb_spheres = 0;
	scene->nb_planes = 0;
	scene->nb_cylinders = 0;
	scene->fd = open(av[1], O_RDONLY);
	if (scene->fd == -1)
		free_all(scene, "Failed to open file");
	parse(scene);
	print_scene(scene);
	ft_printf("%sNo error has been found\n%s", GREEN, RESET);
}
