#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>

float get_cpu_temp();

int main()
{
	unsigned int decimals = 0;
	float cpu_temp = 0;
	while ((opt = getopt(argc, argv, "d")) != -1) {
		switch(opt) {
			case 'd':
				decimals = 1;
				break;
		}
	}

	cpu_temp = get_cpu_temp();

	if(decimals)printf("<txt>%.1f ºC</txt>\n",cpu_temp);
	else printf("<txt>%d ºC</txt>\n",(int) cpu_temp);

	return 0;
}

float get_cpu_temp(){
	FILE *fp;
	char buff[5];
	float cpu_temp = 0;
	fp = fopen("/sys/class/thermal/thermal_zone0/temp", "r");
	if(fp==NULL) return -1;
	fscanf(fp, "%s", buff);
	cpu_temp = (float)atoi(buff)/1000;
	fclose(fp);
	return cpu_temp;
}
