#include "miniRT.h"
#include <math.h>

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
	double	length;
}	t_ray;

t_vec3	vec3_scale(t_vec3 v, double scalar)
{
	return ((t_vec3){v.x * scalar, v.y * scalar, v.z * scalar});
}

void	ft_swap(double *a, double *b)
{
	double	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

t_vec3	cylinder_normal(t_cylinder cy, t_vec3 hit_point)
{
	t_vec3	cp;
	double	projection;
	t_vec3	top_center;

	cp = vec3_sub(hit_point, cy.origin);
	projection = ft_dot(cp, cy.normal);
	if (fabs(projection) < 1e-6)
		return (vec3_scale(cy.normal, -1.0));
	top_center = vec3_add(cy.origin, vec3_scale(cy.normal, cy.height));
	if (fabs(ft_dot(vec3_sub(hit_point, top_center), cy.normal)) < 1e-6)
		return (cy.normal);
	return (vec3_normalize(vec3_sub(cp, vec3_scale(cy.normal, projection))));
}

static void	cy_solve(double a, double b, double c, double t[2])
{
	double	d;
	double	q;

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
	if (t[0] > t[1])
		ft_swap(&t[0], &t[1]);
}

static bool	cy_cap(t_ray r, double t, t_cylinder cy, bool top)
{
	t_vec3	p;
	t_vec3	c;
	double	y;
	double	d;

	p = vec3_add(r.origin, vec3_scale(r.direction, t));
	c = vec3_sub(p, cy.origin);
	y = ft_dot(c, cy.normal);
	if (top && y < cy.height - 1e-6)
		return (false);
	if (!top && y > 1e-6)
		return (false);
	d = ft_dot(c, c) - y * y;
	return (d <= cy.radius * cy.radius + 1e-6);
}

double	cylinders_hit(void *p_cy, t_ray r)
{
	t_vec3	oc;
	double	abc[3];
	double	t[2];
	double	closest;
	double	y;
	double	denom;
	double	cap_t;
	t_vec3	top_center;
	t_cylinder *cy;

	cy = (t_cylinder *)p_cy;
	oc = vec3_sub(r.origin, cy->origin);
	closest = -1;
	abc[0] = ft_dot(vec3_cross(r.direction, cy->normal),
			vec3_cross(r.direction, cy->normal));
	abc[1] = 2 * ft_dot(vec3_cross(r.direction, cy->normal),
			vec3_cross(oc, cy->normal));
	abc[2] = ft_dot(vec3_cross(oc, cy->normal),
			vec3_cross(oc, cy->normal)) - cy->radius * cy->radius;
	cy_solve(abc[0], abc[1], abc[2], t);
	if (t[0] > 1e-6)
	{
		y = ft_dot(vec3_sub(vec3_add(r.origin, vec3_scale(r.direction, t[0])),
					cy->origin), cy->normal);
		if (y >= 0 && y <= cy->height)
			closest = t[0];
	}
	if (closest < 0 && t[1] > 1e-6)
	{
		y = ft_dot(vec3_sub(vec3_add(r.origin,
						vec3_scale(r.direction, t[1])), cy->origin), cy->normal);
		if (y >= 0 && y <= cy->height)
			closest = t[1];
	}
	denom = ft_dot(r.direction, cy->normal);
	if (fabs(denom) > 1e-6)
	{
		cap_t = ft_dot(vec3_sub(cy->origin, r.origin), cy->normal) / denom;
		if (cap_t > 1e-6 && (closest < 0 || cap_t < closest)
			&& cy_cap(r, cap_t, *cy, false))
			closest = cap_t;
		top_center = vec3_add(cy->origin, vec3_scale(cy->normal, cy->height));
		cap_t = ft_dot(vec3_sub(top_center, r.origin), cy->normal) / denom;
		if (cap_t > 1e-6 && (closest < 0 || cap_t < closest)
			&& cy_cap(r, cap_t, *cy, true))
			closest = cap_t;
	}
	return (closest);
}
