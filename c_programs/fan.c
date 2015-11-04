#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <stdint.h>
#include <softPwm.h>
#include <errno.h>
#include <string.h>

// Max and Min PWM values
#define MIN_FAN_SPEED 350
#define MAX_FAN_SPEED 1024


#define FAN_PWM_PIN 7

// Default values, if you dont define any other ones.
#define DEFAULT_MIN_TEMP 50
#define DEFAULT_MAX_TEMP 70
#define DEFAULT_REFRESH_TIME 300	// 5 min

int get_cpu_temp();
int map(long x, long in_min, long in_max, long out_min, long out_max);
void print_help();


// you need to add -lwiringPi to the compile arguments
int main(int argc, char *argv[]){

	int opt;

	int minimum = DEFAULT_MIN_TEMP;
	int maximum = DEFAULT_MAX_TEMP;
	int refresh_time = DEFAULT_REFRESH_TIME; //5 minutes
	unsigned char debug = 0;

	int cpu_temp = 0;
	int fan_speed = 0;

	while ((opt = getopt(argc, argv, "m:M:r:dh")) != -1) {
		switch(opt) {
			case 'm':
				minimum = atoi(optarg);
				break;
			case 'M':
				maximum = atoi(optarg);
				break;
			case 'r':
				refresh_time = atoi(optarg);
				break;
			case 'h':
				print_help();
				return 0;
				break;
			case 'd':
				debug = 1;
			case 's':
				printf("TEMP: %d\n",get_cpu_temp());
				return 0;
		}
	}

	if(debug){
		printf("DEBUG MODE:\n");
		printf("\tMinimum temp: %d\n",minimum);
		printf("\tMaximum temp: %d\n",maximum);
		printf("\tRefresh time: %d secs\n",refresh_time);
	}

	if (wiringPiSetup () == -1) return -1;

	if(softPwmCreate (FAN_PWM_PIN, 0, 1024)!=0) {
		printf("Error Initiating Software PWM on that pin\n %s\n", strerror(errno));
		return -1;
	}

	//pinMode (FAN_PWM_PIN, PWM_OUTPUT) ;

	while(1){

		cpu_temp = get_cpu_temp();
		fan_speed = map(cpu_temp,minimum,maximum,MIN_FAN_SPEED,MAX_FAN_SPEED);

		if(debug) printf("TEMP:%d\tFAN:%d/%d\n",cpu_temp,fan_speed,MAX_FAN_SPEED);
		else {
			softPwmWrite (FAN_PWM_PIN, fan_speed) ;
			//pwmWrite(FAN_PWM_PIN, fan_speed);
		}
		sleep(refresh_time);

	}
	return 0;
}

int map(long x, long in_min, long in_max, long out_min, long out_max)
{
	if(x<in_min) return 0;
	if(x>in_max) return MAX_FAN_SPEED;
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
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
	printf("Controls FAN PWM Output by monitoring CPU temperature sensor\n");
	printf("\t-m : minimum temp value\n");
	printf("\t-M : maximum temp value\n");
	printf("\t-r : refresh interval in seconds\n");
	printf("\t-d : debug mode, just writes the values on screen\n");
	printf("\t-s : show temperature and exits.\n");


	printf("\nActual temp: %d\n", get_cpu_temp());
}
