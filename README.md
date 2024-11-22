# philosopher
## Introduction
This project is part of the **42 School curriculum** and explores the concept of multithreading, synchronization, and concurrency through the implementation of the **Dining Philosophers Problem**, originally proposed by Edsger Dijkstra. The project simulates philosophers alternating between eating, thinking, and trying to acquire forks (resources), emphasizing proper resource management to avoid **deadlocks**, **starvation**, or **race conditions**.

## Overview
The **Dining Philosophers Problem** involves:
- **N Philosophers** sitting at a circular table.
- **N Forks**, with one placed between each philosopher.
- Philosophers alternately **think**, **eat**, and **attempt to pick up forks** (two are required to eat).

The challenge lies in avoiding:
- **Deadlocks**: All philosophers simultaneously pick up one fork, causing a circular wait.
- **Starvation**: A philosopher fails to get both forks indefinitely.
- **Race Conditions**: Incorrect shared resource access due to improper synchronization.

This project aims to implement the solution using:
- **Threads**: Each philosopher as a separate thread.
- **Mutexes**: Forks protected by mutexes to prevent concurrent access.
- **Custom Logic**: To handle edge cases like starvation or timing issues.

## Installation
1. **Clone the Repository**:
   ```bash
   git clone https://github.com/cremedekiwi/c_philosopher.git philosopher
   cd philosopher
   ```

2. **Compile the Program**:
   Use the provided `Makefile` to compile:
   ```bash
   make
   ```

3. **Clean Up**:
   Remove compiled binaries or object files:
   ```bash
   make clean
   ```

## Usage
1. **Run the Program**:
   ```bash
   ./philosopher <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
   ```

   - **number_of_philosophers**: Total number of philosophers and forks.
   - **time_to_die**: Time (ms) before a philosopher dies without eating.
   - **time_to_eat**: Time (ms) a philosopher spends eating.
   - **time_to_sleep**: Time (ms) a philosopher spends sleeping.
   - **number_of_times_each_philosopher_must_eat** (optional): Stops simulation after all philosophers have eaten this many times.

2. **Example**:
   ```bash
   ./philosopher 5 800 200 200
   ```

   Simulates 5 philosophers with the specified time constraints.

## Implementation Details

1. **Philosophers as Threads**:
   - Each philosopher is a thread executing an infinite loop of thinking, eating, and sleeping.

2. **Forks as Mutexes**:
   - Each fork is protected by a mutex to ensure proper synchronization.

3. **Avoiding Deadlocks**:
   - Philosophers pick up the forks in a defined order (e.g., lowest-numbered fork first).

4. **Avoiding Starvation**:
   - Introduce mechanisms to prioritize philosophers who have eaten the least.

5. **Timing**:
   - Accurate timing is ensured using `gettimeofday` or other high-resolution timers.
