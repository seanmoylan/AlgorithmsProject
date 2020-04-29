// https://www.youtube.com/watch?v=SjyR74lbZOc

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

void print_usage() {
	printf("Usage: getopt_example -f <temp> | getopt_example -c <temp> \n");
	exit(2);
}

void print_farenheit(float temp){
	float f = ((temp * 9) / 5) + 32;
	printf("%.2f centegrade is %.2f farenheit\n", temp, f);
}

void print_centegrade(float temp){
	float c = ((temp - 32) * 5) / 9;
	printf("%.2f farenheit is %.2f centegrade\n", temp, c);
}

int main(int argc, char *argv[ ]) {
	if(argc < 2){
		print_usage();
	}

	int option;
	int cflag = 0;
	int fflag = 0;
	int tflag = 0;

	while((option = getopt(argc, argv, "c:f:t:")) != -1){
		switch(option){
			case 't':
				print_farenheit(44.4);
				exit(0);
				break;
			case 'c':
				if(cflag){
					print_usage();
					exit(1);
				}else{
					cflag++;
					fflag++;
					tflag++;
				}
				print_centegrade(atof(optarg));
				break;
			case 'f':
				if(fflag){
					print_usage();
					exit(1);
				}else{
					fflag++;
					cflag++;
					tflag++;
				}
				print_farenheit(atof(optarg));
				break;
			
			default:
				printf("Use -f or -c to convert to centegrade or farenheit\n");
		}
	}

}