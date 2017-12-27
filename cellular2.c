#include <string.h>
#include <unistd.h>
#include <stdlib.h>

# define SIZE 42
# define CLEAR write(STDOUT_FILENO, "\33[2J\33[0;0H", sizeof("\33[2J\33[0;0H"))

static void 				*getMap(void)
{
	int 					**array;
	int 					y;

	y = 0;
	array = malloc(sizeof(int*) * SIZE);
	while (y < SIZE)
	{
		array[y] = malloc(sizeof(int) * SIZE);
		memset(array[y], 0, sizeof(int) * SIZE);
		y++;
	}
	return (array);
}

static void 				unsetMap(int **const map)
{
	int 					y;

	y = 0;
	while (y < SIZE)
	{
		free(map[y++]);
	}
	free(map);
}

static void 				printMap(int **const map)
{
	static const char 		*print[] =
	{
		"0 ",
		"\33[38;5;201m1 \33[37m",
		"\33[38;5;200m2 \33[37m",
		"\33[38;5;199m3 \33[37m",
		"\33[38;5;198m4 \33[37m",
		"\33[38;5;197m5 \33[37m",
		"\33[38;5;196m6 \33[37m"
	};
	int 					y;
	int 					x;

	y = 0;
	x = 0;	
	while (y < SIZE)
	{
		while (x < SIZE)
		{
			write(STDOUT_FILENO, print[map[y][x]], strlen(print[map[y][x]]));
			x++;
		}
		write(STDOUT_FILENO, "\n", 1);
		x = 0;
		y++;
	}
}

static void 				seedMap(int **const map, const int nstate, const int seed)
{
	int 					y;
	int 					x;
	int 					r;

	y = 0;
	x = 0;
	while (y < SIZE)
	{
		while (x < SIZE)
		{
			r = (int)arc4random_uniform((uint32_t)seed);
			if (r)
			{
				r = (int)arc4random_uniform((uint32_t)nstate + 1);
				map[y][x] = r;
			}
			x++;
		}
		x = 0;
		y++;
	}
}

static void 				ft_make_turn(int ***map, int *const set)
{
	int **const 			m = *map;
	int **const 			new = getMap();
	int 					y;
	int 					x;
	int 					total;

	x = 1;
	y = 1;
	while (y < SIZE - 1)
	{
		while (x < SIZE - 1)
		{
			total = m[y + 1][x + 1] + m[y + 1][x] + m[y + 1][x - 1] +
					m[y][x + 1] + m[y][x - 1] +
					m[y - 1][x + 1] + m[y - 1][x] + m[y - 1][x - 1];
			total /= 8;
			if (total <= 0)
				new[y][x] = 0;
			else
				new[y][x] = total;
			x++;
		}
		x = 1;
		y++;
	}
	unsetMap(m);
	*map = new;
}

static void 				ft_cellular(int *const set)
{
	int 					**map;

	map = getMap();
	seedMap(map, *set, *(set + 1));
	CLEAR;
	printMap(map);
	sleep(1);
	while (set[2]--)
	{
		CLEAR;
		ft_make_turn(&map, set);
		printMap(map);
		sleep(1);
	}
}

// nstate[0] - seed[1] - turn[2] - survive[3]
int						 	main(int argc, char **argv)
{
	int 					set[argc - 1];
	int 					i;

	i = 0;
	while (*++argv)
	{
		set[i++] = atoi(*argv);
	}
	ft_cellular(set);
}
