#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/fcntl.h>

int main(int argc, char *argv[])
{
	int fd = -1, ret;
	
	char *tmp1, tmp2[10], ch='t';
	char devname_head[50] =	
	"/sys/devices/w1_bus_master1/28-00000";
	char devname_end[10] = "/w1_slave";
	char dev_name[100];
	
	long value;
	int integer, decimal;
	char buffer[100];

	int i,j;
	
	strcpy(dev_name, devname_head);
	strcat(dev_name, argv[1]);
	strcat(dev_name, devname_end);
	
	if ((fd = open(dev_name, O_RDONLY)) < 0)
	{
		perror("Greška pri otvaranju!");
		exit(1);
	}
	
	ret = read(fd, buffer, sizeof(buffer));
	if (ret < 0)
	{
		perror("Greška pri čitanju!");
		exit(1);
	}

	tmp1 = strchr(buffer, ch);
	sscanf(tmp1, "t=%s", tmp2);
	value = atoi(tmp2);

	integer = value / 1000;
	decimal = value % 1000;
	printf("Temperatura je %d.%d\n", integer,decimal);
	close(fd);
	
	return 0;
}