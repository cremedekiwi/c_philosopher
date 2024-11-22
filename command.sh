#!/bin/bash

case $1 in
	1)
	echo "./philo 1 800 200 200"
	./philo 1 800 200 200
	;;
	2)
	echo "./philo 5 800 200 200"
	./philo 5 800 200 200
	;;
	3)
	echo "./philo 5 800 200 200 7"
	./philo 5 800 200 200 7
	;;
	4)
	echo "./philo 4 410 200 200"
	./philo 4 410 200 200
	;;
	5)
	echo "./philo 4 310 200 100"
	./philo 4 310 200 100
	;;
	*)
	echo "Usage: ./command.sh {1|2|3|4|5}"
	;;
esac
