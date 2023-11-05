/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/23 11:39:00 by arommers      #+#    #+#                 */
/*   Updated: 2023/11/05 16:23:44 by adri          ########   odam.nl         */
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

# define MAPW 24
# define MAPH 24
# define TEXW 64
# define TEXH 64
# define WIDTH 1024
# define HEIGHT 512

typedef struct s_line
{
	int		line_height;
	int		draw_start;
	int		draw_end;
	
}	t_line;

typedef struct t_wall
{
	char			*path;
	mlx_texture_t	*tex;
}	t_wall;

typedef struct s_ray
{
	int			mapx; // Which x square of the map we are in
	int			mapy; // Which y square of the map we are in
	int			stepx; // What direction to step in during DDA (+1 or -1)
	int			stepy; // What direction to step in during DDA (+1 or -1) 
	int			side; // Did we hit a vertical or horizontal side of a wall
	int			wall; // Did the ray hit a wall?
	double		camera_x; // Coordinate in camera space
	double		dirx; // x part of ray direction vector
	double		diry; // y part of ray direction vector
	double		init_dist_x; // Initial length from player to first vertical wall
	double		init_dist_y; // Initial length from player to first horizontal wall
	double		delta_dist_x; // Length of the ray from one vertical line to the next
	double		delta_dist_y; // Length of the ray from one horizontal line to the next
	double		perp_wall_dist; // Eventual ray length/distance
	t_line		*line;
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
	// char		*no_texture;
	// char		*so_texture;
	// char		*we_texture;
	// char		*ea_texture;
	// int			f_r;
	// int			f_g;
	// int			f_b;
	// int			c_r;
	// int			c_g;
	// int			c_b;
	int			(*map)[MAPH];
	mlx_t		*mlx;
	t_ray		*ray;
	t_wall		*walls;
	t_player	*player;
	mlx_image_t	*img;
}	t_data;

// Parsing the input
// int		line_counter(char *file);
// void	put_data(int argc, char **argv);
// t_data	*initialize_data_struct(t_data *data);
// t_data	*f_c_colors(t_data *data, char *line);
// t_data	*texture_data(t_data *data, char *line);
// t_data	*texture_color_init(t_data *data, char *with_nl);
// t_data	*map_init(t_data *data, char *with_nl, int fd, int size_map);

// // Check data
// int		check_map(t_data *data);
// int		check_data(t_data *data);
// int		check_colors(t_data *data);

// DDA algorithm function
void	game_loop(void *param);
void	prep_wall_draw(t_ray *ray);
void    calc_ray_length(t_ray *ray);
void    run_DDA_algo(t_data *data, t_ray *ray);
void	calc_start(t_ray *ray, t_player *player);
void    prep_DDA_algo(t_ray *ray, t_player *player);

// Draw functions
void    	prep_wall_draw(t_ray *ray);
// void   		draw_wall(t_data *data, int x, int start, int end);
void    	put_texture(t_data *data, int x, int start, int end);
int32_t		ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
int32_t		get_pixel(mlx_texture_t *texture, int32_t x, int32_t y);



// temporary init functions
void 	init_line(t_line *line);
void 	init_player(t_player *player);
void 	init_ray(t_ray *ray, t_line *line);
void 	init_data(t_data *data, t_player *player, t_ray *ray);
void    load_textures(t_data *data);

// Moves
void	clear_frame(t_data *data);
void	moves(mlx_key_data_t keydata, void *param);

int main(int argc, char **argv);

#endif