#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>

float get_cpu_temp();

int main()
{
	float cpu_temp = 0;
	cpu_temp = get_cpu_temp();

	printf("<txt>%.1f ºC</txt>\n",cpu_temp);

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
