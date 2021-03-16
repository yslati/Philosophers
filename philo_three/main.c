#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

/**
 * n 2-200
 * die 60
 * eat 60
 * sleep 60
 * ? eat count
 */

int		g_n;
int		g_die;
int		g_eat;
int		g_sleep;
int		g_eatc;

typedef struct	s_philo
{

}				t_philo;

int			is_degit(int n)
{
	return (n >= '0' && n <= '9');
}

void		health(void* data)
{

}

static	int	ft_help(long a, int sign)
{
	if (a < 0 && sign > 0)
		return (-1);
	if (a > 0 && sign < 0)
		return (0);
	return (a);
}

int			ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	a;

	a = 0;
	i = 0;
	sign = 1;
	while (str[i] == '\t' || str[i] == '\f' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
	{
		if (str[i] > '9' || str[i] < 48)
			break ;
		a = (a * 10) + str[i] - 48;
		i++;
	}
	a = a * sign;
	return (ft_help(a, sign));
}

/**
* n 2-200
* die 60
* eat 60
* sleep 60
* ? eat count
*/

int			args_isnumeric(char **av, int ac)
{
	int i;
	int j;

	j = 0;
	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
			if (!is_degit(av[i][j++]))
			{
				printf("wrong argument !\n");
				return (0);
			}
		i++;
	}
	return (1);
}

int		get_value(char **av, int ac)
{
	g_n = ft_atoi(av[1]);
	g_die = ft_atoi(av[2]);
	g_eat = ft_atoi(av[3]);
	g_sleep = ft_atoi(av[4]);
	g_eatc = (ac == 6) ? ft_atoi(av[5]) : -1;
	if (g_n < 2 || g_n > 200 || g_die < 60 || g_eat < 60 || g_sleep < 60)
	{
		printf("wrong argument !\n");
		return (0);
	}
	return (1);
}

int			main(int ac,char **av)
{
	t_philo		p;

	if (ac < 5 || ac > 6)
	{
		printf("wrong argument !\n");
		return (1);
	}
	else
	{
		if (!args_isnumeric(av, ac) || !get_value(av, ac))
			return (1);
		if (g_eatc == 0)
			return (0);
	}
	return (0);
}
