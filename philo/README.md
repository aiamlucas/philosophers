*This project has been created as part of the 42 curriculum by lbueno-m*

# Philosophers

> Five philosophers sit at a round table. Each needs two forks to eat. Don't let them starve.

---

## Description

This project is a C implementation of the **Dining Philosophers Problem**, a classic computer science problem originally formulated by Edsger Dijkstra in 1965.

The goal is to simulate N philosophers sitting around a table, each alternating between three states
 - thinking 
 - eating
 - sleeping 

without ever dying of starvation and without causing a deadlock.

The simulation runs with the following constraints:

- Each philosopher is represented as a separate **thread**
- Each fork between two philosophers is protected by a **mutex**
- A philosopher dies if they have not started eating within `time_to_die` milliseconds since their last meal or the start of the simulation
- The simulation ends when a philosopher dies, or when all philosophers have eaten a minimum number of times (if specified)
- Philosophers do not communicate with each other

Key concepts covered: POSIX threads, mutexes, race conditions and deadlock

---

## Instructions

### Compilation

```
make
```

To compile with debug symbols:
```
make DEBUG=1
```

To compile for use with Helgrind:
```
make HELGRIND=1
```

To clean object files:
```
make clean
```

To clean everything including the binary:
```
make fclean
```

### Usage

```
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

### Examples

```
# 5 philosophers, dies after 800ms, eats for 200ms, sleeps for 200ms
./philo 5 800 200 200

# Same but stops after each philosopher has eaten 7 times
./philo 5 800 200 200 7

# 1 philosopher will always die (only one fork available)
./philo 1 800 200 200
```

### Checking for data races

```
make HELGRIND=1
valgrind --tool=helgrind ./philo 5 800 200 200
```

---

## Resources

- https://en.wikipedia.org/wiki/Thread_(computing)
- https://en.wikipedia.org/wiki/Concurrent_computing
- https://en.wikipedia.org/wiki/Parallel_computing
- https://en.wikipedia.org/wiki/Multi-core_processor
- https://en.wikipedia.org/wiki/Dining_philosophers_problem
- https://www.youtube.com/@CodeVault
- man pages: pthread_create, pthread_join, pthread_mutex_init, pthread_mutex_lock
pthread_mutex_destroy, gettimeofday and usleep.

### AI Usage

Claude/Chatgpt were used during this project exclusively
through their standard chat interfaces (no agents, no automated code generation,
no plugins, etc.) was used during this project for:
- Code review: help in refactoring and reviewing the logic 
- Understanding concepts: help clarifying concepts related to multithreading and parallel programming, including race conditions, deadlock, starvation, mutex synchronization, etc.
- Documentation: helping generating this README.md
- Testing: generate different inputs to test edge cases, etc.
