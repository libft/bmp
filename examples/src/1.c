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

# include <limits.h>
# include <stdint.h>

# if SIZE_MAX == UINT16_MAX

typedef int16_t	t_ssize_t;

# elif SIZE_MAX == UINT32_MAX

typedef int32_t	t_ssize_t;

# elif defined(UINT64_MAX) && SIZE_MAX == UINT64_MAX

typedef int64_t	t_ssize_t;

# else
#  error "Failed to define ssize_t"
# endif

#else

# include <unistd.h>

typedef ssize_t	t_ssize_t;

#endif

static void	fill(void *context, size_t x, size_t y, t_ft_bmp_pixel *out)
{
	(void)context;
	out->r = (uint8_t)(256 - x);
	out->g = (uint8_t)(256 - y);
	out->b = (uint8_t)1;
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
	if (_write(1, result, (unsigned int)length) != (t_ssize_t)length)
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
	if (write(1, result, length) != (ssize_t)length)
	{
		free(result);
		free(bmp);
		return (EXIT_FAILURE);
	}
}

#endif
