/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakherra <aakherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 08:25:22 by aakherra          #+#    #+#             */
/*   Updated: 2025/02/18 09:36:38 by aakherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "/usr/include/minilibx-linux/mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include <stdbool.h>
# include <X11/X.h>
# include <X11/keysym.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# ifndef TILE_SIZE
#  define TILE_SIZE 64
# endif

# ifndef BG
#  define BG 2
# endif

# ifndef COLS
#  define COLS 7
# endif

# ifndef EX
#  define EX 6
# endif

# ifndef PLY
#  define PLY 4
# endif

typedef struct s_points
{
	size_t	x;
	size_t	y;
}	t_points;

typedef struct mystruct
{
	bool		exit_ac;
	size_t		coll_count;
	size_t		x;
	size_t		y;
}	t_mystruct;

typedef struct s_data {
	int			dir;
	char		**m;
	void		*mlx;
	void		*win;
	void		*bg_sprites[BG];
	void		*cols_sprites[COLS];
	void		*ply_sprites[PLY];
	void		*ex_sprites[EX];
	void		*enemy;
	bool		at_exit;
	size_t		coll_count;
	size_t		total_coll;
	size_t		moves;
	size_t		i;
	t_points	*pl_cords;
	t_points	*size;
}	t_data;

int		on_destroy(t_data *data);
int		handle_input(int keycode, t_data *data);
int		ft_strcmp(const char *s1, const char *s2);
char	*get_next_line(int fd);
char	*ft_itoa(int n);
char	*ft_strdup(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, size_t start, size_t len);
char	*my_strdup(char *s);
char	**allocate(size_t y, char *file);
void	ft_putstr(char *s, int fd);
void	load_textures(void *mlx, int s, int t, void **arr);
void	free_all(char **p, size_t j, int fd);
void	free_and_exit(int fd, char *s);
void	exit_with_err(char *s, int f, char **m);
void	helper(char **m, t_points *cords, size_t *t, t_points *pl_cords);
void	set_window(char **m, t_points *size, t_points *pl_cords, size_t t);
void	check_pl_access(char **m, t_mystruct *s, size_t x, size_t y);
void	move_ply(t_data *data, size_t y, size_t x, int dir);
void	add_check(char c, size_t *t, char **m);
void	check_ext(char *s);
void	set_exit(t_data *data, int x, int y);
void	check_dir(t_data *data);
void	put_to_win(t_points *size, t_data *data, t_points *cords, t_points *l);
void	set_window(char **m, t_points *size, t_points *pl_cords, size_t t);
void	free_m(char **m);
void	display_win(t_data *data);
void	ft_putnbr(size_t n);
size_t	get_line_len(char *s);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);

#endif
