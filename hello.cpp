/*
 * hello.cpp
 *
 *  Created on: Apr 1, 2015
 *      Author: OS1
 */

#include <iostream.h>
#include"declare.h"
extern int userMain(int argc,char**argv);
void main(int argc, char**argv)
{
	Timer::inicijalizuj();

	userMain(argc,argv);

	Timer::restore();
}


