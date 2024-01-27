#include "philo.h"

int     philo(t_arg *ptr)
{
    pthread_t   m_th;
    int i;

    i = -1;
    while (++i < ptr->philos_number)
    {
        pthread_create(&ptr->philo[i].th, NULL, routine, &ptr->philo[i]);
        usleep(100);
        pthread_detach(ptr->philo[i].th);
    }
    while (ptr->status != 'd')
    {
        i = 0;
        if (ptr->finished_philos == ptr->philos_number)
        {
            ptr->status = 'd';
            break ;
        }
        while (i < ptr->philos_number)
        {
            if (ptr->philo[i].status != 'f' && get_time() - ptr->philo[i].last_eat > ptr->time_to_die)
            {
                print_status(&ptr->philo[i], 'd');
                ptr->status = 'd';
            }
            i++;
        }
    }
    i = -1;
    while (++i < ptr->philos_number)
        pthread_join(ptr->philo[i].th, NULL);
    return (0);
}

void    *routine(void *addr)
{
    t_philo   *philo;

    philo = addr;
    philo->status = 's';
    if (philo->arg->philos_number % 2 && philo->id % 2 == 0)
        ft_usleep(philo->arg->time_to_eat + 50);
    while (philo->arg->status != 'd')
    {
        pthread_mutex_lock(philo->fork_1);
        print_status(philo, 'f');
        pthread_mutex_lock(philo->fork_2);
        print_status(philo, 'f');

        ft_eat(philo);
        pthread_mutex_unlock(philo->fork_1);
        pthread_mutex_unlock(philo->fork_2);

        pthread_mutex_lock(&philo->arg->mtx);
        if (philo->status == 'f')
        {
            philo->arg->finished_philos++;
            pthread_mutex_unlock(&philo->arg->mtx);
            return (NULL);
        }
        pthread_mutex_unlock(&philo->arg->mtx);

        print_status(philo, 's');
        ft_usleep(philo->arg->time_to_sleep);
        print_status(philo, 't');
    }
    return (NULL);
}

// void    *monitor(void *addr)
// {
//     int i;
//     t_arg   *ptr;

//     ptr = addr;
//     while (1)
//     {
//         if (ptr->finished_philos == ptr->philos_number)
//             return (NULL);
//         i = 0;
//         while (i < ptr->philos_number && ptr->philo[i].status != 'f')
//         {
//             if (get_time() - ptr->philo[i].last_eat > ptr->time_to_die)
//             {
//                 print_status(&ptr->philo[i], 'd');
//                 ptr->finished_philos = 1;
//                 //pthread_mutex_lock(&ptr->mtx);
//                 //exit (0);
//                 return (NULL);
//             }
//         }
//     }
//     return (NULL);
// }

