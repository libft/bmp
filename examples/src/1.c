/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 15:46:56 by Juyeong Maing     #+#    #+#             */
/*   Updated: 2023/07/02 17:46:57 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_suppress_msvc_warnings.h"

#include "ft_bmp.h"

#include <stdio.h>
#include <stdlib.h>

static void	fill(void *context, size_t x, size_t y, t_ft_bmp_pixel *out)
{
	(void)context;
	out->r = (uint8_t)x;
	out->g = (uint8_t)y;
	out->b = 255;
}

int	main(int argc, char **argv)
{
	FILE		*fp;
	t_ft_bmp	*bmp;
	char		*result;
	size_t		length;

	if (argc != 2)
	{
		if (printf("usage: %s output_filename\n", argv[0]) < 0)
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	fp = fopen(argv[1], "wb");
	if (!fp)
		return (EXIT_FAILURE);
	bmp = ft_bmp_new(256, 256, fill, NULL);
	if (!bmp)
		return (EXIT_FAILURE);
	if (ft_bmp_serialize(bmp, &result, &length))
		return (EXIT_FAILURE);
	if (fwrite(result, 1, length, fp) != length)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
