/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:14:06 by mjuncker          #+#    #+#             */
/*   Updated: 2025/04/29 12:00:43 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/vector.h"
#include "raytracer.h"
#include <stdio.h>

t_hit	hit_result(const t_vec3 origin, const t_ray r, const double t,
	const size_t idx)
{
	t_hit	hit;

	hit.point = vec3_add(r.origin, vec3_mult(r.dir, t));
	hit.normal = vec3_normalize(vec3_sub(hit.point, origin));
	hit.distance = t;
	hit.obj_index = idx;
	return (hit);
}

double	sphere_res(double a, double b, double disc)
{
	double	t1;
	double	t2;
	double	tmp;

	if (disc < 0)
		return (-1);
	tmp = sqrt(disc);
	t1 = (-b - tmp) / (2 * a);
	t2 = (-b + tmp) / (2 * a);
	if (t1 > 0)
		return (t1);
	return (t2);
}

double	sphere_hit(void *sphere, const t_ray ray)
{
	t_vec3	oc;
	double	a;
	double	b;
	double	c;
	double	disc;

	oc = vec3_sub(((t_sphere *)sphere)->origin, ray.origin);
	a = ft_dot(ray.dir, ray.dir);
	b = -2.0 * ft_dot(ray.dir, oc);
	c = ft_dot(oc, oc) - ((t_sphere *)sphere)->radius
		* ((t_sphere *)sphere)->radius;
	disc = b * b - 4 * a * c;
	return (sphere_res(a, b, disc));
}
