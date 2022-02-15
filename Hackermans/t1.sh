#!/bin/bash


time=.05

sed -n 1,38p anime.txt
sleep $time

for i in {1..520}
do
	a=$(($i*38))
	b=$(($i + 1))
	c=$(($b*38))
	sed -n $a,${c}p anime.txt
	sleep $time
done
exit 0

