/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:16:11 by mjuncker          #+#    #+#             */
/*   Updated: 2025/04/08 16:54:48 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_H
# define MATH_H

typedef unsigned int	t_uint;

int		overflow_check(const char *s, void (*f)(int, void *), void *param);

int		ft_abs(float n);
int		ft_max(float a, float b);
int		ft_min(float a, float b);

t_uint	pcg_hash(t_uint input);
float	random_float(t_uint input);
float	ft_clamp(float f, float min, float max);

#endif
