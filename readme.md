**This repo is a collection of tutorials and little codes that I use on my raspberry computer**

# Config files

-  [**Conky**](https://github.com/maesoser/rpi_goodies/blob/master/tutorials/conky.md)

# Tutorials

## [Configure DS3132 RTC Module](http://www.raspberrypi-spy.co.uk/2015/05/adding-a-ds3231-real-time-clock-to-the-raspberry-pi/)

## Replace LXDE with XFCE

Install XFCE4:
```
$ sudo apt-get install xfce4 xfce4-goodies
```
Remove all the LXDE related packages:
```
$ sudo apt-get remove lxappearance lxde lxde-* lxinput lxmenu-data lxpanel lxpolkit lxrandr lxsession* lxsession lxshortcut lxtask lxterminal
```
Due to the fact that LXterminal will also remove the Pi Store, install the pistore package back (if you want to):
```
$ sudo apt-get install pistore
```
Because the default desktop environment has been removed, XFCE4 will be set by default, so you don’t have to do anything special.

Run autoremove and autoclean to remove the packages that are not needed anymore:
```
$ sudo apt-get autoremove
$ sudo apt-get autoclean
```
Now you are done. Reboot and choose XFCE4 from the display manager:
```
$ sudo reboot
```
I extract this steps from [this tutorial](http://linuxg.net/how-to-properly-remove-lxde-and-install-xfce-on-raspbian-debian-for-raspberry-pi/)

## Turn hdmi off

This can be achieved with the command `tvservice -o`. I added this command to my `/etc/rc.local` file in order to turn off the hdmi cicuitry everytime I turn on the raspberry pi.

## Turn off Raspberry pi leds

My RPi is inside the PlusberryPi box so these lights are pretty useless. For that reason I decided to turn them off so, according to [this excellent article](http://www.midwesternmac.com/blogs/jeff-geerling/controlling-pwr-act-leds-raspberry-pi), I added this lines to `/boot/config.txt`:

```
# Disable the ACT LED.
dtparam=act_led_trigger=none
dtparam=act_led_activelow=off

# Disable the PWR LED.
dtparam=pwr_led_trigger=none
dtparam=pwr_led_activelow=off
```

## Spin down hard drive

I've found an [useful tutorial](http://www.htpcguides.com/spin-down-and-manage-hard-drive-power-on-raspberry-pi/) that explain all the steps to do this. I followed it except one thing. Instead of writting `/dev/sda` on the `/etc/hdparm.conf` file, I decided to use the uuid so the lines I added looks like this:

```
/dev/disk/by-uuid/[MY HDD UUID] {
  write_cache = on
  spindown_time = 120
}
```

In order to obtain the uuid of your drive you should use the command `blkid /dev/sda1` for instance.

# Tools

## temp

**temp** is a little code written in C and designed to work with [genmon](http://goodies.xfce.org/projects/panel-plugins/xfce4-genmon-plugin).
It just shows the CPU temperature, by reading `/sys/class/thermal/thermal_zone0/temp` file. I could have use a simple sh script but I decided to use C because this is just a derivation of the next program.

You can compile it easily:

You can compile it by writing this:
```
gcc -Wall -o temp temp.c
```

If you want one decimal (56,3 ºC) you should include the `-d` option.

## Fan control

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

## Shutdown button

**shutbtn** monitorize the [PlusberryPi](https://www.indiegogo.com/projects/plusberry-pi-media-box-running-on-raspberry-pi) shutdown button every second and executes a halt when it detects it has been pushed. You could start the program when the system starts using the steps we utilized above for fan control. The button is connected by default at GPIO 29

Compile it, move it to `/bin`, change it's permissions and finally, modify rc.local as we did above.
```
gcc -O3 -Wall -o shutbtn shutbtn.c -lwiringPi
mv shutbtn /bin/shutbtn
cd /bin
sudo chmod 775 shutbtn
nano /etc/rc.local
```
