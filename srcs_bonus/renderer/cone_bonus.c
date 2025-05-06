/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:38:21 by abidolet          #+#    #+#             */
/*   Updated: 2025/05/06 14:03:30 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h_bonus.h"
#include "raytracer_bonus.h"
#include "libft/vector.h"

static double	find_closest_intersection(double intersections[3])
{
	double	closest;
	int		i;

	closest = HUGE_VAL;
	i = -1;
	while (++i < 3)
		if (intersections[i] > 1e-6 && intersections[i] < closest)
			closest = intersections[i];
	if (closest != HUGE_VAL)
		return (closest);
	return (-1.0);
}

static double	check_cone_cap(t_ray ray, t_cylinder *co)
{
	t_vec3	normalized_dir;
	t_vec3	cap_center;
	double	denom;
	double	t;

	normalized_dir = vec3_normalize(co->normal);
	cap_center = vec3_add(co->origin, vec3_mult(normalized_dir, co->height));
	denom = ft_dot(ray.dir, normalized_dir);
	if (fabs(denom) < 1e-6)
		return (HUGE_VAL);
	t = ft_dot(vec3_sub(cap_center, ray.origin), normalized_dir) / denom;
	if (t < 1e-6)
		return (HUGE_VAL);
	if (vec3_length(vec3_sub(vec3_add(ray.origin,
					vec3_mult(ray.dir, t)), cap_center)) > co->radius)
		return (HUGE_VAL);
	return (t);
}

static double	process_inter(double roots[2], t_cylinder *co, t_ray ray)
{
	int		i;
	double	h;
	double	intersections[3];

	i = -1;
	while (++i < 2)
	{
		if (roots[i] > 1e-6)
		{
			h = ft_dot(vec3_sub(vec3_add(ray.origin,
							vec3_mult(ray.dir, roots[i])), co->origin),
					vec3_normalize(co->normal));
			if (h >= 0.0 && h <= co->height)
				intersections[i] = roots[i];
			else
				intersections[i] = HUGE_VAL;
		}
		else
			intersections[i] = HUGE_VAL;
	}
	intersections[2] = check_cone_cap(ray, co);
	return (find_closest_intersection(intersections));
}

static void	solve_cone_eq(t_cylinder *co, t_ray ray, double params[3])
{
	t_vec3	normalized_dir;
	double	cos_sq;
	t_vec3	delta_p;
	double	dv;
	double	dp;

	normalized_dir = vec3_normalize(co->normal);
	cos_sq = pow(cos(atan(co->radius / co->height)), 2);
	delta_p = vec3_sub(ray.origin, co->origin);
	dv = ft_dot(ray.dir, normalized_dir);
	dp = ft_dot(delta_p, normalized_dir);
	params[0] = dv * dv - cos_sq;
	params[1] = 2 * (dv * dp - ft_dot(ray.dir, delta_p) * cos_sq);
	params[2] = dp * dp - ft_dot(delta_p, delta_p) * cos_sq;
}

double	cone_hit(void *p, t_ray ray)
{
	t_cylinder	*co;
	double		params[3];
	double		roots[2];
	double		discriminant;
	double		tmp;

	co = (t_cylinder *)p;
	solve_cone_eq(co, ray, params);
	discriminant = params[1] * params[1] - 4 * params[0] * params[2];
	if (discriminant < 0.0)
		return (-1.0);
	tmp = sqrt(discriminant);
	roots[0] = (-params[1] - tmp) / (2 * params[0]);
	roots[1] = (-params[1] + tmp) / (2 * params[0]);
	return (process_inter(roots, co, ray));
}
