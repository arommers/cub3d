/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/13 17:29:51 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/11/20 10:39:49 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	line_counter(char *file)
{
	int		fd;
	int		count_line;
	char	*line;

	count_line = 0;
	fd = open(file, O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
		{
			break ;
		}
		count_line++;
		free(line);
	}
	close(fd);
	return (count_line);
}

t_input	*initialize_data_struct(t_input *input)
{
	input->no_texture = NULL;
	input->so_texture = NULL;
	input->we_texture = NULL;
	input->ea_texture = NULL;
	input->floor_color = false;
	input->ceiling_color = false;
	input->f_r = 0;
	input->f_g = 0;
	input->f_b = 0;
	input->c_r = 0;
	input->c_g = 0;
	input->c_b = 0;
	input->map = NULL;
	return (input);
}

t_input	*texture_data(t_input *input, char *line)
{
	char	**path_data;
	char	*texture_path;

	path_data = ft_split(line, ' ');
	texture_path = ft_strdup(path_data[1]);
	if (line[0] == 'N' && line[1] == 'O')
		input->no_texture = texture_path;
	else if (line[0] == 'S' && line[1] == 'O')
		input->so_texture = texture_path;
	else if (line[0] == 'W' && line[1] == 'E')
		input->we_texture = texture_path;
	else if (line[0] == 'E' && line[1] == 'A')
		input->ea_texture = texture_path;
	free_2darray(path_data);
	return (input);
}

t_input	*f_c_colors(t_input *input, char *line)
{
	char	*before_split;
	char	**colors;

	before_split = ft_substr(line, 2, ft_strlen(line) - 2);
	colors = ft_split(before_split, ',');
	if (line[0] == 'F')
	{
		input->floor_color = true;
		input->f_r = ft_atoi(colors[0]);
		input->f_g = ft_atoi(colors[1]);
		input->f_b = ft_atoi(colors[2]);
	}
	if (line[0] == 'C')
	{
		input->ceiling_color = true;
		input->c_r = ft_atoi(colors[0]);
		input->c_g = ft_atoi(colors[1]);
		input->c_b = ft_atoi(colors[2]);
	}
	free_2darray(colors);
	free(before_split);
	return (input);
}
