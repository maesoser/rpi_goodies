/*
  C Program that takes care of the shutdown button on the PlusberryPi
  Compile with gcc -Wall -o shutbtn shutbtn.c -lwiringPi , run with sudo
*/

 /*
 Copyright 2016 Sergio Maeso Jiménez [massesos@gmail.com]
    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at
        http://www.apache.org/licenses/LICENSE-2.0
    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
 */

#include <stdio.h>
#include <wiringPi.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#define SHUTDOWN_PIN 29

int main(){

  if (wiringPiSetup () < 0)
  {
    printf ("Unable to setup wiringPi\n") ;
    return -1 ;
  }

 pinMode(SHUTDOWN_PIN, INPUT);
 pullUpDnControl(SHUTDOWN_PIN, PUD_UP);

  while(1){
  if(digitalRead(SHUTDOWN_PIN) == LOW){
      	printf("Shutting Down\n");
      	system("halt");
      	return 0;
    	}
    	sleep(1);
  }
  return -1;
}
