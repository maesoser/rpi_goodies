**This repo is a collection of tutorials and little codes that I use on my raspberry computer**

## Tutorials

-  [**DS3132 Config**](http://www.raspberrypi-spy.co.uk/2015/05/adding-a-ds3231-real-time-clock-to-the-raspberry-pi/)
-  [**Replace LXDE for XFCE**](https://github.com/maesoser/rpi_goodies/blob/master/tutorials/xfce.md)
-  [IR Sensor](https://github.com/maesoser/rpi_goodies/blob/master/tutorials/ir_sensor.md)
-  [Conky](https://github.com/maesoser/rpi_goodies/blob/master/tutorials/conky.md)

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

### Fan control

**fan** controls the rpi's fan speed. It's also written in C and make use of the temp.c code together with the [**WiringC**](http://wiringpi.com/) library.

You can compile it by writting this:
```
gcc -O3 -Wall -o fan fan.c -lwiringPi
```

After that you could do `sudo chmod 775 fan` to execute fan easily like any other program.

You should run it using `sudo` (cause of WiringC)

If you want to start the program when raspbian boot up, you should add a line like this, just before the `exit 0` line, in file `/etc/rc.local` :

```
/home/sierra/bin/fan &
```

You do not need to worry about sudo because rc.local runs with superuser attributes. Notice that `/home/sierra/bin/fan` is the particular location of the executable file on my raspberry.

I also made the circuit depicted in this [video](https://www.youtube.com/watch?v=Ra1CY-zaDj4) cause the rPi did not gave me enough power. In my case, instead of connect the circuit to the 5v pin on the rPi I used the FAN connector of my PlusberryPi.

### Shutdown button

**shutbtn** monitorize the [PlusberryPi](https://www.indiegogo.com/projects/plusberry-pi-media-box-running-on-raspberry-pi) shutdown button every second and executes a halt when it detects it has been pushed. You could start the program when the system starts using the steps we utilized above for fan control. The button is connected by default at GPIO 29

Compile it, move it to `/bin`, change it's permissions and finally, modify rc.local as we did above.
```
gcc -O3 -Wall -o shutbtn shutbtn.c -lwiringPi
mv shutbtn /bin/shutbtn
cd /bin
sudo chmod 775 shutbtn
nano /etc/rc.local
```
