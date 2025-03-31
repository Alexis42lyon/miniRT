#include "raytracer.h"

t_hit	sp_hit_result(const t_sphere sp, const t_ray r, const double t)
{
	t_hit	hit;

	hit.hit_point = vec3_add(r.origin, vec3_mult(r.dir, t));
	hit.hit_normal = unit_vec3(vec3_sub(hit.hit_point, sp.origin));
	hit.hit_distance = t;
	return (hit);
}

t_hit	sphere_hit(const t_sphere sphere, const t_ray ray)
{
	t_vec3	oc;
	double	a;
	double	h;
	double	c;
	double	t;

	oc = vec3_sub(sphere.origin, ray.origin);
	a = vec3_lenght_square(ray.dir);
	h = ft_dot(ray.dir, oc);
	c = vec3_lenght_square(oc) - sphere.radius * sphere.radius;
	t = h * h - a * c;
	if (t < 0)
		return ((t_hit){{0, 0, 0}, {0, 0, 0}, -1, 0});
	return (sp_hit_result(sphere, ray, ((h - sqrt(t)) / a)));
}
