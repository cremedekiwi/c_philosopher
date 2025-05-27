# Dining Philosophers

A multithreaded simulation of the classic Dining Philosophers problem, implemented in C using POSIX threads (pthreads).

## Overview

The Dining Philosophers problem is a classic synchronization problem in computer science that illustrates the challenges of resource sharing in concurrent programming. This implementation simulates philosophers sitting around a circular table, each needing two forks to eat, with the goal of avoiding deadlock and starvation.

## Features

- **Thread-safe implementation** using mutexes for synchronization
- **Deadlock prevention** through careful fork assignment and philosopher desynchronization
- **Death monitoring** to detect when philosophers haven't eaten in time
- **Configurable parameters** for flexible testing scenarios
- **Debug mode** with detailed status information
- **Comprehensive error handling** for robust execution

## Project Structure

```
philo/
├── Makefile
├── includes/
│   └── philo.h          # Header file with structures and function prototypes
├── srcs/
│   ├── main.c           # Program entry point
│   ├── parsing.c        # Input validation and parsing
│   ├── init.c           # Data structure initialization
│   ├── dinner.c         # Main simulation logic
│   ├── monitor.c        # Death monitoring thread
│   ├── getters_setters.c # Thread-safe data access
│   ├── synchro_utils.c  # Synchronization utilities
│   ├── safe_functions.c # Safe wrappers for system calls
│   ├── utils.c          # Utility functions
│   └── write.c          # Status output functions
├── command.sh           # Test script with valid scenarios
└── error.sh            # Test script with invalid inputs
```

## Compilation

```bash
make
```

This will compile the project with the following flags:
- `-Wall -Wextra -Werror` for strict error checking
- `-pthread` for POSIX thread support
- `-g` for debugging information

## Usage

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Parameters

- **number_of_philosophers**: Number of philosophers (and forks) [1-200]
- **time_to_die**: Time in milliseconds after which a philosopher dies if they haven't eaten
- **time_to_eat**: Time in milliseconds it takes for a philosopher to eat
- **time_to_sleep**: Time in milliseconds a philosopher spends sleeping
- **number_of_times_each_philosopher_must_eat** (optional): Simulation stops when all philosophers have eaten this many times

### Parameter Constraints

- All time values must be at least 60ms
- Maximum 200 philosophers
- All values must be positive integers
- Values cannot exceed INT_MAX

## Examples

### Basic Usage

```bash
# 5 philosophers, die after 800ms, eat for 200ms, sleep for 200ms
./philo 5 800 200 200

# Same as above, but stop after each philosopher eats 7 times
./philo 5 800 200 200 7

# Edge case: single philosopher
./philo 1 800 200 200
```

### Test Scripts

```bash
# Run predefined valid test cases
./command.sh 1    # Single philosopher
./command.sh 2    # Basic scenario
./command.sh 3    # Limited meals
./command.sh 4    # Tight timing
./command.sh 5    # Very tight timing

# Test error handling
./error.sh 1      # Negative value
./error.sh 2      # Non-numeric input
./error.sh 3      # Value too large
./error.sh 4      # Integer overflow
./error.sh 5      # Zero value
./error.sh 6      # Too many philosophers
./error.sh 7      # Time too short
```

## Implementation Details

### Key Algorithms

**Deadlock Prevention**: Philosophers are assigned forks in a specific order (odd-numbered philosophers pick up the right fork first, even-numbered pick up the left fork first) to prevent circular waiting.

**Desynchronization**: Philosophers start at slightly different times to reduce contention and prevent synchronized behavior that could lead to starvation.

**Death Monitoring**: A separate monitor thread continuously checks if any philosopher has exceeded their time-to-die limit.

### Thread Synchronization

- **Philosopher mutexes**: Protect individual philosopher state
- **Fork mutexes**: Ensure exclusive access to forks
- **Table mutex**: Protects global simulation state
- **Write mutex**: Ensures atomic output operations

### Data Structures

```c
typedef struct s_philo {
    int         id;
    long        meals_counter;
    bool        full;
    long        last_meal_time;
    t_fork      *first_fork;
    t_fork      *second_fork;
    pthread_t   thread_id;
    t_mtx       philo_mutex;
    t_table     *table;
} t_philo;

typedef struct s_table {
    long        philo_nbr;
    long        time_to_die;
    long        time_to_eat;
    long        time_to_sleep;
    long        nbr_limit_meals;
    long        start_simulation;
    bool        end_simulation;
    bool        all_threads_ready;
    long        threads_running_nbr;
    pthread_t   monitor;
    t_mtx       table_mutex;
    t_mtx       write_mutex;
    t_fork      *forks;
    t_philo     *philos;
} t_table;
```

## Output Format

The program outputs philosopher actions in real-time:

```
0     1 has taken a fork
0     1 has taken a fork
0     1 is eating
200   1 is sleeping
400   1 is thinking
400   2 has taken a fork
...
```

Each line shows:
- **Timestamp** (milliseconds since simulation start)
- **Philosopher ID**
- **Action** (taking fork, eating, sleeping, thinking, or died)

## Debug Mode

Enable debug mode by changing `DEBUG_MODE` to 1 in `philo.h` for detailed information including:
- Fork IDs being picked up
- Meal counters
- Color-coded output

## Error Handling

The program validates all inputs and handles various error conditions:
- Invalid argument count
- Non-numeric inputs
- Negative values
- Values exceeding limits
- System call failures
- Memory allocation failures

## Performance Considerations

- **Precise timing**: Uses busy-waiting for microsecond precision
- **Efficient monitoring**: Monitor thread sleeps between checks to reduce CPU usage
- **Memory management**: Proper cleanup of all allocated resources
- **Thread safety**: All shared data access is protected by appropriate mutexes
