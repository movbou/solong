/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achajar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 14:45:17 by achajar           #+#    #+#             */
/*   Updated: 2025/04/20 14:45:23 by achajar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include "ft_printf/ft_printf.h"
# include "gnl/get_next_line_bonus.h"
# include "libft/libft.h"
# include <mlx.h>

# define UP 119
# define DOWN 115
# define RIGHT 100
# define LEFT 97
# define ESC 65307

typedef struct so_game
{
	char	**map;
	void	*mlx;
	void	*win;
	void	*wall;
	void	*player;
	void	*collectible;
	void	*exit;
	void	*empty;
	int		tile_size;
	int		map_width;
	int		map_height;
	int		moves;
	int		player_x;
	int		player_y;
	int		collectibles;	
}	t_game;

typedef struct s_counts
{
	int	c_count;
	int	p_count;
	int	e_count;
}	t_counts;

typedef struct s_xy
{
	int	x;
	int	y;
}	t_xy;

void	print_error(char *msg);
char	**read_map(const char *file_path);
char	*read_file(int fd);
void	path_check(char *path);
int		is_wall(const char *line);
void	valid_map(char **map, t_game *game);
void	components_check(char **map, t_game *game);
void	components_count(char **map, t_counts *counts, t_game *game);
int		is_path_accessible(char **map, t_xy *tr, t_game *game, int itemes);
void	free_map(char **map);
void	init_game(t_game *game);
void	count_collectibles(t_game *game);
void	player_position(t_game *game);
void	load_textures(t_game *game);
void	map_rendder(t_game *game);
void	load_textures(t_game *game);
void	handle_events(t_game *game);
int		close_game(t_game *game);
int		handle_keypress(int key, t_game *game);
void	move_player(t_game *game, int new_x, int new_y);
void	put_tile_to_window(t_game *game, int x, int y, void *tile);
void	draw_moves(t_game *game);
void	check_windows_size(t_game *game);
void	er_ex(char *msg, t_game *game);
void	free_exit(char *msg, char *line, char *temp);
void	free_textures(char *msg, t_game *game);

#endif
