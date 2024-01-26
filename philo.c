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

    // printf("%ld\n", ptr->time_to_die);
    // printf("%ld\n", ptr->time_to_eat);
    // printf("%ld\n", ptr->time_to_sleep);
    // exit(0);
    i = -1;
    while (++i < ptr->philos_number)
        pthread_create(&ptr->philo[i].th, NULL, routine, ptr->philo[i]);//----
    pthread_create(&ptr->philo[i].th, NULL, monitor, ptr);
    i = -1;
    while (++i < ptr->philos_number)
        pthread_join(ptr->philo[i].th, NULL);
    pthread_join(ptr->philo[i].th, NULL);
    return (0);
}

void    *routine(void *addr)
{
    int id;
    t_arg   *ptr;

    ptr = addr;
    id = ready_philo(ptr);
    ptr->philo[id].status = 's';
    while (1)
    {
        if (ptr->philo[id].status == 'd')
            return (NULL);
        if (ptr->philo[id].eat_counter == ptr->eat_times)
        {
            ptr->philo[id].status = 'f';
            break ;
        }
        printf("%ld\t%d is thinking\n", get_time() - ptr->start_time, id);
        pthread_mutex_lock(&ptr->philo[id].fork_1->mtx);
        printf("%ld\t%d has taken a fork\n", get_time() - ptr->start_time, id);
        pthread_mutex_lock(&ptr->philo[id].fork_2->mtx);
        printf("%ld\t%d has taken a fork\n", get_time() - ptr->start_time, id);
        printf("%ld\t%d is eating\n", get_time() - ptr->start_time, id);
        ptr->philo[id].last_eat = get_time();
        pthread_mutex_lock(&ptr->philo[id].le_th);
        ptr->philo[id].eat_counter++;
        ft_sleep(ptr->time_to_eat);
        pthread_mutex_unlock(&ptr->philo[id].le_th);
        pthread_mutex_unlock(&ptr->philo[id].fork_1->mtx);
        pthread_mutex_unlock(&ptr->philo[id].fork_2->mtx);
        printf("%ld\t%d is sleeping\n", get_time() - ptr->start_time, id);
        ft_sleep(ptr->time_to_sleep);
        
    }
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
                exit(0);
            }
        }
    }
}

