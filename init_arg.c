#include "philo.h"

static void    init_philos(t_arg *ptr);

int     init_arg(t_arg *ptr)
{
    int i;

    ptr->fork = malloc(sizeof(t_fork) * ptr->philos_number);
    init_philos(ptr);
    i = -1;
    while (++i < ptr->philos_number)
    {
        pthread_mutex_init(&ptr->fork[i].mtx, NULL);
        pthread_mutex_init(&ptr->philo[i].le_th, NULL);
    }
    ptr->start_time = get_time();
    ptr->finished_philos = 0;
    return (0);
}

static void    init_philos(t_arg *ptr)
{
    int i;

    ptr->philo = malloc(sizeof(t_philo) * ptr->philos_number);
    i = 0;
    while (i < ptr->philos_number)
    {
        ptr->philo[i].id = i;
        ptr->philo[i].eat_counter = 0;
        ptr->philo[i].last_eat = get_time();
        ptr->philo[i].status = 'r';
        ptr->philo[i].fork_1 = &ptr->fork[(i + 1) % ptr->philos_number];
        ptr->philo[i].fork_2 = &ptr->fork[i];
        if (i % 2)
        {
            ptr->philo[i].fork_1 = &ptr->fork[i];
            ptr->philo[i].fork_2 = &ptr->fork[(i + 1) % ptr->philos_number];
        }
        i++;
    }
}