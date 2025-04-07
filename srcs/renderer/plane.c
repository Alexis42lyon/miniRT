#include "raytracer.h"
#include "libft/vector.h"

double	plane_hit(const t_plane plane, const t_ray ray)
{
	t_vec3	oc;
	double	denominator;
	double	res;

	denominator = ft_dot(plane.normal, ray.dir);
	oc = vec3_sub(plane.origin, ray.origin);
	res = ft_dot(oc, plane.normal) / denominator;
	if (res >= 0)
		return (res);
	return (-1);
}
