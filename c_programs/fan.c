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

/*
Program that controlls a fan attached to a raspbery pi.
It turn on and off the fan depending on the temperature recived by the cpu sensor

Compile with gcc -Wall -o fan fan.c -lwiringPi , run with sudo
*/

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <stdint.h>
#include <signal.h>

// DEFINES
#define FAN_PIN 7
#define DEFAULT_TEMP 49
#define DEFAULT_REFRESH_TIME 10
#define DEFAULT_FALLBACK_TEMP 5

//FUNCTION DEFINITIONS
int get_cpu_temp();
void print_help();
void ctrl_c ();

//VARIABLES
int threshold_temp = DEFAULT_TEMP;
int target_temp = DEFAULT_TEMP - DEFAULT_FALLBACK_TEMP;
int refresh_time = DEFAULT_REFRESH_TIME; //5 minutes

unsigned char debug = 0;
int pin = FAN_PIN;
int cpu_temp = 0;

int main(int argc, char *argv[]){

	int opt;

	while ((opt = getopt(argc, argv, "t:p:r:vh")) != -1) {
		switch(opt) {
			case 't':
				threshold_temp = atoi(optarg);
				break;
			case 'p':
				pin = atoi(optarg);
				break;
			case 'r':
				refresh_time = atoi(optarg);
				break;
			case 'h':
				print_help();
				return 0;
				break;
			case 'v':
				debug = 1;
		}
	}

	if(debug){
		printf("VERBOSE MODE:\n");
		printf("\tThreshold temp: %d\n",threshold_temp);
		printf("\tPin: %d\n",pin);
		printf("\tRefresh time: %d\n",refresh_time);

	}
	signal (SIGINT, ctrl_c);

	if (wiringPiSetup () == -1) return -1;

	pinMode (pin, OUTPUT) ;
	target_temp = threshold_temp;
	while(1){

		cpu_temp = get_cpu_temp();

		if(cpu_temp >= target_temp){
			if(debug)	printf("TEMP: %d\tFAN ACTIVE\n",cpu_temp);
			digitalWrite(pin,HIGH);
			target_temp = threshold_temp - DEFAULT_FALLBACK_TEMP;
		}
		else{
			if(debug)	printf("TEMP: %d\tFAN STOPPED\n",cpu_temp);
			digitalWrite(pin,LOW);
			target_temp = threshold_temp;

		}
		sleep(refresh_time);

	}
	return 0;
}

int get_cpu_temp(){
	FILE *fp;
	char buff[5];
	int cpu_temp = 0;
	fp = fopen("/sys/class/thermal/thermal_zone0/temp", "r");
	if(fp==NULL) return -1;
	fscanf(fp, "%s", buff);
	cpu_temp = atoi(buff)/1000;
	fclose(fp);
	return cpu_temp;
}

void print_help(){
	printf("Controls fan by monitoring CPU temperature sensor\n");
	printf("\t-t : threshold temperature\n");
	printf("\t-p : pin (wiringPi convention)\n");
	printf("\t-r : refresh interval in seconds\n");
	printf("\tv  : verbose mode\n");

	printf("\nActual temperature: %d\n", get_cpu_temp());
}

/*
*		gracefully handle a Control C
*/
void ctrl_c ( ){
	printf("Ctrl C.\n");
	digitalWrite(pin,LOW);
	exit(0);
}
