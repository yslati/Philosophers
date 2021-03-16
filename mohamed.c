#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
typedef struct	s_philo
{
	int			id;
	long	int limit;
	pthread_t	hl;
}				t_philo;
pthread_mutex_t forks[5];
pthread_t	ths[5];
t_philo		ps[5];
int			g_died;
long int	get_time(void)
{
	struct timeval v;
	gettimeofday(&v, NULL);
	return ((v.tv_sec * 1000) + (v.tv_usec / 1000));
}
// monitor
void	*health(void *data)
{
	t_philo *p = data;
	while (1)
	{
		if (get_time() >= p->limit)
		{
			g_died = 0;
			printf("%d is died\n", p->id);
			break;
		}
	}
	return (NULL);
}
void	*routine(void *data)
{
	t_philo *p = data;
	int left = p->id;
	int right = (p->id + 1) % 5;
	p->limit = get_time() + 800;
	pthread_create(&p->hl, NULL, health, p);
	pthread_detach(p->hl);
	while (1)
	{
		// Forks
		pthread_mutex_lock(&forks[left]);
		printf("%d has taken a fork\n", p->id);
		pthread_mutex_lock(&forks[right]);
		printf("%d has taken a fork\n", p->id);
		// Eat
		p->limit = get_time() + 800;
		printf("%d is eating\n", p->id);
		usleep(1000 * 600);
		// Release forks
		pthread_mutex_unlock(&forks[left]);
		pthread_mutex_unlock(&forks[right]);
		// Sleep
		printf("%d is sleeping\n", p->id);
		usleep(1000 * 200);
		printf("%d is thinking\n", p->id);
	}
	return (NULL);
}
int		main()
{
	g_died = 1;
	// Init Mutexes
	int i = 0;
	while (i < 5)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	// Start philosopher
	i = 0;
	while (i < 5)
	{
		ps[i].id = i;
		pthread_create(&ths[i], NULL, routine, &ps[i]);
		usleep(100);
		i++;
	}
	while (g_died)
	{
		usleep(1000);
	}
	// free
}