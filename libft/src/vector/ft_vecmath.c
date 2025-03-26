#include "libft/vector.h"
#include <math.h>


t_vec3	vec3_add(const t_vec3 v1, const t_vec3 v2)
{
	return ft_vec3new(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

t_vec3 vec3_divide(const t_vec3 v1, const double d)
{
	 return (ft_vec3new(v1.x / d, v1.y / d, v1.z / d));
}

t_vec3	vec3_sub(const t_vec3 v1, const t_vec3 v2)
{
	return ft_vec3new(v1.x - v2.x, v1.y + v2.y, v1.z + v2.z);
}

double	vec3_magn(const t_vec3 vec)
{
	return (sqrt((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z)));
}

double	ft_dot(const t_vec3 v1, const t_vec3 v2)
{
	 return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}
