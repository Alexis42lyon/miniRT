#include "libft/vector.h"
#include <math.h>


t_vec3	vec3_add(t_vec3 v1, t_vec3 v2)
{
	return ft_vec3new(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

int	vec3_magn(t_vec3 vec)
{
	return (sqrt((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z)));
}

int	ft_dot(t_vec3 v1, t_vec3 v2)
{
	 return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}
