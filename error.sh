#!/bin/bash

case $1 in
	1)
	echo "./philo 1 800 200 -200"
	./philo 1 800 200 -200
	;;
	2)
	echo "./philo 1 800 200 a"
	./philo 1 800 200 a
	;;
	3)
	echo "./philo 1 800 200 12345678912"
	./philo 1 800 200 12345678912
	;;
	4)
	echo "./philo 1 800 200 2147483648"
	./philo 1 800 200 2147483648
	;;
	5)
	echo "./philo 1 800 200 0"
	./philo 1 800 200 0
	;;
	6)
	echo "./philo 201 800 200 200"
	./philo 201 800 200 200
	;;
	7)
	echo "./philo 200 800 59 200"
	./philo 200 800 59 200
	;;
	*)
	echo "Usage: ./error.sh {1|2|3|4|5|6|7}"
	;;
esac
