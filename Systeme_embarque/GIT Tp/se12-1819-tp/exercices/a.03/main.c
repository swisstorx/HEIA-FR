/*
 * main.c
 *
 *  Created on: Oct 10, 2018
 *      Author: sven
 */
#include <stdio.h>

char* open(char* argv[]){
	char* param[]={"open",argv[0],argv[1],argv[2]};

	return *param;
}


int main(int argc,char* argv[]){

	printf("%s %s %s \n",argv[1],argv[2],argv[3]);


return 0;
}

