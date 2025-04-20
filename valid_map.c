/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achajar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 14:46:34 by achajar           #+#    #+#             */
/*   Updated: 2025/04/20 14:46:39 by achajar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	components_count(char **map, t_counts *counts, t_game *game)
{
	int	i;
	int	j;

	i = 0;
	counts->c_count = 0;
	counts->p_count = 0;
	counts->e_count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'C')
				counts->c_count++;
			else if (map[i][j] == 'P')
				counts->p_count++;
			else if (map[i][j] == 'E')
				counts->e_count++;
			else if (map[i][j] != '0' && map[i][j] != '1')
				er_ex("Map contains invalid characters", game);
			j++;
		}
		i++;
	}
}

void	components_check(char **map, t_game *game)
{
	t_counts	counts;

	components_count(map, &counts, game);
	if (counts.p_count != 1)
		er_ex("Map must have exactly one player (P)", game);
	if (counts.c_count < 1)
		er_ex("Map must have at lest one collectible (C)", game);
	if (counts.e_count != 1)
		er_ex("Map must have exactly one exit (E)", game);
}

int	is_wall(const char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1')
			return (0);
		i++;
	}
	return (1);
}

void	valid_map(char **map, t_game *game)
{
	int		i;
	int		row_len;
	t_xy	tr;

	i = 0;
	row_len = ft_strlen(map[i]);
	while (map[i])
	{
		if ((int)ft_strlen(map[i]) != row_len)
			er_ex("Map is not rectangular.", game);
		i++;
	}
	i = 0;
	while (map[i])
	{
		if ((i == 0 || map[i + 1] == NULL) && !is_wall(map[i]))
			er_ex("Top or Bottom row is not properly enclosed by walls", game);
		if (map[i][0] != '1' || map[i][row_len - 1] != '1')
			er_ex("Left or Right side wall is missing at row index", game);
		i++;
	}
	components_check(map, game);
	check_windows_size(game);
	if (!is_path_accessible(map, &tr, game, 0))
		er_ex("Cannot reach all collectibles or exit", game);
}
