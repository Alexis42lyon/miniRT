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
	print_ppm_header(img.header, path);
	img.values = parse_image(&img.header, fd, prog);

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
	char	*line;
	unsigned char	res;
	uint		i = 0;
	uint		j = 0;

	values = malloc(header->width * header->height * sizeof(t_vec3));
	if (!values)
		print_exit(prog, "malloc failed");
	
	line = ft_get_next_line(fd);
	if (!line)
		print_exit(prog, "malloc failed");
	res = line[i];
	i++;
	while (line && i < header->width * header->height)
	{
		if (line[i] == '\n')
		{
			line = ft_get_next_line(fd);
		}
		if (res > header->max_values)
		{
			free(values);
			print_exit(prog, "overflow in ppm file");
		}
		if (j == 0)
			values[i].x = res / (double)header->max_values;
		else if (j == 1)
			values[i - 1].y = res / (double)header->max_values;
		else if (j == 2)
			values[i - 2].z = res / (double)header->max_values;
		j++;
		j %= 3;
		res = line[i++];
		if (!line || line[i] == '\n')
		{
			line = ft_get_next_line(fd);
		}
	}
	print_values(values, header);
	return (values);
}

