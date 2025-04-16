/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_struct_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 10:47:22 by abidolet          #+#    #+#             */
/*   Updated: 2025/04/16 10:52:35 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdio.h>

void	print_spheres(const t_scene *scene)
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

void	print_planes(const t_scene *scene)
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

void	print_cylinders(const t_scene *scene)
{
	size_t	i;

	printf(CYAN "\n[Cylinders: %zu]" RESET "\n", scene->nb_cylinders);
	if (scene->cylinders)
	{
		i = 0;
		while (i < scene->nb_cylinders)
		{
			printf(YELLOW "- Cylinder\t%zu:" RESET "\n", i + 1);
			printf("Origin:\t\t" GREEN "(%.2lf, %.2lf, %.2lf)" RESET "\n",
				scene->cylinders[i].origin.x, scene->cylinders[i].origin.y,
				scene->cylinders[i].origin.z);
			printf("Normal:\t\t" GREEN "(%.2lf, %.2lf, %.2lf)" RESET "\n",
				scene->cylinders[i].normal.x, scene->cylinders[i].normal.y,
				scene->cylinders[i].normal.z);
			printf("Radius:\t\t" CYAN "%.2lf" RESET "\n",
				scene->cylinders[i].radius);
			printf("Height:\t\t" CYAN "%.2lf" RESET "\n",
				scene->cylinders[i].height);
			printf("Color:\t\t" CYAN "0x%x" RESET "\n",
				vec_to_int(scene->cylinders[i].material.albedo));
			i++;
		}
	}
}

void	print_cones(const t_scene *scene)
{
	size_t	i;

	printf(CYAN "\n[Cones: %zu]" RESET "\n", scene->nb_cones);
	if (scene->cones)
	{
		i = 0;
		while (i < scene->nb_cones)
		{
			printf(YELLOW "- Cone\t%zu:" RESET "\n", i + 1);
			printf("Origin:\t\t" GREEN "(%.2lf, %.2lf, %.2lf)" RESET "\n",
				scene->cones[i].origin.x, scene->cones[i].origin.y,
				scene->cones[i].origin.z);
			printf("Normal:\t\t" GREEN "(%.2lf, %.2lf, %.2lf)" RESET "\n",
				scene->cones[i].normal.x, scene->cones[i].normal.y,
				scene->cones[i].normal.z);
			printf("Radius:\t\t" CYAN "%.2lf" RESET "\n",
				scene->cones[i].radius);
			printf("Height:\t\t" CYAN "%.2lf" RESET "\n",
				scene->cones[i].height);
			printf("Color:\t\t" CYAN "0x%x" RESET "\n",
				vec_to_int(scene->cones[i].material.albedo));
			i++;
		}
	}
}
