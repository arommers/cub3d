/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/30 13:04:05 by arommers      #+#    #+#                 */
/*   Updated: 2023/11/17 14:35:59 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	main(int argc, char *argv[])
{
	t_data		data;
	mlx_t		*mlx;
	mlx_image_t	*screen;

	check_args(argc, argv);
	init_data(&data, mlx, screen);
	input_data(argv, &data);
	init_player(&data);
	init_ray(&data);
	load_textures(&data);
	mlx_image_to_window(data.mlx, data.img, 0, 0);
	make_mm_img(&data);
	mlx_loop_hook(data.mlx, &game_loop, &data);
	mlx_key_hook(data.mlx, &moves, &data);
	mlx_scroll_hook(data.mlx, &scroll, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	ft_clean(&data);
	return (0);
}
