/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 21:07:28 by abidolet          #+#    #+#             */
/*   Updated: 2025/03/25 08:54:52 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

int	main(int ac, char **av)
{
	t_scene	scene;
	t_win	win;

	if (ac != 2)
	{
		ft_dprintf(2, "%sError\n%s\n%s",
			RED, "Wrong number of arguments", RESET);
		return (1);
	}
	ft_memset(&scene, 0, sizeof(t_scene));
	scene.win = &win;
	init(&scene, av);
	// start(&scene, av);
	// create_img(&win);
	free_all(&scene, NULL);
	return (0);
}
