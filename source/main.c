/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/23 11:42:30 by arommers      #+#    #+#                 */
/*   Updated: 2023/10/27 11:26:29 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// # define WIDTH 1024
// # define HEIGHT 512
// # define PI 3.14159
// # define PI2 PI / 2
// # define PI3 3 * PI / 2

// static  mlx_image_t *player, *wall, *background, *dir, *line;
// static  float pdx, pdy, pa; //player position
// static  int mapX = 8, mapY = 8, mapS = 64;
// static  int map[]=
// 	{
// 		1,1,1,1,1,1,1,1,
// 		1,0,1,0,0,0,0,1,
// 		1,0,1,0,0,0,0,1,
// 		1,0,1,0,0,0,0,1,
// 		1,0,0,0,0,0,0,1,
// 		1,0,0,0,0,1,0,1,
// 		1,0,0,0,0,0,0,1,
// 		1,1,1,1,1,1,1,1,
// 	};

void bresenhams_line_draw(int x1, int y1, int x2, int y2)
{
	printf("in the begining\n");
	int32_t color = ft_pixel(255, 255, 0, 255);
	printf("after color\n");
	int dx = (x2 - x1); // x difference
	int dy = (x2 - x1); // y difference
	int m = dy/dx; // slope
	printf("m = %d\n", m);
	if (m < 1)
	{
		printf("are we here?");
		int decision_parameter = 2*dy - dx;
		int x = x1; // initial x
		int y = y1; // initial y
		if (dx < 0) // decide the first point and second point
		{
			x = x2; // making second point as first point
			y = y2;
			x2 = x1;
		}
		mlx_put_pixel(background, x, y, color);// plot a point
		while (x < x2) // from 1st point to 2nd point
		{
			if (decision_parameter >= 0)
			{
				x = x+1;
				y = y+1;
				decision_parameter = decision_parameter + 2*dy - 2*dx * (y+1 - y);
			}
			else
			{
				x = x+1;
				y = y;
				decision_parameter = decision_parameter + 2*dy - 2*dx * (y - y);
			}
			mlx_put_pixel(background, x, y, color);
		}
	}
	else if (m > 1)
	{
		printf("here????\n");
		int decision_parameter = 2*dx - dy;
		int x = x1; // initial x
		int y = y1; // initial y
		if (dy < 0)
		{
			x = x2;
			y = y2;
			y2 = y1;
		}
		mlx_put_pixel(background, x, y, color);
		while (y < y2)
		{
			if (decision_parameter >= 0)
			{
				x = x+1;
				y = y+1;
				decision_parameter = decision_parameter + 2*dx - 2*dy * (x+1 - x);
			}
			else
			{
				y = y+1;
				x = x;
				decision_parameter = decision_parameter + 2*dx - 2*dy * (x- x);
			}
			mlx_put_pixel(background, x, y, color);
		}
	}
	else if (m == 1)
	{
		printf("are we here?\n");
		int x = x1;
		int y = y1;
		printf("x = %d\n", x);
		mlx_put_pixel(background, x, y, color);
		printf("didnt get here\n");
		while (x < x2)
		{
			x = x+1;
			y = y+1;
			mlx_put_pixel(background, x, y, color);
		}
		//mlx_image_to_window(mlx, background, y * 64, x * 64); 
	}
}

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void draw_map(mlx_t *mlx)
{
	int32_t	x, y;

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
	mlx_image_to_window(mlx, background, 0, 0); 
	for (y = 0; y < mapY; y++)
	{
		for (x = 0; x < mapX; x++)
		{
			if (map[y * mapX + x] == 1)
				mlx_image_to_window(mlx, wall, y * 64, x * 64);
			// else
			// 	mlx_image_to_window(mlx, background, y, x); 
		}
	}
}

void draw_player(void* param)
{
	mlx_t* mlx = param;
	int32_t color = ft_pixel(255, 255, 0, 255);
	for (int32_t i = 0; i < player->width; ++i)
	{
		for (int32_t y = 0; y < player->height; ++y)

			mlx_put_pixel(player, i, y, color);
	}
	color = ft_pixel(255, 0, 0, 255);
	// mlx_put_pixel(background, player->instances[0].x, player->instances[0].y, color);
	// color = ft_pixel(0, 0, 255, 255);
	// mlx_put_pixel(background, player->instances[0].x + 5, player->instances[0].y + 5, color);
	bresenhams_line_draw(player->instances[0].x, player->instances[0].y, player->instances[0].x + 5 , player->instances[0].y + 5);
	// for (int32_t i = player->width; i < dir->width; ++i)
	// {
	// 	for (int32_t y = 0; y < player->height; ++y)

	// 		mlx_put_pixel(dir, i, y, color);
	// }
	// printf("after draw are we here?\n");
	// color = ft_pixel(255, 0, 0, 255);
	// mlx_put_pixel(player, 0, 0, color);
	//bresenhams_line_draw(, 0, 10, 10);
}

// void draw_player_and_line(void* param)
// {
//     mlx_t* mlx = param;
//     int32_t color = ft_pixel(255, 255, 0, 255);

//     draw_player(param);

//     int line_length = 32;
//     int x1 = player->instances[0].x + (pdx * line_length);
//     int y1 = player->instances[0].y + (pdy * line_length);

//     draw_line(line, player->instances[0].x, player->instances[0].y, x1, y1, color);
// }


void ft_hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_W))
	{
		int x1 = player->instances[0].x;
		int y1 = player->instances[0].y;
		player->instances[0].x += pdx;
		player->instances[0].y += pdy;
		dir->instances[0].x += pdx;
		dir->instances[0].y += pdy;
		// printf("pdx = %f and pdy = %f\n", pdx, pdy);
		// int x2 = player->instances[0].x;
		// int y2 = player->instances[0].y;
		// printf("x2- x1 = %d\n", x2 - x1);
		// bresenhams_line_draw(x1, y1, x2, y2);
		// int32_t color = ft_pixel(255, 0, 0, 255);
		// mlx_put_pixel(player, pdx, pdy, color);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_S))
	{
		player->instances[0].x -= pdx;
		player->instances[0].y -= pdy;
		dir->instances[0].x -= pdx;
		dir->instances[0].y -= pdy;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_A))
	{	// for (int32_t i = player->width; i < dir->width; ++i)
	// {
	// 	for (int32_t y = 0; y < player->height; ++y)

	// 		mlx_put_pixel(dir, i, y, color);
	// }
		pa -= 0.1;
		if (pa < 0)
			pa += (2 * PI);
		pdx = cos(pa) * 5;
		pdy = sin(pa) * 5;
		// int32_t color = ft_pixel(255, 0, 0, 255);
		// mlx_put_pixel(player, pdx, pdy, color);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_D))
	{
		pa += 0.1;
		if (pa > (2 * PI))
			pa -= (2 * PI);
		pdx = cos(pa) * 5;
		pdy = sin(pa) * 5;
	} 
}

int main(int argc, char **argv)
{
	mlx_t *mlx;

	put_data(argc, argv);
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
	if (!(dir = mlx_new_image(mlx, 20, 20)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	// if (!(line = mlx_new_image(mlx, WIDTH, HEIGHT)))
	// {
    // 	mlx_close_window(mlx);
    // 	puts(mlx_strerror(mlx_errno));
    // 	return(EXIT_FAILURE);
	// }
    if (!(wall = mlx_new_image(mlx, 64, 64)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(background = mlx_new_image(mlx, 512, 512)))
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
	if ((mlx_image_to_window(mlx, dir, WIDTH / 4, HEIGHT / 4)) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		EXIT_FAILURE;
	}
	// mlx_loop_hook(mlx, draw_player, mlx);
	mlx_loop_hook(mlx, draw_player, mlx);
	mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return 0;
}

