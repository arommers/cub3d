/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/23 11:42:30 by arommers      #+#    #+#                 */
/*   Updated: 2023/10/23 11:46:10 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./include/cub3d.h"
#define WIDTH	2560
#define HEIGHT	1440
int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

int main()
{
	mlx_t	*mlx;
	mlx_image_t	*image;

	mlx = mlx_init(WIDTH, HEIGHT, "MLX42", false);
	image = mlx_new_image(mlx, WIDTH, HEIGHT);
	mlx_image_to_window(mlx, image, 0, 0);
	uint32_t colour = ft_pixel(0xFF, 0xFF, 0xFF, 0xFF);
	mlx_put_pixel(image, 500, 500, colour);
	mlx_put_pixel(image, 0, 1000, colour);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return 0;
}

