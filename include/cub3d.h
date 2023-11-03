/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/23 11:39:00 by arommers      #+#    #+#                 */
/*   Updated: 2023/11/02 22:12:44 by parisasadeq   ########   odam.nl         */
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

# define WIDTH 1048
# define HEIGHT 512
# define mapWidth 24
# define mapHeight 24

static int worldMap[mapWidth][mapHeight]=
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


typedef struct t_dir
{
	float	startx;
	float	starty;
	float	endx;
	float	endy;
}	t_dir;

typedef struct s_player
{
	double		x;
	double		y;
	double		dirX;
	double		dirY;
	double		planeX;
	double		planeY;
	double		cameraX;
	double		rayDirX;
	double		rayDirY;
	// length of the ray from current position to next x or y side
	double		sideDistX;
	double		sideDistY;
	//length of the ray from one x or y side to next x or y side
	double		deltaDistX;
	double		deltaDistY;
	double		perpWallDist;
	//what direction to step in x or y direction (+1 or -1)
	int			stepX;
	int			stepY;
	int			hit; //was there a wall hit?
	int			side; //was a NS or a EW wall hit?
	int			mapX;
	int			mapY;
	int			drawStart;
	int			drawEnd;
	int			lineHeight;
	int32_t		color;
	mlx_image_t	*img;
	struct s_data		*data;
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
t_data	*put_data(int argc, char **argv);
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

// Input Player
t_player	*input_player(t_player *player, int argc, char **argv);

int		main(int argc, char **argv);
//void bresenhams_line_draw(int x1, int y1, int x2, int y2, mlx_t *mlx);
void	bresenhams_line_draw(int x1, int y1, int x2, int y2, t_player *player);
int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
void	control_keys(mlx_key_data_t keydata, void *param);
//void	game_loop(t_player *player);
void	game_loop(void	*param);
void	wall_color(t_player *player);
void	draw_wall(t_player *player, int x);
void	init_deltaDist(t_player *player);
void	init_sideDist(t_player *player);
void	till_hitting_wall(t_player *player);
void	prev_fisheye(t_player *player);

#endif