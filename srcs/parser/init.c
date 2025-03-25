/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 14:47:16 by abidolet          #+#    #+#             */
/*   Updated: 2025/03/25 08:57:21 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>
#include <fcntl.h>

void	init(t_scene *scene, char **av)
{
	ft_memset(scene, 0, sizeof(t_scene));
	scene->fd = open(av[1], O_RDONLY);
	if (scene->fd == -1)
		free_all(scene, "Failed to open file");
	parse(scene);
	print_scene(scene);
	ft_printf("%sNo error has been found\n%s", GREEN, RESET);
}
