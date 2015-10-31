**This repo is a collection of tutorials and little codes that I use on my raspberry computer**

## Tutorials

-  [**DS3132 Config**](http://www.raspberrypi-spy.co.uk/2015/05/adding-a-ds3231-real-time-clock-to-the-raspberry-pi/)
-  [**Replace LXDE for XFCE**](https://github.com/maesoser/rpi_goodies/blob/master/tutorials/xfce.md)
-  [SmartShutdown Pin](https://github.com/maesoser/rpi_goodies/blob/master/tutorials/smartshutdown.md)
-  [IR Sensor](https://github.com/maesoser/rpi_goodies/blob/master/tutorials/ir_sensor.md)
-  [Conky](https://github.com/maesoser/rpi_goodies/blob/master/tutorials/conky.md)
-  [External temp sensor]()
## Tools

### temp

**temp** is a little code written in C and designed to work with [genmon](http://goodies.xfce.org/projects/panel-plugins/xfce4-genmon-plugin).
It just shows the CPU temperature, by reading `/sys/class/thermal/thermal_zone0/temp` file. I could have use a simple sh script but I decided to use C because this is just a derivation of the next program.

You can compile it easily:

You can compile it by writing this:
```
gcc -Wall -o temp temp.c
```

If you want one decimal (56,3 ºC) you should include the `-d` option.

### fan_control

**fan_control** as it name says, control the rpi's fan speed. It's also written in C and make use of the temp.c code together with the [**WiringC**](http://wiringpi.com/) library.

You can compile it by writting this:
```
gcc -Wall -o fan fan.c -lwiringPi -lpthread
```
And you should run it using `sudo` (cause of WiringC)

It has some options to fix the maximum and minimum temperature and the refresh rate as well as a "debug" mode that shows the hypothetical status of the program (temperatue and pwm value) without really acting on the Raspberry GPIO pins. You can take a look at this arguments by writing `sudo ./fan -h`

At the beginning we used pin 1 (BCM_GPIPO 18) to be PWM output, however if you are currently playing music or using the audio system via the 3.5mm jack socket, then you’ll find one channel of audio PWM coming through the pin.

So we changed to SoftwarePWM. It should work. The fan should be attached to **pin 7** but you could change this, its one of the first defines of the code.
