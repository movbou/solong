/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achajar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 14:45:41 by achajar           #+#    #+#             */
/*   Updated: 2025/04/20 14:45:45 by achajar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_textures(t_game *game)
{
	int	size;

	size = game->tile_size;
	game->wall = mlx_xpm_file_to_image(game->mlx, "textures/wall.xpm", &size,
			&size);
	game->player = mlx_xpm_file_to_image(game->mlx, "textures/player.xpm",
			&size, &size);
	game->collectible = mlx_xpm_file_to_image(game->mlx,
			"textures/collectible.xpm", &size, &size);
	game->exit = mlx_xpm_file_to_image(game->mlx, "textures/exit.xpm", &size,
			&size);
	game->empty = mlx_xpm_file_to_image(game->mlx, "textures/empty.xpm", &size,
			&size);
	if (!game->wall || !game->empty || !game->player || !game->exit
		|| !game->collectible)
		free_textures("Failed to load textures.", game);
}

void	map_rendder(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == '1')
				put_tile_to_window(game, x, y, game->wall);
			else if (game->map[y][x] == '0')
				put_tile_to_window(game, x, y, game->empty);
			else if (game->map[y][x] == 'P')
				put_tile_to_window(game, x, y, game->player);
			else if (game->map[y][x] == 'E')
				put_tile_to_window(game, x, y, game->exit);
			else if (game->map[y][x] == 'C')
				put_tile_to_window(game, x, y, game->collectible);
			x++;
		}
		y++;
	}
}

int	close_game(t_game *game)
{
	if (game->wall)
		mlx_destroy_image(game->mlx, game->wall);
	if (game->player)
		mlx_destroy_image(game->mlx, game->player);
	if (game->collectible)
		mlx_destroy_image(game->mlx, game->collectible);
	if (game->exit)
		mlx_destroy_image(game->mlx, game->exit);
	if (game->empty)
		mlx_destroy_image(game->mlx, game->empty);
	if (game->map)
		free_map(game->map);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(EXIT_SUCCESS);
}

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == ESC)
		close_game(game);
	else if (keycode == LEFT || keycode == 65361)
		move_player(game, game->player_x - 1, game->player_y);
	else if (keycode == RIGHT || keycode == 65363)
		move_player(game, game->player_x + 1, game->player_y);
	else if (keycode == UP || keycode == 65362)
		move_player(game, game->player_x, game->player_y - 1);
	else if (keycode == DOWN || keycode == 65364)
		move_player(game, game->player_x, game->player_y + 1);
	return (0);
}

void	handle_events(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, handle_keypress, game);
	mlx_hook(game->win, 17, 0L, close_game, game);
}
