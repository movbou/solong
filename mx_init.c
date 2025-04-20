/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mx_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achajar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 14:46:06 by achajar           #+#    #+#             */
/*   Updated: 2025/04/20 14:46:09 by achajar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_game(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		er_ex("Failed to initialize MiniLibX.", game);
	game->tile_size = 64;
	game->map_height = 0;
	while (game->map[game->map_height])
		game->map_height++;
	game->map_width = ft_strlen(game->map[0]);
	game->collectibles = 0;
	game->moves = 0;
	valid_map(game->map, game);
	count_collectibles(game);
	player_position(game);
	game->win = mlx_new_window(game->mlx, game->map_width * game->tile_size,
			game->map_height * game->tile_size, "So Long");
	if (!game->win)
		er_ex("Failed to create a game window.", game);
	load_textures(game);
	map_rendder(game);
	handle_events(game);
	mlx_string_put(game->mlx, game->win, 10, 20, 0xFF0000, "Moves :      0");
	mlx_loop(game->mlx);
}
