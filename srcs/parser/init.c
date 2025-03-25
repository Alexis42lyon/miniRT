/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 14:47:16 by abidolet          #+#    #+#             */
/*   Updated: 2025/03/25 09:16:26 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>
#include <fcntl.h>

void	init(t_scene *scene, char **av)
{
	ft_bzero(scene, sizeof(t_scene));
	scene->fd = open(av[1], O_RDONLY);
	if (scene->fd == -1)
		free_all(NULL);
	parse(scene);
	print_scene(scene);
	ft_printf("%sNo error has been found\n%s", GREEN, RESET);
}
