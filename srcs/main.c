/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 21:07:28 by abidolet          #+#    #+#             */
/*   Updated: 2025/03/24 10:14:08 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

int	main(int ac, char **av)
{
	t_scene	scene;

	if (ac != 2)
	{
		ft_dprintf(2, "%sError\n%s\n%s", RED, "Wrong number of arguments", RESET);
		return (1);
	}
	ft_memset(&scene, 0, sizeof(t_scene));
	init(&scene, av);
	// start(&scene, av);
	free_all(&scene, NULL);
	return (0);
}
