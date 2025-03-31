/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 23:42:35 by abidolet          #+#    #+#             */
/*   Updated: 2025/03/30 18:42:39 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

#if SHOW_SRUCT

# include <stdio.h>

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
			printf("  Origin: " GREEN "(%.2lf, %.2lf, %.2lf)" RESET "\n",
				scene->spheres[i].origin.x, scene->spheres[i].origin.y,
				scene->spheres[i].origin.z);
			printf("  Diameter: " CYAN "%.2lf" RESET "\n",
				scene->spheres[i].radius);
			printf("  Color: " CYAN "0x%06lx" RESET "\n",
				scene->spheres[i].color);
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
			printf(YELLOW "- Plane %zu:" RESET "\n", i + 1);
			printf("  Origin: " GREEN "(%.2lf, %.2lf, %.2lf)" RESET "\n",
				scene->planes[i].origin.x, scene->planes[i].origin.y,
				scene->planes[i].origin.z);
			printf("  Normal: " BLUE "(%.2lf, %.2lf, %.2lf)" RESET "\n",
				scene->planes[i].normal.x, scene->planes[i].normal.y,
				scene->planes[i].normal.z);
			printf("  Color: " CYAN "0x%06lx" RESET "\n",
				scene->planes[i].color);
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
			printf("  Origin: " GREEN "(%.2lf, %.2lf, %.2lf)" RESET "\n",
				scene->cylinders[i].origin.x, scene->cylinders[i].origin.y,
				scene->cylinders[i].origin.z);
			printf("  Normal: " BLUE "(%.2lf, %.2lf, %.2lf)" RESET "\n",
				scene->cylinders[i].normal.x, scene->cylinders[i].normal.y,
				scene->cylinders[i].normal.z);
			printf("  Diameter: " CYAN "%.2lf" RESET "\n",
				scene->cylinders[i].radius);
			printf("  Height: " CYAN "%.2lf" RESET "\n",
				scene->cylinders[i].height);
			printf("  Color: " CYAN "0x%06lx" RESET "\n",
				scene->cylinders[i].color);
			i++;
		}
	}
}

static void	print_ambient_light(const t_ambient_light *ambient)
{
	printf(CYAN "\n[Ambient Light]" RESET "\n");
	printf("Set: ");
	if (ambient->is_set)
		printf(GREEN "Yes" RESET "\n");
	else
		printf(CYAN "No" RESET "\n");
	if (ambient->is_set)
	{
		printf("Ratio: " CYAN "%.2lf" RESET "\n", ambient->ratio);
		printf("Color: " CYAN "0x%06lx" RESET "\n", ambient->color);
	}
}

static void	print_camera(const t_camera *camera)
{
	printf(CYAN "\n[Camera]" RESET "\n");
	printf("Set: ");
	if (camera->is_set)
		printf(GREEN "Yes" RESET "\n");
	else
		printf(CYAN "No" RESET "\n");
	if (camera->is_set)
	{
		printf("Origin: " GREEN "(%.2lf, %.2lf, %.2lf)" RESET "\n",
			camera->origin.x, camera->origin.y, camera->origin.z);
		printf("Direction: " BLUE "(%.2lf, %.2lf, %.2lf)" RESET "\n",
			camera->direction.x, camera->direction.y, camera->direction.z);
		printf("FOV: " CYAN "%d" RESET "\n", camera->fov);
	}
}

static void	print_light(const t_light_source *light)
{
	printf(CYAN "\n[Light]" RESET "\n");
	printf("Set: ");
	if (light->is_set)
		printf(GREEN "Yes" RESET "\n");
	else
		printf(CYAN "No" RESET "\n");
	if (light->is_set)
	{
		printf("Origin: " GREEN "(%.2lf, %.2lf, %.2lf)" RESET "\n",
			light->origin.x, light->origin.y, light->origin.z);
		printf("Ratio: " CYAN "%.2lf" RESET "\n", light->ratio);
		printf("Color: " CYAN "0x%06lx" RESET "\n", light->color);
	}
}

void	print_scene(const t_scene *scene)
{
	printf(YELLOW "\n=== SCENE DUMP ===" RESET "\n");
	printf(CYAN "\n[General Info]" RESET "\n");
	printf("Spheres: " CYAN "%zu" RESET "\n", scene->nb_spheres);
	printf("Planes: " CYAN "%zu" RESET "\n", scene->nb_planes);
	printf("Cylinders: " CYAN "%zu" RESET "\n", scene->nb_cylinders);
	print_ambient_light(&scene->ambient_light);
	print_camera(&scene->camera);
	print_light(&scene->light);
	print_spheres(scene);
	print_planes(scene);
	print_cylinders(scene);
	printf(YELLOW "\n=== END OF DUMP ===" RESET "\n\n");
}

#else

void	print_scene(const t_scene *scene)
{
	(void)scene;
}

#endif
