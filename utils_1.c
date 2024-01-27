#include "philo.h"

void    ft_eat(t_philo *philo)
{
    print_status(philo, 'e');
    //pthread_mutex_lock(&philo->arg->mtx);
    philo->eat_counter++;
    if (philo->eat_counter == philo->arg->eat_times)
        philo->status = 'f';
    philo->last_eat = get_time();
    //pthread_mutex_unlock(&philo->arg->mtx);
    ft_usleep(philo->arg->time_to_eat);
}
