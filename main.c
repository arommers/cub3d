/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/23 11:42:30 by arommers      #+#    #+#                 */
/*   Updated: 2023/10/23 14:54:20 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./include/cub3d.h"

# define WIDTH 1024
# define HEIGHT 512
# define COLOR (0.3, 0.3, 0.3, 0.3)

static mlx_image_t *img;
    
int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void ft_fill(void* param)
{
    int32_t color = ft_pixel(77, 77, 77, 255);
    for (int32_t i = 0; i < WIDTH; i++)
	{
		for (int32_t y = 0; y < HEIGHT; y++)

			mlx_put_pixel(img, i, y, color);
	}
}

int main()
{
    int map[]=
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
    
    mlx_t *mlx;
    
    if (!(mlx =mlx_init(WIDTH, HEIGHT, "cub3d", false )))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
    if (!(img = mlx_new_image(mlx, WIDTH, HEIGHT)))
    {
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
    if ((mlx_image_to_window(mlx,img,0, 0)) == -1)
    {
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
    mlx_loop_hook(mlx, ft_fill, mlx);
    mlx_loop(mlx);
    mlx_terminate(mlx);
    return 0;
}

