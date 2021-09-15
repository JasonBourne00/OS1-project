/*
 * thread.cpp
 *
 *  Created on: Aug 10, 2021
 *      Author: OS1
 */

#include"thread.h"
#include"PCB.h"
#include"PCBList.h"
#include"Timer.h"
#include"Schedule.h"
#include<iostream.h>

ID Thread::IDgenerator=0;
PCBList* Thread::lista=new PCBList();

Thread::Thread(StackSize sz, Time timeslice){
	//Timer::lockFlag=0;
	myPCB=new PCB(this,sz,timeslice);
	lista->put(myPCB);
	myID=++IDgenerator;
	//Timer::lockFlag=1;

}
Thread::~Thread(){
	if(myPCB!=0)
	delete myPCB;

}
void Thread::start(){
	if(myPCB->myStatus==nova){
	myPCB->myStatus=aktivna;
	Scheduler::put(myPCB);
	}

}
ID Thread::getId(){
	return myID;
}
ID Thread::getRunningId(){
	return PCB::running->myThread->getId();
}
Thread* Thread::getThreadById(ID id){
	return lista->get_byID(id)->myThread;
}

void Thread::waitToComplete(){
	myPCB->wait_to_complete();
}
void dispatch(){
	//lock;
	_dispatch();
	//unlock;
}
