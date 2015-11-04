#!/bin/bash

# monitor GPIO pin 24 (wiringPi pin 1) for shutdown signal
# export GPIO pin 24 and set to input with pull-up

gpio mode 24 input  #echo "24" > /sys/class/gpio/export
gpio mode 24 up     #echo "in" > /sys/class/gpio/gpio24/direction

# wait for pin to go low

while [ true ]
do
if [ $(gpio read 24) -eq 0 ]
then
 echo "Raspberry Pi Shutting Down!"
 halt &
 exit 0
fi
sleep 1
done
