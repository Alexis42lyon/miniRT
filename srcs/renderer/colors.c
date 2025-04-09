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

	color = vec3_mult(vec3_add(hit.normal, (t_vec3){1, 1, 1}), 0.5);
	return (color);
}

t_uint	vec_to_int(const t_vec3 color)
{
	unsigned char r = (unsigned char)(color.x * 255.0f);
	unsigned char g = (unsigned char)(color.y * 255.0f);
	unsigned char b = (unsigned char)(color.z * 255.0f);
	unsigned char a = 255; // fully opaque

	return ((a << 24) | (r << 16) | (g << 8) | b);
}

t_vec3	int_to_vec(t_uint color)
{
	t_vec3 vec;

	unsigned char r = (color >> 16) & 0xFF;
	unsigned char g = (color >> 8) & 0xFF;
	unsigned char b = color & 0xFF;

	vec.x = r / 255.0f;
	vec.y = g / 255.0f;
	vec.z = b / 255.0f;

	return vec;
}

