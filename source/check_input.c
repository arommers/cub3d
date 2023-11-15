/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/13 17:17:58 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/11/15 12:49:58 by parisasadeq   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_colors(t_input *input)
{
	t_input	*temp;

	temp = input;
	if (temp->f_r > 255 || temp->f_r < 0)
		return (1);
	if (temp->f_g > 255 || temp->f_g < 0)
		return (1);
	if (temp->f_b > 255 || temp->f_b < 0)
		return (1);
	if (temp->c_r > 255 || temp->c_r < 0)
		return (1);
	if (temp->c_g > 255 || temp->c_g < 0)
		return (1);
	if (temp->c_b > 255 || temp->c_b < 0)
		return (1);
	return (0);
}

int	check_map_char(t_input *input)
{
	t_input	*temp;
	int		i;
	int		j;

	temp = input;
	i = 0;
	j = 0;
	while (temp->map[i] != NULL)
	{
		while (temp->map[i][j] != '\0')
		{
			if (!(temp->map[i][j] == '0' || \
			temp->map[i][j] == '1' || temp->map[i][j] == ' ' \
			|| temp->map[i][j] == 'N' || temp->map[i][j] == 'S' || \
			temp->map[i][j] == 'W' || temp->map[i][j] == 'E'))
				return (1);
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

void	check_input_order(char *line, t_input *input)
{
	if (!line)
	{
		if (input->file->lines_left == 0)
			printf("invalid map\n");
		else
			printf("allocation failed!\n");
		exit (1);
	}
	if (input->no_texture == NULL || input->so_texture == NULL || \
	input->ea_texture == NULL || input->we_texture == NULL || \
	input->ceiling_color == false || input->floor_color == false)
	{
		printf("Invalid map!\n");
		exit (1);
	}
}

void	check_input(t_data *data, int size_map)
{
	t_input	*temp;

	temp = data->input;
	if (check_colors(data->input) != 0)
		ft_error(data, "Colors should be in the range of 0 to 255\n");
	if (check_map_char(data->input) != 0)
		ft_error(data, "Map should only contain 0s and 1s\n");
	if (check_wall_spaces(temp->map, size_map) != 0 || \
	check_wall_leftside(data->input->map) != 0)
		ft_error(data, "Map should be surrounded by walls\n");
}

void	check_args(int argc, char **argv)
{
	char	*cub_file;
	int		filename_size;

	filename_size = ft_strlen(argv[1]);
	if (argc > 2 || argc == 1)
	{
		printf("Put the right amount of input\n");
		exit (1);
	}
	cub_file = ft_substr(argv[1], filename_size - 4, 4);
	if (ft_strncmp(cub_file, ".cub", 4) != 0)
	{
		printf("File name is not valid!");
		free(cub_file);
		exit (1);
	}
	free(cub_file);
}
