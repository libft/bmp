/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 15:46:56 by Juyeong Maing     #+#    #+#             */
/*   Updated: 2023/07/02 17:02:47 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bmp.h"

#include <stdlib.h>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)

# include <io.h>

#else

# include <unistd.h>

#endif

static void	fill(void *context, size_t x, size_t y, t_ft_bmp_pixel *out)
{
	(void)context;
	out->r = 256 - x;
	out->g = 256 - y;
	out->b = 1;
}

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)

int	main(void)
{
	t_ft_bmp *const	bmp = ft_bmp_new(256, 256, fill, NULL);
	char			*result;
	size_t			length;

	if (!bmp)
		return (EXIT_FAILURE);
	if (ft_bmp_serialize(bmp, &result, &length))
	{
		free(bmp);
		return (EXIT_FAILURE);
	}
	if ((size_t)_write(1, result, length) != length)
	{
		free(result);
		free(bmp);
		return (EXIT_FAILURE);
	}
}

#else

int	main(void)
{
	t_ft_bmp *const	bmp = ft_bmp_new(256, 256, fill, NULL);
	char			*result;
	size_t			length;

	if (!bmp)
		return (EXIT_FAILURE);
	if (ft_bmp_serialize(bmp, &result, &length))
	{
		free(bmp);
		return (EXIT_FAILURE);
	}
	if ((size_t)write(1, result, length) != length)
	{
		free(result);
		free(bmp);
		return (EXIT_FAILURE);
	}
}

#endif
