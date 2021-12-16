#include "cub3D.h"

void	ft_send_key(int key, t_data *data)
{
	if (key == W)
		data->move = W;
	else if (key == S)
		data->move = S;
	else if (key == A)
		data->move = A;
	else if (key == D)
		data->move = D;
	else if (key == ESC)
		ft_close(data);
}

void	drawing_map(t_data *data, int x, int y)
{
	int		i;
	int		j;

	i = -1;
	while (data->map[++i])
	{
		x = 0;
		j = -1;
		while (data->map[i][++j])
		{
			if (data->map[i][j] == '1')
				mlx_put_image_to_window(data->mlx, data->mlx_win, \
										data->mlx_image, x, y);
			if (data->map[i][j] == 'N' || data->map[i][j] == 'W'
				|| data->map[i][j] == 'S' || data->map[i][j] == 'E')
				mlx_put_image_to_window(data->mlx, data->mlx_win, \
										data->mlx_image, x, y);
			if (data->map[i][j] == 'C')
				mlx_put_image_to_window(data->mlx, data->mlx_win, \
										data->coin, x, y);
			x += 20;
		}
		y += 20;
	}
}

int	action(t_data *data)
{
	data->loop_counter++;
	mlx_clear_window(data->mlx, data->mlx_win);
	drawing_map(data, 0, 0);
	get_move_from_key(data);
	coin_animations(data);
	return (0);
}

int	button_pressed(int key, t_data *data)
{
	ft_send_key(key, data);
	printf("%d\n", key);
	return (key);
}

void	run(t_data *data)
{
	mlx_data_init(data);
	mlx_loop_hook(data->mlx, action, data);
	mlx_hook(data->mlx_win, 17, 0, ft_close, data);;
	mlx_hook(data->mlx_win, 02, (1L << 2), button_pressed, data);
	mlx_loop(data->mlx);
	exit(0);
}
