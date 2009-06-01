/*
 * 
 * mbblink       Motherboard LED Indicator and Watchdog.
 *
 * Version:      mbbblink  0.1.3  25-Sep-2008  jerungkun@gmail.com
 *
 * Description:
 *  C Version of combination of previous bash script mb_blink and watchdog program
 *  this program will loop to blink the led and feed the watchdog
 *
 */

#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <assert.h>
#include <ctype.h>
#include <time.h>

char *logfile;
int count;

volatile unsigned char *wdt_control;
volatile unsigned char *wdt_feed;
unsigned char *ledstart;

int fd;

/* append log file*/
void appendlog(char *logdata){
	FILE *fp;
	
	fp = fopen(logfile,"a+");
	
	if(fp) {
		fprintf(fp,"%s\n",logdata);
	}
		
	fclose(fp);	
}

/* cleanup process */
void Cleanup(int sig) {
	char strout[100];
	//printf("Process Terminated!\n");
	sprintf(strout,"mbblink terminate with count: %d", count);
	appendlog(strout);	

	munmap(&wdt_control,getpagesize());
	munmap(&wdt_feed,getpagesize());
	munmap(&ledstart,getpagesize());  

	close(fd);
	
	exit(sig);
}

/* cleanup process */
void AppClose() {
	char strout[100];
	//printf("Process Terminated!\n");
	sprintf(strout,"mbblink terminate with count: %d", count);
	appendlog(strout);	

	munmap(&wdt_control,getpagesize());
	munmap(&wdt_feed,getpagesize());
	munmap(&ledstart,getpagesize());  

	close(fd);
}

int main() {
	
	count = 0;
	logfile = "/var/log/rglog";
	int ledstat = 0;
	off_t ledaddr, ledpage;
	unsigned char *chardat, charval;
	unsigned int intval;
	unsigned int isetval;
	int ival;
	int iset=0;

	signal(SIGHUP, Cleanup);
	signal(SIGINT, Cleanup);
	signal(SIGQUIT, Cleanup);
	signal(SIGTERM, Cleanup);
	signal(SIGKILL, Cleanup);

	/* Initialize Watchdog */
	fd = open("/dev/mem", O_RDWR);
	assert(fd != -1);
	
	wdt_control = (unsigned char *)mmap(0,getpagesize(),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0x23800000);
	wdt_feed = (unsigned char *)mmap(0,getpagesize(),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0x23C00000);

	
	//printf("Get Direction...");
	ledaddr = 0x80840014;
	ledpage = ledaddr & 0xfffff000;
	
	ledstart = mmap(0, getpagesize(), PROT_READ|PROT_WRITE, MAP_SHARED, fd, ledpage);
	
	*wdt_feed=0x05;
	*wdt_control=0x07;

	/* 8 bit way */
	chardat = ledstart + (ledaddr & 0xfff);
	intval = (unsigned int)*chardat;
	/* end 8 bit way */
	//printf("Dir Value: 0x%X\n",intval); /* */
	
	ival = (intval & 0x08) >> 3;
	//printf("LED 3 Dir : %d\n",ival);
	if (ival != 1) iset = 1;
	
	ival = (intval & 0x80) >> 7;
	if (ival != 1) iset = 1;
		
	//printf("LED 7 Dir : %d\n",ival);
	
	if (iset == 1) {
		//printf("Set DIO 3 and 7 Dir as Output\n");

		chardat = ledstart + (ledaddr & 0xfff);
		intval = (unsigned int)*chardat;
		intval = intval | 0x88;
		charval = (unsigned char)intval;
		*chardat = charval; 
	}
	
	munmap(&ledstart,getpagesize());  

	//printf("Get LED Data...");
	ledaddr = 0x80840004;
	ledpage = ledaddr & 0xfffff000;

	ledstart = mmap(0, getpagesize(), PROT_READ|PROT_WRITE, MAP_SHARED, fd, ledpage);
	
	chardat = ledstart + (ledaddr & 0xfff);
	intval = (unsigned int)*chardat;
	
	//printf("Data Value: 0x%X\n",intval);
	
	ival = (intval & 0x08) >> 3;
	//printf("LED 3 Data : %d\n",ival);
	if (ival != 1) iset = 1;
	
	ival = (intval & 0x80) >> 7;
	if (ival != 1) iset = 1;
		
	//printf("LED 7 Data : %d\n",ival);

	ledstat = 1;
	
	while (1) {
		/* feed watchdog */
		*wdt_feed=0x05;

		/* blink led */
		if (ledstat == 1){
			//printf("Blink OFF\n");
			chardat = ledstart + (ledaddr & 0xfff);
			intval = (unsigned int)*chardat;
			intval = intval | 0x88; /* using OR to set bit 10001000 */
			charval = (unsigned char)(intval ^ 0x88); /* using XOR to set bit 00000000 */
			*chardat = charval; 
			
			ledstat=0;
		}
		else {
			//printf("Blink ON\n");

			chardat = ledstart + (ledaddr & 0xfff);
			intval = (unsigned int)*chardat;
			charval = (unsigned char)(intval | 0x88); /* using OR */

			*chardat = charval; 

			ledstat=1;
		}

		count++;
		if (count >= 600) {
			AppClose();
			return 0;
		}
		sleep(1);
	}

	return 0;
}
