/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 14:47:16 by abidolet          #+#    #+#             */
/*   Updated: 2025/03/28 21:10:47 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>
#include <fcntl.h>

void	init(t_prog *prog, char **av)
{
	check_mem((t_info){__FILE__, __LINE__, __func__},
		ft_calloc(sizeof(t_scene), 1), (void **)&prog->scene, NULL);
	prog->scene->fd = open(av[1], O_RDONLY);
	if (prog->scene->fd == -1)
		print_exit(prog, "File not found or cannot access to the file");
	parse(prog);
	print_scene(prog->scene);
	ft_printf("%sNo error has been found\n%s", GREEN, RESET);
}
