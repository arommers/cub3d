/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_util.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: adri <adri@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/19 10:06:46 by adri          #+#    #+#                 */
/*   Updated: 2023/11/19 22:58:53 by adri          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*	- Combines the RGBA components into a single integer
	  where the most significant byte is the red component
	  followed by green, blue, and alpha
	- The color components are bit shifted
	  and combined using the bitwise OR operator*/

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

/*	- Retrieves the RGB values of a pixel from a texture (mlx_texture_t)
	  at the specified coordinates (x, y)
	- We calculate the linear index that corresponds to our 2D coordinates (x, y) */

unsigned int	get_pixel(mlx_texture_t	*t, int32_t x, int32_t y)
{
	int	r;
	int	g;
	int	b;

	r = t->pixels[(y * t->width + x) * t->bytes_per_pixel];
	g = t->pixels[(y * t->width + x) * t->bytes_per_pixel + 1];
	b = t->pixels[(y * t->width + x) * t->bytes_per_pixel + 2];

	return ((unsigned int)(r << 24 | g << 16 | b << 8 | 255));
}

/*	Fill in the celing color pixels on the x coordinate of the screen 
	until the start of the texture */

void	put_ceiling(t_data *data, int x, int start)
{
	int		y;
	int32_t	color;

	y = 0;
	color = ft_pixel(data->input->c_r, data->input->c_g, data->input->c_b, 255);
	while (y < start)
		mlx_put_pixel(data->img, x, y++, color);
}

/*	Fill in the floor color pixels on the x coordinate of the screen 
	from the end of the texture untill the bottom */

void	put_floor(t_data *data, int x, int start, int height)
{
	int32_t	color;

	color = ft_pixel(data->input->f_r, data->input->f_g, data->input->f_b, 255);
	while (start < height)
		mlx_put_pixel(data->img, x, start++, color);
}