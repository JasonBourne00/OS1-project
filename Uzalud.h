/*
 * Uzalud.h
 *
 *  Created on: Aug 13, 2021
 *      Author: OS1
 */

#ifndef UZALUD_H_
#define UZALUD_H_
#include"thread.h"
#include<iostream.h>
class Uzalud:public Thread{

public:
	Uzalud():Thread(1024,1){}
	virtual void run();
};


#endif /* UZALUD_H_ */
