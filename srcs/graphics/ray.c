#include "libft/vector.h"
#include "miniRT.h"

t_vec3	ray_to_vec(t_ray r)
{
	return (vec3_add( r.origin, vec3_mult(r.dir, r.lenght)));
}
