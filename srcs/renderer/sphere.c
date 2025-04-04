#include "libft/vector.h"
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
	double	b;
	double	c;
	double	disc;
	double	t1;
	double	t2;

	oc = vec3_sub(sphere.origin, ray.origin);
	a = ft_dot(ray.dir,ray.dir);
	b = -2.0 * ft_dot(ray.dir, oc);
	c = ft_dot(oc, oc) - sphere.radius * sphere.radius;
	disc = b*b - 4*a*c;
	if (disc < 0)
		return (-1);
	t1 = (-b - sqrt(disc)) / (2*a);
	t2 = (-b + sqrt(disc)) / (2*a);
	if (t1 < t2)
		return (t1);
	return (t2);
}
