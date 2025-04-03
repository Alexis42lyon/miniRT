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
	return ((t_vec3){PCG_Hash(seed * 2), PCG_Hash(seed * 8), PCG_Hash(seed)});
}

inline t_vec3	vec3_rand_range(float range, uint seed)
{
	return ((t_vec3){
		PCG_Hash_range(range, seed),
		PCG_Hash_range(range, seed * 2),
		PCG_Hash_range(range, seed * 8)
	});
}
#include <stdio.h>
inline t_vec3	vec3_rand_unit(uint seed)
{
	int		i;
	t_vec3	v;
	double	sqlen;

	i = seed * 8;
	while (1)
	{
		v = vec3_rand_range(1, i);
		sqlen = vec3_lenght_square(v);
		if (1e-160 < sqlen && sqlen <= 1)
			return (vec3_normalize(v));
		i++;
	}
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