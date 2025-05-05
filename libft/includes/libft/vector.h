/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:58:27 by mjuncker          #+#    #+#             */
/*   Updated: 2025/05/02 12:52:06 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <sys/types.h>
# include "libft/math.h"

typedef unsigned int	t_uint;

typedef struct s_vector3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

float	ft_dot(const t_vec3 v1, const t_vec3 v2);

t_vec3	new_vec3(double x, double y, double z);
t_vec3	vec3_zero(void);

t_vec3	vec3_add(const t_vec3 v1, const t_vec3 v2);
double	vec3_lenght(const t_vec3 vec);
t_vec3	vec3_sub(const t_vec3 v1, const t_vec3 v2);
void	print_vec(t_vec3 vec);
t_vec3	vec3_divide(const t_vec3 v1, const double d);
t_vec3	vec3_mult(const t_vec3 v1, const double d);
t_vec3	vec3_normalize(const t_vec3 v);
double	vec3_lenght_square(const t_vec3 vec);

t_vec3	vec3_multv(const t_vec3 v1, const t_vec3 v2);

t_vec3	vec3_reflect(const t_vec3 vec, const t_vec3 n);
t_vec3	vec3_cross(const t_vec3 a, const t_vec3 b);

t_vec3	vec3_clamp(const t_vec3 vec, double min, double max);

t_vec3	random_vec(t_uint seed);

void	get_tangents(t_vec3 normal, t_vec3 *ref_tangent, t_vec3 *ref_bitangent);

#endif
