/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 14:47:16 by abidolet          #+#    #+#             */
/*   Updated: 2025/03/27 18:20:20 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>
#include <fcntl.h>

void	init(t_prog *prog, char **av)
{
	check_mem((t_info){__FILE__, __LINE__, __func__},
		malloc(sizeof(t_scene)), (void **)&prog->scene, prog);
	prog->scene->fd = open(av[1], O_RDONLY);
	if (prog->scene->fd == -1)
		free_all(prog);
	prog->scene->nb_spheres = 0;
	prog->scene->nb_planes = 0;
	prog->scene->nb_cylinders = 0;
	parse(prog);
	print_scene(prog->scene);
	ft_printf("%sNo error has been found\n%s", GREEN, RESET);
}
