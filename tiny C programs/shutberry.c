/*
 * C Program that takes care of the shutdown button on the PLusberryPi
 */
#include <stdio.h>
#include <wiringPi.h>

#define SHUTDOWN_PIN 5 //24 en BCM GPIO

int main(){

    if(wiringPiSetup(){
      return -1;
    }

    pinMode (SHUTDOWN_PIN, INPUT) ;
    pullUpDnControl (SHUTDOWN_PIN, PUD_UP) ;

    while(1){
      if(digitalRead (SHUTDOWN_PIN) == LOW){
        printf("Shutting Down\n");
        system("halt");
        exit(0);
      }
      delay 1;
    }
    return -2;
}
