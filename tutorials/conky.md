# Conky

First of all we are gonna install conky:

sudo apt-get install conky

Now we have to add it to startup

1. Open 'Settings Manager'
2. Select 'Session and Startup'
3. On the 'Application Autostart' click on the 'Add' button
4. On the dialog that opens write the name of the application and the command that runs the application (description isn't mandatory).
5. Once you click 'OK' the application will be added to the list and will automatically be started on the next session login.

We can customize the conky appearance by modifying  `/home/.conkyrc`. [**Here**](https://github.com/maesoser/rpi_goodies/blob/master/tutorials/.conkyrc) is my configuration

**Source**

[add application to xfce session](http://xubuntugeek.blogspot.pt/2011/12/add-application-to-xfcexubuntu-session.html)
