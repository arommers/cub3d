#include "../include/cub3d.h"

// void	vertical_line_drew(int x, int y1, int y2, t_player *player)
// {
// 	int	dx;
// 	int	dy;
// 	int	m;

// 	dx = 0;
// 	dy = y2 - y1;
// 	m = 0;
// 	int decision_parameter = 2*dy - dx;
// 	int x = x1; // initial x
// 	int y = y1; // initial y
// 	if (dx < 0) // decide the first point and second point
// 	{
// 		x = x2; // making second point as first point
// 		y = y2;
// 		x2 = x1;
// 	}
// 	mlx_put_pixel(player->img, x, y, player->color);// plot a point
// 	while (x < x2) // from 1st point to 2nd point
// 	{
// 		if (decision_parameter >= 0)
// 		{
// 			x = x+1;
// 			y = y+1;
// 			decision_parameter = decision_parameter + 2*dy - 2*dx * (y+1 - y);
// 		}
// 		else
// 		{
// 			x = x+1;
// 			y = y;
// 			decision_parameter = decision_parameter + 2*dy - 2*dx * (y - y);
// 		}
// 		mlx_put_pixel(player->img, x, y, player->color);
// 	}
// }

void bresenhams_line_draw(int x1, int y1, int x2, int y2, t_player *player)
{
	int dx = (x2 - x1); // x difference
	int dy = (x2 - x1); // y difference
	int m = dy/dx; // slope
	printf("m = %d\n", m);
	if (m < 1)
	{
		int decision_parameter = 2*dy - dx;
		int x = x1; // initial x
		int y = y1; // initial y
		if (dx < 0) // decide the first point and second point
		{
			printf("getting here?\n");
			x = x2; // making second point as first point
			y = y2;
			x2 = x1;
		}
		mlx_put_pixel(player->img, x, y, player->color);// plot a point
		while (x < x2) // from 1st point to 2nd point
		{
			printf("or here?\n");
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
			mlx_put_pixel(player->img, x, y, player->color);
		}
	}
	else if (m > 1)
	{
		int decision_parameter = 2*dx - dy;
		int x = x1; // initial x
		int y = y1; // initial y
		if (dy < 0)
		{
			x = x2;
			y = y2;
			y2 = y1;
		}
		mlx_put_pixel(player->img, x, y, player->color);
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
			mlx_put_pixel(player->img, x, y, player->color);
		}
	}
	else if (m == 1)
	{
		int x = x1;
		int y = y1;
		mlx_put_pixel(player->img, x, y, player->color);
		while (x < x2)
		{
			x = x+1;
			y = y+1;
			mlx_put_pixel(player->img, x, y, player->color);
		}
		//mlx_image_to_window(mlx, background, y * 64, x * 64); 
	}
}