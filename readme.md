**This repo is a collection of tutorials and little codes that I use on my raspberry computer**

## Tutorials

-  [**DS3132 Config**](http://www.raspberrypi-spy.co.uk/2015/05/adding-a-ds3231-real-time-clock-to-the-raspberry-pi/)
-  [**Replace LXDE for XFCE**](http://raspberrypi.stackexchange.com/questions/10053/changing-to-xfce-from-lxde)
-  [SmartShutdown Pin]()
-  [IR Sensor]()
-  [Conky script]()
-  [External temp sensor]()
## Tools

### temp

**temp** is a little code written in C and designed to work with [genmon](http://goodies.xfce.org/projects/panel-plugins/xfce4-genmon-plugin).
It just shows the CPU temperature, by reading `/sys/class/thermal/thermal_zone0/temp` file. I could have use a simple sh script but I decided to use C because this is just a derivation of the next program.

### fan_control

**fan_control** as it name says, control the rpi's fan speed. It's also written in C and make use of the temp.c code together with the WiringC library.
