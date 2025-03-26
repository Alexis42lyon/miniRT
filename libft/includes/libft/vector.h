/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:58:27 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/25 08:53:50 by mjuncker         ###   ########.fr       */
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


t_vec3	ft_vec3new(double x, double y, double z);
t_vec3	vec3_add(const t_vec3 v1, const t_vec3 v2);
double	ft_dot(const t_vec3 v1, const t_vec3 v2);
double	vec3_magn(const t_vec3 vec);
t_vec3	vec3_sub(const t_vec3 v1, const t_vec3 v2);
void	print_vec(t_vec3 vec);
t_vec3 vec3_divide(const t_vec3 v1, const double d);

#endif
