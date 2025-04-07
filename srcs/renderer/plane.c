#include "raytracer.h"
#include "libft/vector.h"

double	plane_hit(const t_plane plane, const t_ray ray)
{
	double	denominator;
	t_vec3	oc;
	double	res;

	denominator = ft_dot(plane.normal, ray.dir);
	if (fabs(denominator) < 1e-8)
		return (-1.0);
	oc = vec3_sub(plane.origin, ray.origin);
	res = ft_dot(oc, plane.normal) / denominator;
	if (res < 1e-6)
		return (-1.0);
	return (res);
}
