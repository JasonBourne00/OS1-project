/*
 * Event.cpp
 *
 *  Created on: Aug 19, 2021
 *      Author: OS1
 */

#include"Event.h"
#include"KernelEv.h"
Event::Event(IVTNo iv){
	myImpl=new KernelEv(iv);
}
Event::~Event(){
	delete myImpl;
	myImpl=0;
}

void Event::wait(){
	myImpl->wait();
}
void Event::signal(){
	myImpl->signal();

}
