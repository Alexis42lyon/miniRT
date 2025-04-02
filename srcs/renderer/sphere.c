#include "raytracer.h"

t_hit	sp_hit_result(const t_vec3 origin, const t_ray r, const double t, const size_t idx)
{
	t_hit	hit;

	hit.hit_point = vec3_add(r.origin, vec3_mult(r.dir, t));
	hit.hit_normal = vec3_normalize(vec3_sub(hit.hit_point, origin));
	hit.hit_distance = t;
	hit.obj_index = idx;
	return (hit);
}

double	sphere_hit(const t_sphere sphere, const t_ray ray)
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
		return (-1);
	return (((h - sqrt(t)) / a));
}

t_vec3	random_vec_hemisphere(const t_vec3 normal, const uint seed)
{
	t_vec3	vec;

	vec = vec3_rand_unit(seed);
	if (ft_dot(vec, normal) > 0)
	{
		return (vec);
	}
	return (vec3_mult(vec, -1.0));
}
