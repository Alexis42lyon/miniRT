#include "raytracer.h"

t_mat	default_mat(void)
{
	return ((t_mat){
		{1, 1, 1},
		1.0f,
		0.0f,
		-1.0f
	});
}

t_vec3	normal_color(t_hit hit)
{
	t_vec3	color;

	color = vec3_mult(vec3_add(hit.hit_normal, (t_vec3){1, 1, 1}), 0.5);
	return (color);
}

uint	convert_to_rgba(const t_vec3 color)
{
	unsigned short	r;
	unsigned short	g;
	unsigned short	b;
	unsigned short	a;

	r = (unsigned short)(color.x * 255.999f);
	g = (unsigned short)(color.y * 255.999f);
	b = (unsigned short)(color.z * 255.999f);
	a = (unsigned short)(255.999f);
	return ((a << 24) | (r << 16) | (g << 8) | b);
}
