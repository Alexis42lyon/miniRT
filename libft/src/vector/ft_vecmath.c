#include <math.h>
#include "libft/vector.h"

t_vec3	vec3_add(const t_vec3 v1, const t_vec3 v2)
{
	return ((t_vec3){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z});
}

t_vec3 vec3_divide(const t_vec3 v1, const double d)
{
	 return ((t_vec3){v1.x / d, v1.y / d, v1.z / d});
}

t_vec3 vec3_mult(const t_vec3 v1, const double d)
{
	 return ((t_vec3){v1.x * d, v1.y * d, v1.z * d});
}

t_vec3	vec3_sub(const t_vec3 v1, const t_vec3 v2)
{
	return ((t_vec3){v1.x - v2.x, v1.y - v2.y, v1.z - v2.z});
}

double	vec3_lenght(const t_vec3 vec)
{
	return (sqrt(vec3_lenght_square(vec)));
}

double	vec3_lenght_square(const t_vec3 vec)
{
	return ((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));
}

t_vec3	unit_vec3(const t_vec3 v)
{
	return (vec3_divide(v, vec3_lenght(v)));
}

double	ft_dot(const t_vec3 v1, const t_vec3 v2)
{
	 return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}

t_vec3	vec3_rand(uint seed)
{
	return ((t_vec3){PCG_Hash(seed * 2), PCG_Hash(seed * 8), PCG_Hash(seed)});
}

t_vec3	vec3_rand_range(uint range, uint seed)
{
	return ((t_vec3){
		PCG_Hash_range(range, seed),
		PCG_Hash_range(range, seed * 2),
		PCG_Hash_range(range, seed * 8)
	});
}
