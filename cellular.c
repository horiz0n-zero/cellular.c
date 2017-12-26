#include <unistd.h>
#include <stdlib.h>
#include <string.h>

# define CLEAR write(STDOUT_FILENO, "\33[2J\33[0;0H", sizeof("\33[2J\33[0;0H"))

static void				 ft_cellular_print(int *const setting, int **const map)
{
	static const char 	*g_status[] =
	{
		"\33[37m0 ",
		"\33[38;2;0;255;255m1 "
	};
	int 				x;
	int 				y;
	int 				f;

	x = 1;
	y = 1;
	CLEAR;
	while (y < *setting - 1)
	{
		while (x < *setting - 1)
		{
			f = map[x][y];
			write(STDOUT_FILENO, g_status[f], strlen(g_status[f]));
			x++;
		}
		write(STDOUT_FILENO, "\n", 1);
		x = 1;
		y++;
	}
}

static void 			*get_cellular_map(int *const setting)
{
	int 				**new;
	int 				z;
	int 				x;

	new = malloc(sizeof(int*) * *setting);
	z = 0;
	while (z < *setting)
	{
		new[z] = malloc(sizeof(int) * *setting);
		memset(new[z], 0, sizeof(int) * *setting);
		x = 0;
		while (x < *setting)
		{
			if (arc4random_uniform((uint32_t)setting[3]) > 0)
				new[z][x] = 1;
			else
				new[z][x] = 0;
			x++;
		}
		z++;
	}	
	return (new);
}

static void 			ft_make_turn(int *const setting, int ***map)
{
	int **const 		new = get_cellular_map(setting);
	int **const 		m = *map;
	int 				x;
	int 				y;
	int 				total;

	x = 1;
	y = 1;
	while (y < *setting - 1)
	{
		while (x < *setting - 1)
		{
			total = m[x + 1][y + 1] + m[x + 1][y] + m[x + 1][y - 1] +
					m[x][y + 1] + m[x][y] + m[x][y - 1] +
					m[x - 1][y + 1] + m[x - 1][y] + m[x - 1][y - 1];
			if (total > setting[2])
				new[x][y] = 1;
			else
				new[x][y] = 0;
			x++;
		}
		x = 1;
		y++;
	}
	*map = new;
}

static void				ft_cellular(int *const setting)
{
	int 				**map = get_cellular_map(setting);

	**map = 1;
	while (setting[1]-- > 0)
	{
		ft_make_turn(setting, &map);
		ft_cellular_print(setting, map);
		sleep(1);
	}
}

int 					main(int argc, char **argv)
{
	int 				setting[4];
	int 				index;

	memset(setting, 0, sizeof(setting));
	index = 0;
	while (*++argv)
	{
		setting[index++] = atoi(*argv);
	}
	CLEAR;
	ft_cellular(setting);
}
