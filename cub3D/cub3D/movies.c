#include "cub3D.h"

static	void	ft_move_up(t_data *data)
{
	if (data->map[data->params->x - 1][data->params->y] != '1')
	{
		if (data->map[data->params->x - 1][data->params->y] == '0'
			|| data->map[data->params->x - 1][data->params->y] == 'C')
		{
			data->map[data->params->x][data->params->y] = '0';
			data->map[data->params->x - 1][data->params->y] = 'N';
		}
	}
}

static	void	ft_move_down(t_data *data)
{
	if (data->map[data->params->x + 1][data->params->y] != '1')
	{
		if (data->map[data->params->x + 1][data->params->y] == '0'
			|| data->map[data->params->x + 1][data->params->y] == 'C')
		{
			data->map[data->params->x][data->params->y] = '0';
			data->map[data->params->x + 1][data->params->y] = 'S';
		}
	}
}

static	void	ft_move_left(t_data *data)
{
	if (data->map[data->params->x][data->params->y - 1] != '1')
	{
		if (data->map[data->params->x][data->params->y - 1] == '0'
			|| data->map[data->params->x][data->params->y - 1] == 'C')
		{
			data->map[data->params->x][data->params->y] = '0';
			data->map[data->params->x][data->params->y - 1] = 'W';
		}
	}
}

static	void	ft_move_right(t_data *data)
{
	if (data->map[data->params->x][data->params->y + 1] != '1')
	{
		if ((data->map[data->params->x][data->params->y + 1] == '0'
			 || data->map[data->params->x][data->params->y + 1] == 'C'))
		{
			data->map[data->params->x][data->params->y] = '0';
			data->map[data->params->x][data->params->y + 1] = 'E';
		}
	}
}

void	player_move_draw(t_data *data)
{
	int		i;
	int		j;

	i = -1;
	while (data->map[++i])
	{
		j = -1;
		while (data->map[i][++j])
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'W'
				|| data->map[i][j] == 'E' || data->map[i][j] == 'S')
			{
				data->params->x = i;
				data->params->y = j;
			}
		}
	}
}


void	get_move_from_key(t_data *data)
{
		player_move_draw(data);
	if (data->move == D)
	{
		ft_move_right(data);
		data->move = 999;
	}
	else if (data->move == A)
	{
		ft_move_left(data);
		data->move = 999;
	}
	else if (data->move == W)
	{
		ft_move_up(data);
		data->move = 999;
	}
	else if (data->move == S)
	{
		ft_move_down(data);
		data->move = 999;
	}
}
