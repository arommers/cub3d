/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/30 13:04:05 by arommers      #+#    #+#                 */
/*   Updated: 2023/10/30 16:25:26 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int main(int argc, char *argv[])
{
	mlx_t       *mlx;
    t_player    player;
    // t_data      data;
    mlx_image_t *game_window;
    
    player.x = 22;
    player.y = 12; 
    player.dirx = -1;
    player.diry = 0;
    player.planex = 0;
    player.planey = 0.66;
    player.angle = 66;
    
    put_data(argc, argv);
    
    mlx = mlx_init(WIDTH, HEIGHT, "cub3d", false);
    game_window = mlx_new_image(mlx, WIDTH, HEIGHT);
    mlx_image_to_window(mlx, game_window, 0, 0);
    // mlx_loop_hook(mlx, &game_loop, &data);
    mlx_loop(mlx);
    mlx_terminate(mlx);
    return (0);
}