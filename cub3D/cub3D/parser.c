#include "cub3D.h"

void	rot_map(char **map, int len, int size)
{
	char	**r_map;
	int		i;
	int		j;
	int		x;

	i = 0;
	j = len;
	r_map = malloc(sizeof(char *) * (size));
	while (i < size)
	{
		if (map[j])
		{
			x = 0;
			r_map[i] = malloc(sizeof(char) * (len));
			while (j >= 0)
				r_map[i][x++] = map[j--][i];
			r_map[i][x] = '\0';
			j = len;
			i++;
		}
		else
			j--;
	}
	r_map[i] = NULL;
	check_r_map(r_map, len, size);
	free_map(r_map);
}

void	rotate_map(char **map, int len, int size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		if (ft_strlen(map[i]) < size)
		{
			j = (int)ft_strlen(map[i]);
			while (j < size)
			{
				map[i][j] = ' ';
				j++;
			}
			map[i][j] = '\0';
		}
		i++;
	}
	rot_map(map, i, size);
	free_map(map);
}

void	get_map(int i, int j, char **file, t_data *data)
{
	char	**map;
//	char	**tmp;
	int		size;
	int		len;
	int		max_len;

	size = 0;
	while (file[++i])
		++size;
	map = malloc(sizeof(char *) * (size + 1));
//	tmp = malloc(sizeof(char *) * (size + 1));
	i -= size + 1;
	max_len = (int)ft_strlen(file[i]);
	while (file[++i])
	{
//		printf("%s\n", file[i]);
		map[++j] = ft_strdup(file[i]);
//		tmp[j] = ft_strdup(file[i]);
		len = (int)ft_strlen(map[j]);
		if (len > max_len)
			max_len = len;
	}
	map[j + 1] = NULL;
//	tmp[j + 1] = NULL;
//	j = -1;
//	while(map[++j])
//		printf("%s\n", map[j]);
//	tmp = check_map(tmp, data, size, max_len);
//	rotate_map(tmp, size, max_len);
	check_map(map, data, size, max_len); //DO IT!!!!!!!!! //////////////
	data->map = map;
}

int	find_map(int *i, char **file, t_data *data)
{
	t_params	*params;
	int			j;

	params = malloc(sizeof(t_params));
	init_params(&params);
	data->params = params;
	while (file[*i])
	{
		j = 0;
		while (file[*i][j])
		{
			if (file[*i][j] == '1')
			{
				get_map((*i - 1), -1, file, data);
				return (1);
			}
			else if (file[*i][j] == ' ' || (file[*i][j] == '\t'))
				j++;
			else
				ft_error(FILE_ERROR);
		}
		(*i)++;
	}
	return (0);
}

void	parse_file(t_data *data, char **f, int *i, int *j)
{
	while (f[++(*i)])
	{
		*j = 0;
		while (f[*i][*j] && collect_all(data))
		{
			if_space(f[*i], j);
			if (f[*i][*j] == 'N' && f[*i][(*j) + 1] == 'O' && !data->txs->no)
				get_texts(j, f[*i], data, "NO");
			else if (f[*i][*j] == 'S' && f[*i][*j + 1] == 'O' && !data->txs->so)
				get_texts(j, f[*i], data, "SO");
			else if (f[*i][*j] == 'E' && f[*i][*j + 1] == 'A' && !data->txs->ea)
				get_texts(j, f[*i], data, "EA");
			else if (f[*i][*j] == 'W' && f[*i][*j + 1] == 'E' && !data->txs->we)
				get_texts(j, f[*i], data, "WE");
			else if (f[*i][*j] == 'F' && !data->colors->floor)
				get_colors(j, f[*i], data, 'F');
			else if (f[*i][*j] == 'C' && !data->colors->cell)
				get_colors(j, f[*i], data, 'C');
			else if (f[*i][*j] == '1')
				find_map(i, f, data);
			else
				ft_error(FILE_ERROR);
		}
	}
}
