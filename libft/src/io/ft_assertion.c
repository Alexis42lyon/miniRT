/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_assertion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:56:02 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/29 11:24:01 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io.h"

void	print_error(const char *msg)
{
	ft_dprintf(2, "%sError\n%s\n%s", RED, msg, RESET);
}

int	malloc_assert(void *mem, const char *file, int line)
{
	if (mem)
		return (0);
	ft_dprintf(2, "%s%s:%d: %s: malloc assertion failed%s\n",
		GRAY, file, line, RED, RESET);
	return (-1);
}
