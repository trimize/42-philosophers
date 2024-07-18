# philosophers


Introducing threads in c, philosophers is a simple program that treats threads as living beings who need to eat, sleep and think the goal is to make them live as long as possible.
Important to note, for the bonus part threads are still used in this repo instead of processes, semaphores are still used tho.

## Installation


```bash
git clone https://github.com/trimize/42-philosophers.git && cd 42-philosophers
```

## Usage

For the mandatory part :

```bash
cd philo && make
```


For the bonus part : 


```bash
cd philo_bonus && make
```


To run the algorithm :

The program has 5 arguments and the last one is optional :

- numbers_of_philo
- time_to_die
- time_to_eat
- time_to_sleep
- number_of_time_each_philo_must_eat

Each argument can be between 1 and int MAX.
Tho if you try very big values it is at your risk.

Below is an example on how to run:

```bash
./philo 10 500 200 200 10
```

For the bonus part :

```bash
./philo_bonus 10 500 200 200 10
```

In this exmaple the program will stop when all philosophers ate 10 times.
A message is displayed when a philosopher ate enough, and the thread is stopped.


## Grade

125
