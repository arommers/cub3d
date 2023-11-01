/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/23 11:39:00 by arommers      #+#    #+#                 */
/*   Updated: 2023/10/27 11:28:13 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/include/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>

# define WIDTH 1024
# define HEIGHT 512
# define PI 3.14159
# define PI2 PI / 2
# define PI3 3 * PI / 2

static mlx_image_t *player, *wall, *background, *dir, *line;
static float pdx, pdy, pa; //player position
static int mapX = 8, mapY = 8, mapS = 64;
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


typedef struct t_dir
{
	float	startx;
	float	starty;
	float	endx;
	float	endy;
}	t_dir;

typedef struct s_player
{
	float		x;
	float		y;
	float		dx;
	float		dy;
	float		angle;
	mlx_image_t	*img;
}	t_player;

typedef struct s_data
{
	char		*no_texture;
	char		*so_texture;
	char		*we_texture;
	char		*ea_texture;
	int			f_r;
	int			f_g;
	int			f_b;
	int			c_r;
	int			c_g;
	int			c_b;
	t_player	*player;
	char		**map;
}		t_data;

// Parsing the input
void	put_data(int argc, char **argv);
t_data	*map_init(t_data *data, char *with_nl, int fd, int size_map);
t_data	*texture_color_init(t_data *data, char *with_nl);
t_data	*f_c_colors(t_data *data, char *line);
t_data	*texture_data(t_data *data, char *line);
int		line_counter(char *file);
t_data	*initialize_data_struct(t_data *data);

// Check data
int		check_colors(t_data *data);
int		check_map(t_data *data);
int		check_data(t_data *data);

int main(int argc, char **argv);
//void bresenhams_line_draw(int x1, int y1, int x2, int y2, mlx_t *mlx);
void bresenhams_line_draw(int x1, int y1, int x2, int y2);
int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);

#endif