#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include "libft.h"
# include <limits.h>
# include "./minilibx_mms/mlx.h"

# define WINDOW_X 640
# define WINDOW_Y 480

# define FILE_ERROR 100
# define MAP_ERROR 101
# define READ_ERROR 103
# define MALLOC_ERROR 102



# define W 13
# define A 0
# define S 1
# define D 2
# define LEFT 123
# define RIGHT 124
# define ESC 53

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

typedef struct s_rgb
{
	int r;
	int g;
	int b;
}t_rgb;

typedef struct s_colors
{
	t_rgb *floor;
	t_rgb *cell;
}	t_colors;

typedef struct s_texs
{
	char *no;
	char *so;
	char *we;
	char *ea;

}	t_texs;

typedef struct s_data
{
	int			move;
	char		**map;
	void		*mlx;
	void		*mlx_win;
	void		*mlx_image;
	t_texs		*texs;
	t_colors	*colors;
}	t_data;

int		get_next_line(int fd, char **line);
int		ft_strcmp(char *str1, char *str2);
int		ft_atoi_rgb(char *str);

#endif