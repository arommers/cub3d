/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/23 11:42:30 by arommers      #+#    #+#                 */
/*   Updated: 2023/10/25 16:11:34 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./include/cub3d.h"

# define WIDTH 1024
# define HEIGHT 512
# define PI 3,14159
# define PI2 PI / 2
# define PI3 3 * PI / 2

static  mlx_image_t *player, *wall, *background, *dir;
static  float pdx, pdy, pa;
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
    for (int32_t i = 0; i < wall->width -1; i++)
	{
		for (int32_t y = 0; y < wall->height -1; y++)

			mlx_put_pixel(wall, i, y, color);
	}
	color = ft_pixel(192, 192, 192, 255);
    for (int32_t i = 0; i < background->width -1; i++)
	{
		for (int32_t y = 0; y < background->height -1; y++)

			mlx_put_pixel(background, i, y, color);
	}
    for (y = 0; y < mapY; y++)
    {
        for (x = 0; x < mapX; x++)
        {
            if (map[y * mapX + x] == 1)
                mlx_image_to_window(mlx, wall, y * 64, x * 64);
			else
				mlx_image_to_window(mlx, background, y * 64, x * 64); 
        }
    }
}

// void draw_rays(void *param)
// {
// 	mlx_t	*mlx = param;
// 	int32_t color = ft_pixel(255, 255, 0, 255);
	
// 	int r, mx, my, mp, dof;
// 	float rx, ry, ra, xo, yo;
	
// 	ra = pa;
// 	for (r = 0; r < 1; r++)
// 	{
// 		// Check horizontal lines
// 		dof = 0;
// 		xo = 0;
// 		yo = 0;
// 		float aTan = -1/tan(ra);
// 		if (ra > PI)
// 		{
// 			ry =((player->instances[0].y >> 6) << 6) - 0.0001;
// 			rx = ((player->instances[0].y - ry) * aTan + player->instances[0].x);
// 			yo = -64;
// 			xo = -yo * aTan;
// 		}
// 		if (ra < PI)
// 		{
// 			ry =((player->instances[0].y >> 6) << 6) + 64;
// 			rx = ((player->instances[0].y - ry) * aTan + player->instances[0].x);
// 			yo = 64;
// 			xo = yo * aTan;
// 		}
// 		if (ra == 0 || ra == PI)
// 		{
// 			rx = player->instances[0].x;
// 			ry = player->instances[0].y;
// 			while (dof < 8)
// 			{
// 				mx = (int)(rx) >> 6;
// 				my = (int) (ry) >> 6;
// 				mp = my * mapX + mx;
// 				if (mp < mapX * mapY && map[mp] == 1) // hit a wall
// 					dof = 8;
// 				else // next line
// 				{
// 					rx += xo;
// 					ry += yo;
// 					dof += 1;
// 				}
// 			}
// 		}
// 				// Check vertical lines
// 		dof = 0;
// 		xo = 0;
// 		yo = 0;
// 		float nTan = -tan(ra);
// 		if (ra > PI2 && ra < PI3)
// 		{
// 			rx =((player->instances[0].x >> 6) << 6) - 0.0001;
// 			ry = ((player->instances[0].x - rx) * nTan + player->instances[0].y);
// 			xo = -64;
// 			yo = -xo * nTan; // looking left
// 		}
// 		if (ra < PI2 || ra < PI3)
// 		{
// 			rx =((player->instances[0].x >> 6) << 6) + 64;
// 			ry = ((player->instances[0].x - rx) * nTan + player->instances[0].y);
// 			xo = 64;
// 			yo = xo * nTan; // looking right
// 		}
// 		if (ra == 0 || ra == PI)
// 		{
// 			rx = player->instances[0].x;
// 			ry = player->instances[0].y;
// 			while (dof < 8)
// 			{
// 				mx = (int)(rx) >> 6;
// 				my = (int)(ry) >> 6;
// 				mp = my * mapX + mx;
// 				if (mp < mapX * mapY && map[mp] == 1) // hit a wall
// 					dof = 8;
// 				else // next line
// 				{
// 					rx += xo;
// 					ry += yo;
// 					dof += 1;
// 				}
// 			}
// 		}
// 		mlx_put_pixel(wall, rx, ry, color);
// 	}
// }

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
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_W))
	{
		player->instances[0].x += pdx;
		player->instances[0].y += pdy;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_S))
	{
		player->instances[0].x -= pdx;
		player->instances[0].y -= pdy;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_A))
	{
		if (pa < 0)
			pa += 2 * PI;
		pa -= 0.1;
		pdx = cos(pa) * 5;
		pdy = sin(pa) * 5;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_D))
	{
		// if (pa > 2 * PI)
		// 	pa -= 2 * PI;
		pa += 0.1;
		pdx = cos(pa) * 5;
		pdy = sin(pa) * 5;
	}
}

int main()
{
    mlx_t *mlx;
    
    pdx = cos(pa) * 5; // gives you the x-component of a unit vector pointing in the direction of pa.
	pdy = sin(pa) * 5; // gives you the y-component of the same unit vector.
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
	if (!(dir = mlx_new_image(mlx, 4, 32)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
    if (!(wall = mlx_new_image(mlx, 64, 64)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(background = mlx_new_image(mlx, 64, 64)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
    draw_map(mlx);
	if ((mlx_image_to_window(mlx, player, WIDTH / 4, HEIGHT / 4)) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		EXIT_FAILURE;
	}
    mlx_loop_hook(mlx, draw_player, mlx);
    mlx_loop_hook(mlx, ft_hook, mlx);
    mlx_loop(mlx);
    mlx_terminate(mlx);
    return 0;
}

