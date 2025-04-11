/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:34:21 by abidolet          #+#    #+#             */
/*   Updated: 2025/04/11 15:32:25 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "libft/vector.h"
#include <math.h>

static void	swap_double(double *a, double *b)
{
	double	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static void	solve_cylinder_eq(double abc[3], double roots[2])
{
	double	discriminant;
	double	q;

	discriminant = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (discriminant < 0)
	{
		roots[0] = INFINITY;
		roots[1] = INFINITY;
		return ;
	}
	if (abc[1] > 0)
		q = -0.5 * (abc[1] + sqrt(discriminant));
	else
		q = -0.5 * (abc[1] - sqrt(discriminant));
	roots[0] = q / abc[0];
	roots[1] = abc[2] / q;
}

static double	check_caps(t_ray_cylinder ray, t_cylinder *cy, bool top)
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
	if (vec3_lenght(vec3_sub(hit, cap_center)) > cy->radius)
		return (INFINITY);
	return (t);
}

static double	check_body(t_cylinder *cy, t_ray_cylinder ray, double t)
{
	t_vec3	hit;
	t_vec3	vec;
	double	proj;

	hit = vec3_add(ray.origin, vec3_mult(ray.dir, t));
	vec = vec3_sub(hit, cy->origin);
	proj = ft_dot(vec, cy->normal);
	if (proj < -1e-6 || proj > cy->height + 1e-6)
		return (INFINITY);
	return (t);
}

double	cylinders_hit(void *obj, t_ray_cylinder ray)
{
	double		abc[3];
	double		t[2];
	double		res[3];
	t_cylinder	*cy;

	cy = (t_cylinder *)obj;
	abc[0] = ft_dot(ray.dir, ray.dir) - pow(ft_dot(ray.dir, cy->normal), 2);
	abc[1] = 2 * (ft_dot(ray.dir, vec3_sub(ray.origin, cy->origin))
			- ft_dot(ray.dir, cy->normal)
			* ft_dot(vec3_sub(ray.origin, cy->origin), cy->normal));
	abc[2] = ft_dot(vec3_sub(ray.origin, cy->origin),
			vec3_sub(ray.origin, cy->origin))
		- pow(ft_dot(vec3_sub(ray.origin, cy->origin), cy->normal), 2)
		- cy->radius * cy->radius;
	solve_cylinder_eq(abc, t);
	if (t[0] > t[1])
		swap_double(&t[0], &t[1]);
	res[0] = fmin(check_body(cy, ray, t[0]), check_body(cy, ray, t[1]));
	res[1] = check_caps(ray, cy, false);
	res[2] = check_caps(ray, cy, true);
	res[0] = fmin(res[0], fmin(res[1], res[2]));
	if (res[0] > 1e-6)
		return (res[0]);
	return (-1);
}
