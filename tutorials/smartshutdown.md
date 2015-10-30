# Shutdown Pin

Basically, you can use any available input, but this example will use pin **24**
There is a connector with 3 wires (blue/black/green) coming from the left of the Plusberry board (it's labeled "UART").
Connect the BLUE wire to pin **24** (see image) -

When you press the power button (short press), the GPIO will go from high to low, signalling the RPi to shutdown.
Now, of course, you need to write a script to actually shutdown the RPi when getting the signal.

This is a sample script for OpenELEC
```
>> nano /storage/.config/shutdown.sh
```

```bash
#!/bin/bash
# monitor GPIO pin 24 (wiringPi pin 1) for shutdown signal
# export GPIO pin 24 and set to input with pull-up
echo "24" > /sys/class/gpio/export
echo "in" > /sys/class/gpio/gpio24/direction
# wait for pin to go low
while [ true ] do
    if [ "$(cat /sys/class/gpio/gpio24/value)" == '0' ] then
      echo "Raspberry Pi Shutting Down!"
      halt & exit 0
    fi
    sleep 1
done
```

Now, add it to autostart.sh, so the script will run when booting the system

```
nano /storage/.config/autostart.sh
```
```
(/storage/.config/shutdown.sh &)&
```

### Source

https://www.indiegogo.com/projects/plusberry-pi-media-box-running-on-raspberry-pi#/updates
