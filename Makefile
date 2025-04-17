NAME = so_long
BONUS = so_long_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror
SHR_OBJ = so_long.c get_next_line_utils.c get_next_line.c free_funcs.c helper.c additonal_funcs.c init_funcs.c
SRC = map_check.c mlx_funcs.c $(SHR_OBJ)
BSRC = mlx_funcs_bonus.c map_check_bonus.c ft_itoa.c $(SHR_OBJ) helper_bonus.c
OBJ = $(SRC:.c=.o)
BOBJ = $(BSRC:.c=.o)

all : $(NAME)

$(NAME): $(OBJ) 
	$(CC) $(OBJ) -L/usr/include/minilibx-linux -lmlx -lX11 -lXext -o $(NAME)

bonus: $(BONUS)
	
$(BONUS): $(BOBJ)
	$(CC) $(BOBJ) -L/usr/include/minilibx-linux -lmlx -lX11 -lXext -o $(BONUS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ) $(BOBJ)

fclean: clean
	$(RM) $(NAME) $(BONUS)

re: fclean all

.PHONY:  all clean fclean re bonus
