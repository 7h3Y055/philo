#include "philo.h"

long    ft_atoil(char const *str)
{
    long    n;
    int     i;

    n = 0;
    i = 0;
    if (!str)
        return (-1);
    while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == ' '))
        i++;
    while (str[i] && str[i] == '+')
        i++;
    while (str[i])
    {
        if (!(str[i] >= '0' && str[i] <= '9'))
            return (printf("[ERROR] Wrong input!\n"), -27);
        n = n * 10 + str[i] - '0';
        i++;
    }
    if (n > INT_MAX)
        return (-27);
    return (n);
}

long    get_time(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec * 0.001));
}

void    clean_all(t_arg *ptr)
{
    int i;

    i = -1;
    while (++i < ptr->philos_number)
    {
        pthread_mutex_destroy(&ptr->fork[i].mtx);
        pthread_mutex_destroy(&ptr->philo[i].le_th);
    }
}

int     ready_philo(t_arg *ptr)
{
    int i;

    i = 0;
    while (i < ptr->philos_number)
    {
        if (ptr->philo[i].status == 'r')
            return (i);
        i++;
    }
}


void    ft_sleep(long n)
{
    long    start;

    start = get_time();
    while (get_time() < start + n)
        usleep(10);
}



