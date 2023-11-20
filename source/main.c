/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/30 13:04:05 by arommers      #+#    #+#                 */
/*   Updated: 2023/11/20 11:56:16 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int argc, char *argv[])
{
	t_data		data;
	mlx_t		*mlx;
	mlx_image_t	*screen;

	mlx = NULL;
	screen = NULL;
	check_args(argc, argv);
	init_data(&data);
	input_data(argv, &data);
	init_mlx(&data);
	init_player(&data);
	init_ray(&data);
	load_textures(&data);
	mlx_image_to_window(data.mlx, data.img, 0, 0);
	mlx_loop_hook(data.mlx, &game_loop, &data);
	mlx_key_hook(data.mlx, &controls, &data);
	mlx_scroll_hook(data.mlx, &scroll, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	ft_clean(&data);
	return (0);
}
