/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 10:22:49 by abidolet          #+#    #+#             */
/*   Updated: 2025/04/11 12:06:37 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#if SHOW_SRUCT

# include <stdio.h>
# include "raytracer.h"

static void	print_spheres(const t_scene *scene)
{
	size_t	i;

	printf(CYAN "\n[Spheres: %zu]" RESET "\n", scene->nb_spheres);
	if (scene->spheres)
	{
		i = 0;
		while (i < scene->nb_spheres)
		{
			printf(YELLOW "- Sphere %zu:" RESET "\n", i + 1);
			printf("  Origin:\t" GREEN "(%.2lf, %.2lf, %.2lf)" RESET "\n",
				scene->spheres[i].origin.x, scene->spheres[i].origin.y,
				scene->spheres[i].origin.z);
			printf("  Diameter:\t" CYAN "%.2lf" RESET "\n",
				scene->spheres[i].radius);
			printf("  Color:\t" CYAN "0x%x" RESET "\n",
				vec_to_int(scene->spheres[i].material.albedo));
			i++;
		}
	}
}

static void	print_planes(const t_scene *scene)
{
	size_t	i;

	printf(CYAN "\n[Planes: %zu]" RESET "\n", scene->nb_planes);
	if (scene->planes)
	{
		i = 0;
		while (i < scene->nb_planes)
		{
			printf(YELLOW "- Plane\t%zu:" RESET "\n", i + 1);
			printf("  Origin:\t" GREEN "(%.2lf, %.2lf, %.2lf)" RESET "\n",
				scene->planes[i].origin.x, scene->planes[i].origin.y,
				scene->planes[i].origin.z);
			printf("  Normal:\t" BLUE "(%.2lf, %.2lf, %.2lf)" RESET "\n",
				scene->planes[i].normal.x, scene->planes[i].normal.y,
				scene->planes[i].normal.z);
			printf("  Color:\t" CYAN "0x%x" RESET "\n",
				vec_to_int(scene->planes[i].material.albedo));
			i++;
		}
	}
}

static void	print_cylinders(const t_scene *scene)
{
	size_t	i;

	printf(CYAN "\n[Cylinders: %zu]" RESET "\n", scene->nb_cylinders);
	if (scene->cylinders)
	{
		i = 0;
		while (i < scene->nb_cylinders)
		{
			printf(YELLOW "- Cylinder %zu:" RESET "\n", i + 1);
			printf("  Origin:\t" GREEN "(%.2lf, %.2lf, %.2lf)" RESET "\n",
				scene->cylinders[i].origin.x, scene->cylinders[i].origin.y,
				scene->cylinders[i].origin.z);
			printf("  Normal:\t" BLUE "(%.2lf, %.2lf, %.2lf)" RESET "\n",
				scene->cylinders[i].normal.x, scene->cylinders[i].normal.y,
				scene->cylinders[i].normal.z);
			printf("  Diameter:\t" CYAN "%.2lf" RESET "\n",
				scene->cylinders[i].radius);
			printf("  Height:\t" CYAN "%.2lf" RESET "\n",
				scene->cylinders[i].height);
			printf("  Color:\t" CYAN "0x%x" RESET "\n",
				vec_to_int(scene->cylinders[i].material.albedo));
			i++;
		}
	}
	printf(YELLOW "\n=== END OF DUMP ===" RESET "\n\n");
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
	printf(CYAN "\n[Light]" RESET "\n");
	printf("Origin:\t\t" GREEN "(%.2lf, %.2lf, %.2lf)" RESET "\n",
		scene->light.origin.x, scene->light.origin.y, scene->light.origin.z);
	printf("Ratio:\t\t" CYAN "%.2lf" RESET "\n", scene->light.ratio);
	printf("Color:\t\t" CYAN "0x%x" RESET "\n",
		vec_to_int(scene->light.material.albedo));
	print_spheres(scene);
	print_planes(scene);
	print_cylinders(scene);
}

#else

void	print_scene(const t_scene *scene)
{
	(void)scene;
}

#endif
