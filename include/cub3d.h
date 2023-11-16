/* ************************************************************************** */
/*                                                                            */
<<<<<<< HEAD
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psadeghi <psadeghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:39:00 by arommers          #+#    #+#             */
/*   Updated: 2023/11/16 11:32:07 by psadeghi         ###   ########.fr       */
=======
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/23 11:39:00 by arommers      #+#    #+#                 */
/*   Updated: 2023/11/16 12:03:17 by arommers      ########   odam.nl         */
>>>>>>> main
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

# define TEXW 64
# define TEXH 64
# define WIDTH 1920
# define HEIGHT 1080

typedef struct s_line
{
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_line;

typedef enum e_side
{
	NO,
	EA,
	SO,
	WE,
	F
}	t_side;

typedef struct t_wall
{
	char			*path;
	mlx_texture_t	*tex;
}	t_wall;

typedef struct s_ray
{
	int				mapx; 			// Which x square of the map we are in
	int				mapy; 			// Which y square of the map we are in
	int				stepx; 			// What direction to step in during DDA (+1 or -1)
	int				stepy; 			// What direction to step in during DDA (+1 or -1) 
	int				side; 			// Did we hit a vertical or horizontal side of a wall
	int				wall; 			// Did the ray hit a wall?
	double			camera_x; 		// Coordinate in camera space
	double			dirx; 			// x part of ray direction vector
	double			diry; 			// y part of ray direction vector
	double			init_dist_x; 	// Initial length from player to first vertical wall
	double			init_dist_y; 	// Initial length from player to first horizontal wall
	double			delta_dist_x; 	// Length of the ray from one vertical line to the next
	double			delta_dist_y; 	// Length of the ray from one horizontal line to the next
	double			perp_wall_dist; // Eventual ray length/distance
	t_line			*line;
}	t_ray;

typedef struct s_player
{
	double			x;		// player x position
	double			y;		// player y position
	double			dirx;	// direction vector x position
	double			diry;	// direction vector y position
	double			planex;	// camera plane vector x position
	double			planey;	// camera plane vector y position
	mlx_image_t		*img;
	struct s_data	*data;
}	t_player;

typedef struct s_file
{
	int	fd;
	int	file_lines;
	int	lines_left;
}				t_file;

typedef struct s_input
{
	char		*no_texture;
	char		*so_texture;
	char		*we_texture;
	char		*ea_texture;
	bool		floor_color;
	bool		ceiling_color;
	int			f_r;
	int			f_g;
	int			f_b;
	int			c_r;
	int			c_g;
	int			c_b;
	t_file		*file;
	char		**map;
}	t_input;

<<<<<<< HEAD
=======
typedef struct s_file
{
	int	fd;
	int	file_lines;
	int	lines_left;
}	t_file;

>>>>>>> main
typedef struct s_data
{
	int			x;
	t_input		*input;
	int			**map;
	mlx_t		*mlx;
	t_ray		*ray;
	t_wall		*walls;
	t_player	*player;
	mlx_image_t	*img;
}	t_data;

typedef struct s_floor
{
	int		p;
	float	z;

	float	row_d;
	float	step_x;
	float	step_y;

	float	floor_x;
	float	floor_y;

	float	ray_xl;
	float	ray_yl;
	float	ray_xr;
	float	ray_yr;

	int		cell_x;
	int		cell_y;

	int		tex_x;
	int		tex_y;
}	t_floor;

// Input Data
char			player_pos(t_data *data);
void			player_direction(t_data *data, char dir);
void			check_args(int argc, char **argv);
int				line_counter(char *file);
void			check_input(t_data *data, int size_map);
int				check_wall_spaces(char **map, int size_map);
int				check_wall_leftside(char **map);
t_input			*initialize_data_struct(t_input *input);
t_input			*f_c_colors(t_input *input, char *line);
t_input			*texture_data(t_input *input, char *line);
t_input			*texture_color_init(t_input *input, char *with_nl);
t_input			*map_init(t_input *input, char *with_nl);
void			input_data(char **argv, t_data *data);
void			check_input_order(char *line, t_input *input);

// DDA algorithm function
void			game_loop(void *param);
void			prep_wall_draw(t_ray *ray);
void			calc_ray_length(t_ray *ray);
void			run_DDA_algo(t_data *data, t_ray *ray);
void			calc_start(t_ray *ray, t_player *player);
void			prep_DDA_algo(t_ray *ray, t_player *player);

// Draw functions
mlx_texture_t	*check_side(t_data *data);
void			prep_wall_draw(t_ray *ray);
void			put_ceiling(t_data *data, int x, int start);
void			draw_wall(t_data *data, int x, int start, int end);
void			prep_vert_line(t_data *data, int x, int start, int end);
void			put_vert_line(t_data *data, int start, int end, int tex_x);
int32_t			ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
void			put_floor(t_data *data, int x, int start, int height);
unsigned int	get_pixel(mlx_texture_t *texture, int32_t x, int32_t y);

void			draw_background(t_data *data);

// temporary init functions
void			init_line(t_line *line);
void			init_player(t_data *data);
void			init_ray(t_data *data);
void			init_data(t_data *data, mlx_t *mlx, mlx_image_t *img);
void			load_textures(t_data *data);

// Moves
void			clear_frame(t_data *data);
void			moves(mlx_key_data_t keydata, void *param);
void			scroll(double xdelta, double ydelta, void *param);

// Cleanup functions
void			ft_clean(t_data *data);
void			ft_error(t_data *data, char *msg);
void			clean_textures(t_data *data);
void			free_2darray(char **arr);
void			clean_input(t_input *input);

int				main(int argc, char **argv);

#endif