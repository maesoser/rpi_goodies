# Replace LXDE with XFCE

Install XFCE4:

```
$ sudo apt-get install xfce4 xfce4-goodies
```
Remove all the LXDE related packages:
```
$ sudo apt-get remove lxappearance lxde lxde-* lxinput lxmenu-data lxpanel lxpolkit lxrandr lxsession* lxsession lxshortcut lxtask lxterminal
```
Due to the fact that LXterminal will also remove the Pi Store, install the pistore package back:
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
### Source

http://linuxg.net/how-to-properly-remove-lxde-and-install-xfce-on-raspbian-debian-for-raspberry-pi/
