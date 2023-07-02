/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 15:46:56 by Juyeong Maing     #+#    #+#             */
/*   Updated: 2023/07/02 17:40:30 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bmp.h"

#include <stdio.h>
#include <stdlib.h>

static void	fill(void *context, size_t x, size_t y, t_ft_bmp_pixel *out)
{
	(void)context;
	out->r = (uint8_t)(256 - x);
	out->g = (uint8_t)(256 - y);
	out->b = (uint8_t)1;
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
	{
		fclose(fp);
		return (EXIT_FAILURE);
	}
	if (ft_bmp_serialize(bmp, &result, &length))
	{
		fclose(fp);
		free(bmp);
		return (EXIT_FAILURE);
	}
	if (fwrite(result, 1, length, fp) != length)
	{
		fclose(fp);
		free(result);
		free(bmp);
		return (EXIT_FAILURE);
	}
	fclose(fp);
	free(result);
	free(bmp);
	return (EXIT_SUCCESS);
}
