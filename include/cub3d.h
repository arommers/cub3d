/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/23 11:39:00 by arommers      #+#    #+#                 */
/*   Updated: 2023/11/02 14:05:40 by adri          ########   odam.nl         */
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

typedef struct s_ray
{
	int			mapx; // Which x square of the map we are in
	int			mapy; // Which y square of the map we are in
	int			step_x; // What direction to step in during DDA (+1 or -1)
	int			step_y; // What direction to step in during DDA (+1 or -1) 
	int			side; // Did we hit a vertical or horizontal side of a wall
	bool		wall; // Did the ray hit a wall?
	double		camera_x; // Coordinate in camera space
	double		dirx; // x part of ray direction vector
	double		diry; // y part of ray direction vector
	double		init_dist_x; // Initial length from player to first vertical wall
	double		init_dist_y; // Initial length from player to first horizontal wall
	double		delta_dist_x; // Length of the ray from one vertical line to the next
	double		delta_dist_y; // Length of the ray from one horizontal line to the next
	double		perp_wall_dist; // Eventual ray length/distance
}	t_ray;

typedef struct s_player
{
	double		x;
	double		y;
	double		dirx;
	double		diry;
	double		planex;
	double		planey;
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
	t_ray		*ray;
	t_player	*player;
	char		**map;
}	t_data;

// Parsing the input
int		line_counter(char *file);
void	put_data(int argc, char **argv);
t_data	*initialize_data_struct(t_data *data);
t_data	*f_c_colors(t_data *data, char *line);
t_data	*texture_data(t_data *data, char *line);
t_data	*texture_color_init(t_data *data, char *with_nl);
t_data	*map_init(t_data *data, char *with_nl, int fd, int size_map);

// Check data
int		check_colors(t_data *data);
int		check_map(t_data *data);
int		check_data(t_data *data);

// DDA algorithm
void	game_loop(t_data *data);
void    run_DDA_algo(t_data *data, t_ray *ray);
void	calc_start(t_ray *ray, t_player *player);
void    prep_DDA_algo(t_ray *ray, t_player *player);

int main(int argc, char **argv);

#endif