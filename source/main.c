/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/30 13:04:05 by arommers      #+#    #+#                 */
/*   Updated: 2023/11/02 21:28:20 by adri          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void init_data(t_data *data, t_player *player, t_ray *ray, int map[][MAPH])
{
    data->player = player;
    data->ray = ray;
    data->map = (int **)map;
}

void init_player(t_player *player)
{
    player->x = 22;
    player->y = 12; 
    player->dirx = -1;
    player->diry = 0;
    player->planex = 0;
    player->planey = 0.66;
    player->angle = 66;
}

void init_ray(t_ray *ray, t_line *line)
{
    ray->mapx = 0;
    ray->mapy = 0;
    ray->stepx = 0;
    ray->stepy = 0;
    ray->side = 0;
    ray->wall = false;
	ray->camera_x = 0.0;
	ray->dirx = 0.0;
	ray->diry = 0.0;
	ray->init_dist_x= 0.0;
	ray->init_dist_y = 0.0;
	ray->delta_dist_x = 0.0;
	ray->delta_dist_y = 0.0;
	ray->perp_wall_dist = 0.0;
    ray ->line = line;
}

void init_line(t_line *line)
{
    line->line_height = 0;
    line->draw_start = 0;
    line->draw_end = 0;
}

int main(int argc, char *argv[])
{
	int worldMap[MAPW][MAPH] =
    {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
        {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
        {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };
    
    t_data      data;
    t_player    player;
    t_ray       ray;
    t_line      line;
    
    mlx_t       *mlx;
    mlx_image_t *game_window;
    
    init_data (&data, &player, &ray, worldMap);
    data.mlx = mlx;
    data.img = game_window;
    init_player(&player);
    init_ray(&ray, &line);
    init_line(&line);
    
    // put_data(argc, argv);
    
    mlx = mlx_init(WIDTH, HEIGHT, "cub3d", false);
    game_window = mlx_new_image(mlx, WIDTH, HEIGHT);
    mlx_image_to_window(mlx, game_window, 0, 0);
    mlx_loop_hook(mlx, &game_loop, &data);
    mlx_loop(mlx);
    mlx_terminate(mlx);
    return (0);
}