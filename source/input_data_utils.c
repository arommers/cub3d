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
	input = malloc(sizeof(t_input));
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
