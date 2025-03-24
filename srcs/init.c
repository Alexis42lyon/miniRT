/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 14:47:16 by abidolet          #+#    #+#             */
/*   Updated: 2025/03/24 16:15:15 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>
#include <fcntl.h>

void	init(t_scene *scene, char **av)
{
	int		fd;
	char	*line;
	char	**tokens;
	t_list	*new_node;

	scene->mlx = NULL;
	scene->ambient_light.is_set = false;
	scene->camera.is_set = false;
	scene->light.is_set = false;
	scene->spheres = malloc(sizeof(t_sphere));
	if (!scene->spheres)
		free_all(scene, "Malloc failed");
	scene->planes = malloc(sizeof(t_plane));
	if (!scene->planes)
		free_all(scene, "Malloc failed");
	scene->cylinders = malloc(sizeof(t_cylinder));
	if (!scene->cylinders)
		free_all(scene, "Malloc failed");
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		ft_dprintf(2, "%sError\n%s\n%s", RED, "File not found", RESET);
		exit(1);
	}
	line = ft_get_next_line(fd);
	while (line)
	{
		tokens = ft_split(line, ' ');
		if (!tokens)
		{
			close(fd);
			free_all(scene, "Malloc failed");
		}
		new_node = ft_lstnew(tokens);
		if (!new_node)
		{
			close(fd);
			free_all(scene, "Malloc failed");
		}
		ft_lstadd_back(&scene->map, new_node);
		line = get_next_line(fd);
	}
	parse(scene, fd);
	ft_printf("%sNo error has been found\n%s", GREEN, RESET);
}
