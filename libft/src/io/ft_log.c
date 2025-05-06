/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_log.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:15:36 by mjuncker          #+#    #+#             */
/*   Updated: 2025/04/22 11:16:29 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io.h"
#include "libft/string.h"
#include <stdarg.h>

static int	get_next_stop(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '%')
			return (i);
		i++;
	}
	return (ft_strlen(s));
}

static int	handle_characters(const char *type, va_list *ptr, int fd)
{
	void	*tmp;

	if (*type == 'c')
		return (ft_putchar_fd(va_arg(*ptr, int) % 256, fd));
	else if (*type == 's')
	{
		tmp = va_arg(*ptr, char *);
		if (tmp == NULL)
			return (ft_putstr_fd("(null)", fd));
		return (ft_putstr_fd(tmp, fd));
	}
	else if (*type == 'p')
	{
		tmp = va_arg(*ptr, void *);
		if (tmp == NULL)
			return (ft_putstr_fd("(nil)", fd));
		return (ft_putaddr((long int)tmp, "0123456789abcdef", 1));
	}
	else if (*type == '%')
		return (ft_putchar_fd('%', 1));
	else
		return (ft_printf("%%%c", *type));
	return (0);
}

static int	handle_stop(const char *type, va_list *ptr, int fd)
{
	void	*tmp;
	int		len;

	type++;
	if (*type == 'd' || *type == 'i')
		return (ft_putnbr_fd(va_arg(*ptr, int), 1));
	else if (*type == 'u')
	{
		tmp = (char *)ft_uitoa(va_arg(*ptr, unsigned int));
		ft_putstr_fd(tmp, fd);
		len = ft_strlen(tmp);
		free(tmp);
		return (len);
	}
	else if (*type == 'x' || *type == 'X')
	{
		if (*type == 'x')
			return (ft_putnbr_hex(va_arg(*ptr, unsigned int),
					"0123456789abcdef", 1));
		else
			return (ft_putnbr_hex(va_arg(*ptr, unsigned int),
					"0123456789ABCDEF", 1));
	}
	return (handle_characters(type, ptr, fd));
}

int	set_lvl(const t_lvl_log log)
{
	static int	fds[5] = {1, 1, 2, 2, 2};

	if (log > 4)
		return (1);
	if (log == LOG)
		ft_dprintf(1, BLUE "[LOG]: " RESET);
	if (log == SUCCESS)
		ft_dprintf(1, GREEN "[SUCCESS]: " RESET);
	if (log == WARNING)
		ft_dprintf(2, YELLOW "[WARNING]: " RESET);
	if (log == ERROR)
		ft_dprintf(2, RED "[ERROR]: " RESET);
	if (log == ALERT)
		ft_dprintf(2, B_RED "[ALERT]:" RESET " ");
	return (fds[log]);
}

int	ft_log(const t_lvl_log log, const char *s, ...)
{
	size_t	nb_write;
	va_list	ptr;
	char	*block;
	int		fd;

	if (s == NULL)
		return (-1);
	fd = set_lvl(log);
	nb_write = 0;
	va_start(ptr, s);
	while (*s)
	{
		block = ft_substr(s, 0, get_next_stop(s));
		nb_write += ft_putstr_fd(block, fd);
		s += ft_strlen(block);
		if (block)
			free(block);
		if (*s != '%' || (*s == '%' && s[1] == '\0'))
			break ;
		nb_write += handle_stop(s, &ptr, fd);
		s += 2;
	}
	ft_dprintf(fd, "\n");
	return (nb_write);
}
