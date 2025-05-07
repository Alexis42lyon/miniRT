/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppm_loader_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:47:10 by mjuncker          #+#    #+#             */
/*   Updated: 2025/05/07 09:15:23 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture_bonus.h"
#include <fcntl.h>

t_ppm_image	ppm_image(char *path, t_prog *prog)
{
	t_ppm_image	img;
	int			fd;

	if (path[0] == '#')
		return ((t_ppm_image){.header = invalid_header(), .values = NULL});
	fd = open(path, O_RDONLY);
	if (fd == -1)
		print_exit(prog, "no such file or directory");
	img.header = parse_header(fd);
	header_assert(img.header, prog);
	img.values = parse_image(&img.header, fd);
	close(fd);
	if (img.values == NULL)
		print_exit(prog, "image parsing failed");
	ft_log(SUCCESS, "%s is loaded", path);
	return (img);
}

void	print_values(t_vec3 *values, t_ppm_header *header)
{
	t_uint	i;

	i = 0;
	while (i < header->width * header->height)
	{
		print_vec(values[i]);
		i++;
	}
}

void	assign_values(
	t_vec3 *value, unsigned char buff[3], t_ppm_header *header)
{
	value->x = (double)buff[0] / header->max_values;
	value->y = (double)buff[1] / header->max_values;
	value->z = (double)buff[2] / header->max_values;
}

t_vec3	*parse_image(t_ppm_header *header, int fd)
{
	t_vec3			*values;
	unsigned char	buff[3];
	int				i;
	int				nb_read;

	i = 0;
	values = malloc(((header->width * header->height) + 2) * sizeof(t_vec3));
	if (!values)
		return (NULL);
	nb_read = -1;
	while (nb_read != 0)
	{
		nb_read = read(fd, buff, 3);
		if (nb_read == -1)
		{
			free(values);
			return (NULL);
		}
		if (nb_read != 3)
			break ;
		assign_values(&values[i], buff, header);
		i++;
	}
	return (values);
}
