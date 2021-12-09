#SRCS		= main.c
##			  free_arg.c pipex.c child.c \
#
##BSRCS		= ... //bonus part
#
#OBJS		= $(SRCS:.c=.o)
#
##BOBJS		= $(BSRCS:.c=.o) //bonus part
#
#LIBDIR		= Libft
#
#LIBFT_LIB	= $(LIBDIR)/libft.a
#
#LIB			= -L$(LIBDIR) -lft
#
#MLXDIR		= minilibx_mms
#
#MLX			= $(MLXDIR)/libmlx.dylib
#
#MLX_START	= -lmlx -framework OpenGL -framework AppKit
#
#NAME		= cub3D
#
#CC			= gcc
#
#CFLAGS		= -Wall -Werror -Wextra -I
#
#RM			= rm -f
#
#%.o: %.c	Makefile cub3D.h
#			$(CC) $(CFLAGS) $(LIBDIR) $(MLXDIR) -c $< -o $@
#
#$(NAME):	$(LIBFT_LIB) $(OBJS) $(MLX)
#			$(CC) $(CFLAGS) $(LIBDIR) $(OBJS) -o $(NAME) $(LIB) $(MLX_START)
#
#all:		$(NAME)
#
#$(LIBFT_LIB):	tools ;
#
#tools:
#			make -C $(LIBDIR)
#
#$(MLX):		tools2 ;
#
#tools2:
#			$(MAKE) -C $(MLXDIR)
#
#clean:
#			$(MAKE) clean -C $(LIBDIR) $(MLXDIR)
#			$(RM) $(OBJS) $(BOBJS)
#
#fclean:		clean
#			make fclean -C $(LIBDIR)
#			$(RM) $(NAME) $(MLX)
#
#re:			fclean all
#
#.PHONY:		all clean fclean re tools tools2
#
