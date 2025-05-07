/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:34:21 by abidolet          #+#    #+#             */
/*   Updated: 2025/05/07 09:09:17 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer_bonus.h"

static double	check_caps(t_ray ray, t_cylinder *cy, bool top)
{
	t_vec3	cap_center;
	double	denom;
	double	t;
	t_vec3	hit;

	cap_center = vec3_add(cy->origin, vec3_mult(cy->normal, cy->height * top));
	denom = ft_dot(ray.dir, cy->normal);
	if (fabs(denom) < 1e-6)
		return (INFINITY);
	t = ft_dot(vec3_sub(cap_center, ray.origin), cy->normal) / denom;
	if (t < 1e-6)
		return (INFINITY);
	hit = vec3_add(ray.origin, vec3_mult(ray.dir, t));
	if (vec3_length(vec3_sub(hit, cap_center)) > cy->radius)
		return (INFINITY);
	return (t);
}

static double	get_closest(double intersections[3], t_ray ray,
	t_cylinder *cy, double proj)
{
	t_vec3	hit;
	t_vec3	vec;
	int		i;
	double	closest;

	hit = vec3_add(ray.origin, vec3_mult(ray.dir, intersections[0]));
	vec = vec3_sub(hit, cy->origin);
	proj = ft_dot(vec, cy->normal);
	if (proj < -1e-6 || proj > cy->height + 1e-6)
		intersections[0] = INFINITY;
	intersections[1] = check_caps(ray, cy, 0);
	intersections[2] = check_caps(ray, cy, 1);
	closest = HUGE_VAL;
	i = -1;
	while (++i < 3)
		if (intersections[i] > 1e-6 && intersections[i] < closest)
			closest = intersections[i];
	if (closest != HUGE_VAL)
		return (closest);
	return (-1);
}

static double	fill_intersection(double intersections[3], t_cylinder *cy,
	t_ray ray, double roots[2])
{
	double	proj;
	t_vec3	origin_vec;

	origin_vec = vec3_sub(ray.origin, cy->origin);
	proj = ft_dot(origin_vec, cy->normal);
	if (proj >= 0 && proj <= cy->height && ft_dot(origin_vec,
			origin_vec) - proj * proj <= cy->radius * cy->radius)
	{
		if (roots[1] > 1e-6)
			intersections[0] = roots[1];
		else
			intersections[0] = HUGE_VAL;
	}
	else
	{
		if (roots[0] > 1e-6)
			intersections[0] = roots[0];
		else if (roots[1] > 1e-6)
			intersections[0] = roots[1];
		else
			intersections[0] = HUGE_VAL;
	}
	return (proj);
}

static void	solve_cylinder_eq(double abc[3], double roots[2])
{
	double	discriminant;
	double	q;
	double	tmp;

	discriminant = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (discriminant < 0)
	{
		roots[0] = INFINITY;
		roots[1] = INFINITY;
		return ;
	}
	tmp = sqrt(discriminant);
	if (abc[1] > 0)
		q = -0.5 * (abc[1] + tmp);
	else
		q = -0.5 * (abc[1] - tmp);
	roots[0] = q / abc[0];
	roots[1] = abc[2] / q;
}

double	cylinders_hit(void *p, t_ray ray)
{
	t_cylinder	*cy;
	double		params[3];
	double		roots[2];
	double		tmp;
	double		intersections[3];

	cy = (t_cylinder *)p;
	params[0] = ft_dot(ray.dir, ray.dir) - pow(ft_dot(ray.dir, cy->normal), 2);
	params[1] = 2 * (ft_dot(ray.dir, vec3_sub(ray.origin, cy->origin))
			- ft_dot(ray.dir, cy->normal)
			* ft_dot(vec3_sub(ray.origin, cy->origin), cy->normal));
	params[2] = ft_dot(vec3_sub(ray.origin, cy->origin),
			vec3_sub(ray.origin, cy->origin))
		- pow(ft_dot(vec3_sub(ray.origin, cy->origin), cy->normal), 2)
		- cy->radius * cy->radius;
	solve_cylinder_eq(params, roots);
	if (roots[0] > roots[1])
	{
		tmp = roots[0];
		roots[0] = roots[1];
		roots[1] = tmp;
	}
	return (get_closest(intersections, ray, cy,
			fill_intersection(intersections, cy, ray, roots)));
}
