/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 10:34:28 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/31 10:49:31 by mjuncker         ###   ########.fr       */
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

typedef struct s_win	t_win;

// colors.c
t_vec3	sp_normal_color(t_sphere *sp, t_ray r, double t);
int		convert_to_rgba(const t_vec3 color);

// ray.c
t_vec3	ray_to_vec(t_ray r);

// renderer.c
void	start_renderer(t_prog *prog);

#endif
