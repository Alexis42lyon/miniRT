#include "libft/vector.h"
#include "miniRT.h"
#include "raytracer.h"
#include <limits.h>

t_vec3	ray_to_vec(t_ray r)
{
	return (vec3_add(r.origin, vec3_mult(r.dir, r.lenght)));
}

t_ray	get_ray(int i, int j, t_viewport vp)
{
	t_ray	ray;
	t_vec3	px_center;

	px_center = vec3_add(vp.px_00, vec3_add(
				vec3_mult(vp.px_delta_u, i),
				vec3_mult(vp.px_delta_v, j))
			);
	ray.origin = vp.cam->origin;
	ray.dir = vec3_sub(px_center, ray.origin);
	return (ray);
}

t_hit	trace_ray(t_ray ray, t_scene *scene)
{
	t_hit	hit;
	double	dist;
	double	min_dist;
	size_t	i;
	enum e_object_type	type;

	min_dist = INT_MAX;
	hit.obj_index = -1;
	i = 0;
	while (i < scene->nb_spheres)
	{
		dist = sphere_hit(scene->spheres[i], ray);
		if (dist > 0 && dist < min_dist)
		{
			min_dist = dist;
			hit.obj_index = i;
			type = SPHERE;
		}
		i++;
	}
	i = 0;
	while (i < scene->nb_planes)
	{
		dist = plane_hit(scene->planes[i], ray);
		if (dist > 0 && dist < min_dist)
		{
			min_dist = dist;
			hit.obj_index = i;
			type = PLANE;
		}
		i++;
	}
	if (hit.obj_index != (size_t)-1)
	{
		if (type == SPHERE)
			hit = hit_result(scene->spheres[hit.obj_index].origin, ray, min_dist, hit.obj_index);
		else if (type == PLANE)
		{
			hit = hit_result(scene->planes[hit.obj_index].origin, ray, min_dist, hit.obj_index);
			hit.hit_normal = scene->planes[hit.obj_index].normal;
		}
		hit.type = type;
		return (hit);
	}
	return (hit_fail());
}

t_hit	hit_fail(void)
{
	return ((t_hit){
		{0, 0, 0},
		{0, 0, 0},
		-1,
		-1,
		NONE,
	});
}
