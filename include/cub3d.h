/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/23 11:39:00 by arommers      #+#    #+#                 */
/*   Updated: 2023/10/25 11:37:19 by arommers      ########   odam.nl         */
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

typedef struct s_data
{
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	int		f_r;
	int		f_g;
	int		f_b;
	int		c_r;
	int		c_g;
	int		c_b;
	char	**map;
}		t_data;

int	main(int argc, char **argv);


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
# include <math.h>

#endif