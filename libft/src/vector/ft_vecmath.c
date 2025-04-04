#include <math.h>
#include "libft/vector.h"

inline t_vec3	vec3_add(const t_vec3 v1, const t_vec3 v2)
{
	return ((t_vec3){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z});
}

inline t_vec3 vec3_divide(const t_vec3 v1, const double d)
{
	 return ((t_vec3){v1.x / d, v1.y / d, v1.z / d});
}

inline t_vec3 vec3_mult(const t_vec3 v1, const double d)
{
	 return ((t_vec3){v1.x * d, v1.y * d, v1.z * d});
}

inline t_vec3	vec3_sub(const t_vec3 v1, const t_vec3 v2)
{
	return ((t_vec3){v1.x - v2.x, v1.y - v2.y, v1.z - v2.z});
}

inline double	vec3_lenght(const t_vec3 vec)
{
	return (sqrt(vec3_lenght_square(vec)));
}

inline double	vec3_lenght_square(const t_vec3 vec)
{
	return ((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));
}

inline t_vec3	vec3_normalize(const t_vec3 v)
{
	return (vec3_divide(v, vec3_lenght(v)));
}

inline float	ft_dot(const t_vec3 v1, const t_vec3 v2)
{
	 return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}

inline t_vec3	vec3_rand(uint seed)
{
	return ((t_vec3){pcg_hash(seed * 2), pcg_hash(seed * 8), pcg_hash(seed)});
}

inline t_vec3 in_unit_sphere(uint seed)
{
	return vec3_normalize((t_vec3){
		random_float(seed) * 2.0f - 1.0f, 
		random_float(seed) * 2.0f - 1.0f, 
		random_float(seed) * 2.0f - 1.0f
	});
}

// r = d −2(d⋅n)n
inline t_vec3	vec3_reflect(const t_vec3 vec, const t_vec3 n)
{
	return (vec3_sub(vec, vec3_mult(n, 2 * ft_dot(vec, n))));
}

inline t_vec3	vec3_cross(const t_vec3 a, const t_vec3 b)
{
	return ((t_vec3){
		(a.y * b.z) - (a.z * b.y),
		(a.z * b.x) - (a.x * b.z),
		(a.x * b.y) - (a.y * b.x)
	});
}

inline t_vec3	vec3_clamp(const t_vec3 vec, double min, double max)
{
	return ((t_vec3){
		ft_clamp(vec.x, min, max),
		ft_clamp(vec.y, min, max),
		ft_clamp(vec.z, min, max)
	});
}