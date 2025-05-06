/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_struct_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 10:22:49 by abidolet          #+#    #+#             */
/*   Updated: 2025/05/06 14:03:12 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_bonus.h"

#if SHOW_SRUCT

# include "parser.h"
# include <stdio.h>

static void	print_lights(const t_scene *scene)
{
	size_t	i;

	printf(CYAN "\n[Lights: %zu]" RESET "\n", scene->nb_lights);
	if (scene->lights)
	{
		i = 0;
		while (i < scene->nb_lights)
		{
			printf(YELLOW "- Lights %zu:" RESET "\n", i + 1);
			printf("  Origin:\t" GREEN "(%.2lf, %.2lf, %.2lf)" RESET "\n",
				scene->lights[i].origin.x, scene->lights[i].origin.y,
				scene->lights[i].origin.z);
			printf("  Ratio:\t" CYAN "%.2lf" RESET "\n",
				scene->lights[i].ratio);
			printf("  Color:\t" CYAN "0x%x" RESET "\n",
				vec_to_int(scene->lights[i].material.albedo));
			i++;
		}
	}
}

void	print_scene(const t_scene *scene)
{
	printf(YELLOW "\n=== SCENE DUMP ===" RESET "\n");
	printf(CYAN "\n[General Info]" RESET "\n");
	printf("Nb spheres:\t" CYAN "%zu" RESET "\n", scene->nb_spheres);
	printf("Nb planes:\t" CYAN "%zu" RESET "\n", scene->nb_planes);
	printf("Nb cylinders:\t" CYAN "%zu" RESET "\n", scene->nb_cylinders);
	printf(CYAN "\n[Ambient Light]" RESET "\n");
	printf("Ratio:\t\t" CYAN "%.2lf" RESET "\n", scene->ambient_light.ratio);
	printf("Color:\t\t" CYAN "0x%x" RESET "\n",
		vec_to_int(scene->ambient_light.color));
	printf(CYAN "\n[Camera]" RESET "\n");
	printf("Origin:\t\t" GREEN "(%.2lf, %.2lf, %.2lf)" RESET "\n",
		scene->camera.origin.x, scene->camera.origin.y, scene->camera.origin.z);
	printf("Forward:\t" BLUE "(%.2lf, %.2lf, %.2lf)" RESET "\n",
		scene->camera.forward.x, scene->camera.forward.y,
		scene->camera.forward.z);
	printf("FOV:\t\t" CYAN "%d" RESET "\n", scene->camera.fov);
	print_lights(scene);
	print_spheres(scene);
	print_planes(scene);
	print_cylinders(scene);
	print_cones(scene);
	printf(YELLOW "\n=== END OF DUMP ===" RESET "\n\n");
}

#else

void	print_scene(const t_scene *scene)
{
	(void)scene;
}

#endif
