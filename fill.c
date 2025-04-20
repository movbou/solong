/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achajar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 14:48:55 by achajar           #+#    #+#             */
/*   Updated: 2025/04/20 14:48:57 by achajar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	flood_fill(char **map, int row, int col, int *items)
{
	if (map[row][col] == '1' || map[row][col] == 'V')
		return ;
	if (map[row][col] == 'C' || map[row][col] == 'E')
	{
		(*items)++;
		if (map[row][col] == 'E')
		{
			map[row][col] = '1';
			return ;
		}
	}
	map[row][col] = 'V';
	flood_fill(map, row + 1, col, items);
	flood_fill(map, row - 1, col, items);
	flood_fill(map, row, col + 1, items);
	flood_fill(map, row, col - 1, items);
}

static char	**copy_map(char **map, t_game *game)
{
	char	**m_copy;
	int		i;

	i = 0;
	while (map[i])
		i++;
	m_copy = malloc(sizeof(char *) * (i + 1));
	if (!m_copy)
		er_ex("Allocation failed", game);
	i = 0;
	while (map[i])
	{
		m_copy[i] = ft_strdup(map[i]);
		if (!m_copy)
		{
			while (--i >= 0)
				free(m_copy[i]);
			free(m_copy);
			er_ex("Allocation failed", game);
		}
		i++;
	}
	m_copy[i] = NULL;
	return (m_copy);
}

int	is_path_accessible(char **map, t_xy *tr, t_game *game, int itemes)
{
	char		**map_copy;
	t_counts	counts;
	int			required_items;

	tr->y = 0;
	itemes = 0;
	map_copy = copy_map(map, game);
	components_count(map, &counts, game);
	required_items = counts.e_count + counts.c_count;
	while (map[tr->y])
	{
		tr->x = 0;
		while (map[tr->y][tr->x])
		{
			if (map[tr->y][tr->x] == 'P')
			{
				flood_fill(map_copy, tr->y, tr->x, &itemes);
				break ;
			}
			tr->x++;
		}
		tr->y++;
	}
	free_map(map_copy);
	return (itemes == required_items);
}
