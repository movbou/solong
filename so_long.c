/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achajar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 14:46:24 by achajar           #+#    #+#             */
/*   Updated: 2025/04/20 14:46:29 by achajar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		print_error("\033[1;33mUsage:\033[1;37m./so_long <map.ber>");
	game.map = read_map(argv[1]);
	init_game(&game);
	free_map(game.map);
	return (0);
}
