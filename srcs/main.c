/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 21:07:28 by abidolet          #+#    #+#             */
/*   Updated: 2025/03/25 15:06:42 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "mlx.h"
#include "window.h"

int	main(int ac, char **av)
{
	t_scene	scene;
	t_win	win;
	t_prog	prog;

	if (ac != 2)
	{
		ft_dprintf(2, "%sError\n%s\n%s",
			RED, "Wrong number of arguments", RESET);
		return (1);
	}
	prog.win = &win;
	prog.scene = &scene;
	free_all(&prog);
	init(&scene, av);
	init_win(&win);
	free_all(NULL);
	return (0);
}
