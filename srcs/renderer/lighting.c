#include "raytracer.h"
#include <stdio.h>

int	in_light(t_scene *scene, t_hit hit, t_vec3 light_dir)
{
	t_hit	light_hit;
	t_ray		ray;

	ray.origin = hit.point;
	ray.dir = vec3_mult(light_dir, -1);

	light_hit = trace_ray(ray, scene);	
	return (light_hit.distance == -1);
}


t_vec3	phong_shading(t_scene *scene, t_hit hit, t_mat mat, t_ray ray)
{
	t_vec3	diffuse = vec3_zero();
	t_vec3	specular = vec3_zero();
	t_vec3	ambient = vec3_zero();
	short flags;

	t_vec3	light_dir;

	float light_range = 5;

	light_dir = vec3_sub(hit.point, scene->light.origin);
	float	attenuation = light_range / vec3_lenght(light_dir);
	if (attenuation < 0)
		attenuation = 0;
	light_dir = vec3_normalize(light_dir);

	ambient = vec3_multv(mat.albedo, scene->ambient_light.color);
	ambient = vec3_mult(ambient, scene->ambient_light.ratio);

	if (in_light(scene, hit, light_dir))
	{
		// Diffuse = Kd * DOT(N, L) * Od * Ld
		// Kd = reflection coef
		// N = normal
		// L = light
		// Od = mat albeado
		// Ld = light color
		diffuse = vec3_mult(mat.albedo, mat.roughtness * ft_clamp(ft_dot(hit.normal, vec3_mult(light_dir, -1)), 0, 1));
		diffuse = vec3_multv(diffuse, scene->light.material.albedo);
		diffuse = vec3_mult(diffuse, scene->light.ratio);
	
		float specular_coef = 0.6f;
		t_vec3	view_vec = vec3_normalize(vec3_sub(ray.origin, hit.point));
	
		t_vec3	reflect_vec = vec3_reflect(light_dir, hit.normal);
		float d = ft_dot(view_vec, reflect_vec);
		if (d < 0)
			d = 0;
		double	spec = pow(d, 32);
		specular = vec3_mult(scene->light.material.albedo, specular_coef * spec * scene->light.ratio);
		specular = vec3_multv(specular, mat.albedo);
		specular = vec3_mult(specular, attenuation);

	}



	diffuse = vec3_mult(diffuse, attenuation);
	
	flags = SPECULAR | AMBIENT | DIFFUSE;

	t_vec3	merged_pass = vec3_zero();
	if (flags & AMBIENT)
		merged_pass = vec3_add(merged_pass, ambient);
	if (flags & DIFFUSE)
		merged_pass = vec3_add(merged_pass, diffuse);
	if (flags & SPECULAR)
		merged_pass = vec3_add(merged_pass, specular);
	
	return merged_pass;
}
