/* ************************************************************************** */
/*                                                                            */
/*                                                            .               */
/*   tower.h                                                 / \              */
/*                                                          /   \             */
/*   By: charles <charles.cabergs@gmail.com>               /o  o \            */
/*                                                        /  v    \           */
/*   Created: 2020/06/27 14:06:50 by charles             /    _    \          */
/*   Updated: 2020/06/27 16:19:32 by charles            '-----------'         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOWER_H
# define TOWER_H

# include <stdlib.h>
# include <stdint.h>
# include <stddef.h>
# include <string.h>

# include <ncurses.h>

# define MAX_HEIGHT 128

typedef struct
{
	uint8_t	data[MAX_HEIGHT];
	size_t	len;
}			t_tower;

void	towers_init(t_tower towers[3], size_t disk_num);
void	towers_move(t_tower towers[3], size_t from, size_t to);
void	tower_put(t_tower *tower, WINDOW *win, int highlight_level);

#endif
