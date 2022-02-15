#!/bin/bash

echo "Initializing hacker mainframe"
for i in {1..10}
do
	echo "."
	sleep .25
done
alacritty --config-file ~/.config/alacritty/goober.yml -e ./t1.sh &
sleep .1
alacritty --config-file ~/.config/alacritty/goob1.yml  -e ./t2.sh &

echo "loading gibberesh daemon"
for i in {1..50}
do
	printf "."
	sleep .05
done

for i in {1..100}
do
	echo "$i%             $i%             $i%"
	sleep .05
done

proc=$(pgrep alacritty)
arr=($proc)
len=${#arr[@]}
perct=0
clear
while [ $len -ge 2 ]
do
	proc=$(pgrep alacritty)
	arr=($proc)
	len=${#arr[@]}
	perct=$(($perct+4))
	cat /usr/i686-w64-mingw32/bin/*
	clear

done


echo "Initializing neural network"
for i in {1..100}
do
	echo "breaching $i%"
	sleep .05
done
for i in {1..38}
do
	sed -n ${i}p anon.txt
	sleep .15
	
done

alacritty --config-file ~/.config/alacritty/goob1.yml  -e ./t3.sh &
alacritty --config-file ~/.config/alacritty/goob1.yml  -e ./t4.sh &
alacritty --config-file ~/.config/alacritty/goob1.yml  -e ./t5.sh &


proc=$(pgrep alacritty)
arr=($proc)
len=${#arr[@]}
perct=0
clear
while [ $len -ge 2 ]
do
	sleep .5
	proc=$(pgrep alacritty)
	arr=($proc)
	len=${#arr[@]}
	perct=$(($perct+4))
	echo "------------STEALING YOUR DATA--------------"
done
clear
cmatrix

exit
