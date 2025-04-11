/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:34:21 by abidolet          #+#    #+#             */
/*   Updated: 2025/04/11 14:45:46 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <math.h>

void	ft_swap(double *a, double *b)
{
	double	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

static void	cy_solve(t_vec3 oc, t_ray_cylinder r, t_cylinder *cy, double t[2])
{
	double	a;
	double	b;
	double	c;
	double	d;
	double	q;

	a = ft_dot(vec3_cross(r.direction, cy->normal),
			vec3_cross(r.direction, cy->normal));
	b = 2 * ft_dot(vec3_cross(r.direction, cy->normal),
			vec3_cross(oc, cy->normal));
	c = ft_dot(vec3_cross(oc, cy->normal),
			vec3_cross(oc, cy->normal)) - cy->radius * cy->radius;
	d = b * b - 4 * a * c;
	if (d < 0)
	{
		t[0] = INFINITY;
		t[1] = INFINITY;
		return ;
	}
	if (b > 0)
		q = -0.5 * (b + sqrt(d));
	else
		q = -0.5 * (b - sqrt(d));
	t[0] = q / a;
	t[1] = c / q;
}

static bool	cy_cap(t_ray_cylinder r, double t, t_cylinder cy, bool top)
{
	t_vec3	p;
	t_vec3	c;
	double	y;
	double	d;

	p = vec3_add(r.origin, vec3_mult(r.direction, t));
	c = vec3_sub(p, cy.origin);
	y = ft_dot(c, cy.normal);
	if (top && y < cy.height - 1e-6)
		return (false);
	if (!top && y > 1e-6)
		return (false);
	d = ft_dot(c, c) - y * y;
	return (d <= cy.radius * cy.radius + 1e-6);
}

static int	get_res(t_ray_cylinder r, t_cylinder *cy, int res)
{
	double	denom;
	double	cap_t;

	denom = ft_dot(r.direction, cy->normal);
	if (fabs(denom) > 1e-6)
	{
		cap_t = ft_dot(vec3_sub(cy->origin, r.origin), cy->normal) / denom;
		if (cap_t > 1e-6 && (res < 0 || cap_t < res)
			&& cy_cap(r, cap_t, *cy, false))
			return (cap_t);
		cap_t = ft_dot(vec3_sub(vec3_add(cy->origin, vec3_mult(cy->normal,
							cy->height)), r.origin), cy->normal) / denom;
		if (cap_t > 1e-6 && (res < 0 || cap_t < res)
			&& cy_cap(r, cap_t, *cy, true))
			return (cap_t);
	}
	return (res);
}

double	cylinders_hit(void *p_cy, t_ray_cylinder r)
{
	double		t[2];
	double		res;
	double		y;
	t_cylinder	*cy;

	cy = (t_cylinder *)p_cy;
	res = -1;
	cy_solve(vec3_sub(r.origin, cy->origin), r, cy, t);
	if (t[0] > t[1])
		ft_swap(&t[0], &t[1]);
	if (t[0] > 1e-6)
	{
		y = ft_dot(vec3_sub(vec3_add(r.origin, vec3_mult(r.direction, t[0])),
					cy->origin), cy->normal);
		if (y >= 0 && y <= cy->height)
			res = t[0];
	}
	if (res < 0 && t[1] > 1e-6)
	{
		y = ft_dot(vec3_sub(vec3_add(r.origin,
						vec3_mult(r.direction, t[1])), cy->origin), cy->normal);
		if (y >= 0 && y <= cy->height)
			res = t[1];
	}
	return (get_res(r, cy, res));
}
