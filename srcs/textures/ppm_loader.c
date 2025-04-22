/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppm_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:47:10 by mjuncker          #+#    #+#             */
/*   Updated: 2025/04/17 13:57:33 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io.h"
#include "libft/vector.h"
#include "miniRT.h"
#include "texture.h"
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

t_ppm_image		ppm_image(char *path, t_prog *prog)
{
	t_ppm_image	img;
	int			fd;

	fd = open(path, O_RDONLY);
	img.header = parse_header(fd);
	header_assert(img.header, prog);
	img.values = parse_image(&img.header, fd, prog);
	print_ppm_header(img.header, path);
	ft_printf(GREEN "[SUCCESS]: %s is loaded\n" RESET, path);
	return (img);
}

void	print_values(t_vec3* values, t_ppm_header *header)
{
	uint	i = 0;

	while (i < header->width * header->height)
	{
		print_vec(values[i]);
		i++;
	}
}

t_vec3	*parse_image(t_ppm_header *header, int fd, t_prog *prog)
{
	t_vec3	*values;
	unsigned char	buff[3];
	uint		i = 0;
	int			nb_read;

	values = malloc(header->width * header->height * sizeof(t_vec3));
	if (!values)
		print_exit(prog, "malloc failed");
	
	nb_read = -1;
	while (nb_read != 0)
	{
		nb_read = read(fd, buff, 3);
		if (nb_read == -1)
			print_exit(prog, "read call failed");
		values[i].x = (double)buff[0] / header->max_values;
		values[i].y = (double)buff[1] / header->max_values;
		values[i].z = (double)buff[2] / header->max_values;
		i++;
	}
	return (values);
}	
