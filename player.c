/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achajar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 14:46:14 by achajar           #+#    #+#             */
/*   Updated: 2025/04/20 14:46:19 by achajar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_moves(t_game *game)
{
	char	*str;

	str = ft_itoa(game->moves);
	if (!str)
		free_textures("Failed to allocate memory.", game);
	mlx_string_put(game->mlx, game->win, 10, 20, 0x00FF00, "Moves : ");
	mlx_string_put(game->mlx, game->win, 130, 20, 0x00FF00, str);
	free(str);
}

void	handle_collectible(t_game *game, int new_x, int new_y)
{
	if (game->map[new_y][new_x] == 'C')
		game->collectibles--;
}

int	handle_exit(t_game *game, int new_x, int new_y)
{
	int	move;

	if (game->map[new_y][new_x] == 'E')
	{
		if (game->collectibles > 0)
			return (0);
		ft_printf("\033[1;32m\nCongratulations! You won!\n\033[0m");
		move = game->moves + 1;
		ft_printf("\033[1;33m\n    Score: %d moves\n\n\033[0m", move);
		close_game(game);
	}
	return (1);
}

void	move_player(t_game *game, int new_x, int new_y)
{
	if (new_x < 0 || new_x >= game->map_width
		|| new_y < 0 || new_y >= game->map_height)
		return ;
	if (game->map[new_y][new_x] == '1')
		return ;
	handle_collectible(game, new_x, new_y);
	if (!handle_exit(game, new_x, new_y))
		return ;
	game->map[game->player_y][game->player_x] = '0';
	game->player_x = new_x;
	game->player_y = new_y;
	game->map[new_y][new_x] = 'P';
	game->moves++;
	map_rendder(game);
	draw_moves(game);
}
