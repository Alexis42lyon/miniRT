#include "miniRT.h"
#include "raytracer.h"

t_vec3	sp_normal_color(t_sphere *sp, t_ray r, double t)
{
	t_vec3	hit_point;
	t_vec3	normal;
	t_vec3	color;

	hit_point = vec3_add(r.origin, vec3_mult(r.dir, t));
	normal = unit_vec3(vec3_sub(hit_point, sp->origin));
	color = vec3_mult(vec3_add(normal, (t_vec3){1, 1, 1}), 0.5);
	return (color);
}

int convert_to_rgba(const t_vec3 color)
{
	unsigned short r, g, b, a;

	r = (unsigned short)(color.x * 255.999f);
	g = (unsigned short)(color.y * 255.999f);
	b = (unsigned short)(color.z * 255.999f);
	a = (unsigned short)(255.999f);

	return ((a << 24) | (r << 16) | (g << 8) | b);
}
