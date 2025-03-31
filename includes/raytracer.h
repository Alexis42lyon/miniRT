/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 10:34:28 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/31 15:33:19 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACER_H
# define RAYTRACER_H

# include "miniRT.h"
# include <math.h>

typedef struct ray
{
	t_vec3	origin;
	t_vec3	dir;

	int		lenght;
}	t_ray;

typedef struct hit_info
{
	t_vec3	hit_point;
	t_vec3	hit_normal;
	double	hit_distance;

	size_t	obj_index;

}	t_hit;

typedef struct s_win	t_win;

// colors.c
t_vec3	normal_color(t_hit hit);
unsigned int		convert_to_rgba(const t_vec3 color);

// ray.c
t_vec3	ray_to_vec(t_ray r);

// renderer.c
void	start_renderer(t_prog *prog);

#endif
