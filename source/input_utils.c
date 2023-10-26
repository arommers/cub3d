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

t_data	*initialize_data_struct(t_data *data)
{
	data->no_texture = NULL;
	data->so_texture = NULL;
	data->we_texture = NULL;
	data->ea_texture = NULL;
	data->f_r = 0;
	data->f_g = 0;
	data->f_b = 0;
	data->c_r = 0;
	data->c_g = 0;
	data->c_b = 0;
	data->map = NULL;
	return (data);
}
