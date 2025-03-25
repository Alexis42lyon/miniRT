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


t_vec3	ft_vec3new(int x, int y, int z);
t_vec3	vec3_add(t_vec3 v1, t_vec3 v2);
int		ft_dot(t_vec3 v1, t_vec3 v2);
int		vec3_magn(t_vec3 vec);

#endif
