# Philosopher's Dinning Problem
This project is a simulation of the classic dining philosophers problem, implemented in C. It uses threads and mutexes to handle synchronization between philosophers.

[Dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem)

## Building the Project
To build the project, use the provided Makefile:
```sh
make
```
This will create an executable named philo.

## Running the Project
After building, you can run the project with (last arg is optional):
```sh
./philo <num_of_philos> <time_to_die> <time_to_eat> <time_to_sleep> [num_of_times_each_philo_must_eat]
```

## Cleaning Up
To clean up the build artifacts, use:
```sh
make clean
```

To also remove the built executable, use:
```sh
make fclean
```

To rebuild the project from scratch, use:
```sh
make re
```
