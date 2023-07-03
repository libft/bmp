/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 00:00:00 by Juyeong Maing     #+#    #+#             */
/*   Updated: 2023/07/03 00:00:00 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_suppress_msvc_warnings.h"

#include "ft_bmp.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 1024
#define SS_RATE 2

typedef struct s_color
{
	float	r;
	float	g;
	float	b;
}	t_color;

static float	f(float x)
{
	return (1 - sqrt(1 - x / 1.42));
}

static void	calculate_position(float x, float y, float *out_x, float *out_y)
{
	const float	distance_from_center = sqrtf(x * x + y * y);
	const float direction_x = x / distance_from_center;
	const float direction_y = y / distance_from_center;
	const float new_distance_from_center = f(distance_from_center);

	*out_x = new_distance_from_center * direction_x;
	*out_y = new_distance_from_center * direction_y;
}

static void	add_color_at(size_t given_x, size_t given_y, size_t s, t_color *mut)
{
	const float	real_x = (float)given_x / s * 2 - 1;
	const float	real_y = (float)given_y / s * 2 - 1;
	float		x;
	float		y;

	calculate_position(real_x, real_y, &x, &y);
	if (((int)(fabsf(x * 20.5f) + 0.5f) % 2 == 0)
		== ((int)(fabsf(y * 20.5f) + 0.5f) % 2 == 0))
	{
		mut->r += (float)given_x / s;
		mut->g += (float)given_y / s;
		mut->b += 1;
	}
}

static void	fill(void *context, size_t x, size_t y, t_ft_bmp_pixel *out)
{
	size_t	i;
	size_t	j;
	t_color	c;

	(void)context;
	c = (t_color){0, 0, 0};
	i = (size_t)-1;
	while (++i < SS_RATE)
	{
		j = (size_t)-1;
		while (++j < SS_RATE)
			add_color_at(x * SS_RATE + i, y * SS_RATE + j, SIZE * SS_RATE, &c);
	}
	out->r = (uint8_t)(c.r / (SS_RATE * SS_RATE) * 255);
	out->g = (uint8_t)(c.g / (SS_RATE * SS_RATE) * 255);
	out->b = (uint8_t)(c.b / (SS_RATE * SS_RATE) * 255);
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
	bmp = ft_bmp_new(SIZE, SIZE, fill, NULL);
	if (!bmp)
		return (EXIT_FAILURE);
	if (ft_bmp_serialize(bmp, &result, &length))
		return (EXIT_FAILURE);
	if (fwrite(result, 1, length, fp) != length)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
