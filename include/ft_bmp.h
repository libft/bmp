/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bmp.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 15:16:09 by Juyeong Maing     #+#    #+#             */
/*   Updated: 2023/07/02 15:50:27 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BMP_H
# define FT_BMP_H

# include <stddef.h>
# include <stdint.h>
# include <stdbool.h>

typedef bool	t_err;

typedef struct s_ft_bmp_pixel
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
}	t_ft_bmp_pixel;

typedef struct s_ft_bmp
{
	size_t			width;
	size_t			height;
	t_ft_bmp_pixel	extra[];
}	t_ft_bmp;

/**
 * @brief deserialize buffer into BMP
 *
 * @param buffer buffer
 * @param length length of buffer
 * @param out result image, or NULL if buffer isn't valid image
 * @return t_err true on malloc() failure
 * @remarks *out may be NULL even if return value indicates non-error
 */
t_err		ft_bmp_deserialize(
				const void *buffer,
				size_t length,
				t_ft_bmp **out);
t_err		ft_bmp_serialize(
				t_ft_bmp *self,
				char **out,
				size_t *out_length);
t_ft_bmp	*ft_bmp_new(
				size_t width,
				size_t height,
				void (*fill)(
					void *context,
					size_t x,
					size_t y,
					t_ft_bmp_pixel *out),
				void *context);

#endif
