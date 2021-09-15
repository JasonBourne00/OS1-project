/*
 * semaphor.cpp
 *
 *  Created on: Aug 12, 2021
 *      Author: OS1
 */
#include"semaphor.h"
#include"kersem.h"

Semaphore::Semaphore(int init){

	myImpl=new KernelSem(init);

	this->value=init;

}
Semaphore::~Semaphore(){
	delete myImpl;
	myImpl=0;
}

int Semaphore::wait(Time maxTime){
	return myImpl->wait(maxTime);
}
void Semaphore::signal(){
	myImpl->signal();
}
int Semaphore::val()const{
	return myImpl->val();
}



