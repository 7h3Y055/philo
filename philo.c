#include "philo.h"

void    ft_printf(t_arg *ptr)
{
    int i = 0;

    while (i < ptr->philos_number)
    {
        if (i % 2 == 0)
            printf("%p %d %p \n", ptr->philo[i].fork_2, ptr->philo[i].id, ptr->philo[i].fork_1);
        else
            printf("%p %d %p \n", ptr->philo[i].fork_1, ptr->philo[i].id, ptr->philo[i].fork_2);
        i++;
    }
}


int     philo(t_arg *ptr)
{
    int i;

    i = -1;
    while (++i < ptr->philos_number)
    {
        pthread_create(&ptr->philo[i].th, NULL, routine, &ptr->philo[i]);
        pthread_detach(ptr->philo[i].th);
    }
    pthread_create(&ptr->philo[i].th, NULL, monitor, ptr);
    i = -1;
    while (++i < ptr->philos_number)
        pthread_join(ptr->philo[i].th, NULL);
    pthread_join(ptr->philo[i].th, NULL);
    return (0);
}

void    *routine(void *addr)
{
    t_philo   *philo;

    philo = addr;
    philo->status = 's';
    if ((philo->id) % 2 == 0)
        usleep(50);
    if ((philo->id) == 4)
        usleep(200);
    pthread_mutex_lock(&philo->arg->mtx);
    while (philo->status != 'f' || !philo->arg->finished_philos)
    {
        pthread_mutex_unlock(&philo->arg->mtx);
        printf("%ld\t%d is thinking\n", get_time() - philo->arg->start_time, philo->id);
        pthread_mutex_lock(&philo->fork_1->mtx);
        printf("%ld\t%d has taken a fork\n", get_time() - philo->arg->start_time, philo->id);
        pthread_mutex_lock(&philo->fork_2->mtx);
        printf("%ld\t%d has taken a fork\n", get_time() - philo->arg->start_time, philo->id);
        printf("%ld\t%d is eating\n", get_time() - philo->arg->start_time, philo->id);
        philo->last_eat = get_time();
        pthread_mutex_lock(&philo->le_th);
        philo->eat_counter++;
        if (philo->eat_counter == philo->arg->eat_times)
            philo->status = 'f';
        pthread_mutex_unlock(&philo->le_th);
        ft_sleep(philo->arg->time_to_eat);
        pthread_mutex_unlock(&philo->fork_1->mtx);
        pthread_mutex_unlock(&philo->fork_2->mtx);
        printf("%ld\t%d is sleeping\n", get_time() - philo->arg->start_time, philo->id);
        ft_sleep(philo->arg->time_to_sleep);
        pthread_mutex_lock(&philo->arg->mtx);
    }
    pthread_mutex_unlock(&philo->arg->mtx);
    return (NULL);
}

void    *monitor(void *addr)
{
    int i;
    t_arg   *ptr;

    ptr = addr;
    while (1)
    {
        i = 0;
        while (i < ptr->philos_number)
        {
            if (get_time() - ptr->philo[i].last_eat > ptr->time_to_die)
            {
                printf("%ld\t%d died\n", get_time() - ptr->start_time, i);
                ptr->finished_philos = 1;
                pthread_mutex_lock(&ptr->mtx);
                //exit (0);
                return (NULL);
            }
        }
    }
    return (NULL);
}

