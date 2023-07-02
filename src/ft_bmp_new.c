/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bmp_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 15:22:43 by Juyeong Maing     #+#    #+#             */
/*   Updated: 2023/07/02 16:58:29 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bmp.h"

#include <stdlib.h>

t_ft_bmp	*ft_bmp_new(
	size_t width,
	size_t height,
	void (*fill)(void *context, size_t x, size_t y, t_ft_bmp_pixel *out),
	void *context
)
{
	const size_t	size
		= sizeof(t_ft_bmp) + sizeof(t_ft_bmp_pixel) * width * height;
	t_ft_bmp *const	result = malloc(size);
	size_t			y;
	size_t			x;

	result->width = width;
	result->height = height;
	y = (size_t)-1;
	while (++y < result->height)
	{
		x = (size_t)(-1);
		while (++x < result->width)
			fill(context, x, y, &result->extra[y * result->width + x]);
	}
	return (result);
}
