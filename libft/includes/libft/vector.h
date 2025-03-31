/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:58:27 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/31 11:27:08 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

typedef struct s_vector3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;


t_vec3	new_vec3(double x, double y, double z);
t_vec3	vec3_add(const t_vec3 v1, const t_vec3 v2);
double	ft_dot(const t_vec3 v1, const t_vec3 v2);
double	vec3_lenght(const t_vec3 vec);
t_vec3	vec3_sub(const t_vec3 v1, const t_vec3 v2);
void	print_vec(t_vec3 vec);
t_vec3 vec3_divide(const t_vec3 v1, const double d);
t_vec3 vec3_mult(const t_vec3 v1, const double d);
t_vec3	unit_vec3(const t_vec3 v);
double	vec3_lenght_square(const t_vec3 vec);

#endif
