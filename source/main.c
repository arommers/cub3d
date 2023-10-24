/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/23 11:42:30 by arommers      #+#    #+#                 */
/*   Updated: 2023/10/23 16:21:02 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

# define WIDTH 1024
# define HEIGHT 512

static  mlx_image_t *player, *wall;
static  float px, py;
static  int mapX = 8, mapY = 8, mapS = 64;
static  int map[]=
    {
        1,1,1,1,1,1,1,1,
        1,0,1,0,0,0,0,1,
        1,0,1,0,0,0,0,1,
        1,0,1,0,0,0,0,1,
        1,0,0,0,0,0,0,1,
        1,0,0,0,0,1,0,1,
        1,0,0,0,0,0,0,1,
        1,1,1,1,1,1,1,1,	
    };

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void draw_map(mlx_t *mlx)
{
    int32_t     x, y;

    int32_t color = ft_pixel(255, 255, 255, 255);
    for (int32_t i = 0; i < wall->width; i++)
	{
		for (int32_t y = 0; y < wall->height; y++)

			mlx_put_pixel(wall, i, y, color);
	}
    for (y = 0; y < mapY; y++)
    {
        for (x = 0; x < mapX; x++)
        {
            if (map[y * mapX + x] == 1)
                mlx_image_to_window(mlx, wall, y * 64, x * 64);    
        }
    }
}

void draw_player(void* param)
{
    int32_t color = ft_pixel(255, 255, 0, 255);
    for (int32_t i = 0; i < player->width; ++i)
	{
		for (int32_t y = 0; y < player->height; ++y)

			mlx_put_pixel(player, i, y, color);
	}
}

void ft_hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		player->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		player->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		player->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		player->instances[0].x += 5;
}

int main(int argc, char **argv)
{
	mlx_t *mlx;

	put_data(argc, argv);
	if (!(mlx =mlx_init(WIDTH, HEIGHT, "cub3d", false )))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(player = mlx_new_image(mlx, 14, 14)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if ((mlx_image_to_window(mlx, player, WIDTH / 2, HEIGHT / 2)) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		EXIT_FAILURE;
	}
	if (!(wall = mlx_new_image(mlx, 64, 64)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	mlx_loop_hook(mlx, ft_hook, mlx);
	draw_map(mlx);
	mlx_loop_hook(mlx, draw_player, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return 0;
}

