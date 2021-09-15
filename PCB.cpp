/*
 * PCB.cpp
 *
 *  Created on: Aug 10, 2021
 *      Author: OS1
 */


#include"PCB.h"
#include"thread.h"
#include"SCHEDULE.H"
#include<dos.h>
#include"PCBList.h"
#include"Timer.h"
#include<iostream.h>
#include"Uzalud.h"

volatile PCB* PCB::running=0;
Uzalud* PCB::holder=0;
volatile unsigned PCB::brojac_niti=0;

void PCB::wrapper(){
	PCB::running->myThread->run();
	PCB::running->myStatus=zavrsena;
	PCB::brojac_niti--;
	PCB*pomocna;

	for(;(PCB*)PCB::running->waitlist->isEmpty()==0;){
		pomocna=(PCB*)PCB::running->waitlist->get();
		pomocna->myStatus=aktivna;
		Scheduler::put(pomocna);
	}
	dispatch();
}

void PCB::wait_to_complete(){
	if(!(this==(PCB*)PCB::running || this->myStatus==zavrsena || myStatus==nova || this->myThread==PCB::holder)){
		//Timer::lockFlag=0;
		PCB::running->myStatus=blokirana;
		if(waitlist!=0)
		this->waitlist->put((PCB*)PCB::running);
		//Timer::lockFlag=1;
		dispatch();
	}
}
void _dispatch(){
	lock();
	Timer::zahtev_za_promenu=1;
	Timer::timer();
	unlock();
}
PCB::PCB(Thread*myThr, StackSize sz, Time timeSlice){
	sp=ss=bp=0;
	force_wakeup=0;
	this->myThread=myThr;
	this->myStatus=nova;
	size=sz;
	waitlist=new PCBList;
	//if(sz>defaultStackSize)size=defaultStackSize;
	//else size=sz;
	size/=sizeof(unsigned);
	stack=new unsigned[size];
	if(stack){
		stack[size-1]=0x200;
#ifndef BCC_BLOCK_IGNORE
	stack[size-2] = FP_SEG(&(wrapper));
	stack[size-3] = FP_OFF(&(wrapper));

	sp = FP_OFF(stack+size-12);
	ss = FP_SEG(stack+size-12);
	bp = sp;
#endif
	if(timeSlice!=0){
		this->timeslice=timeSlice;
		neogranicen=0;
	}else{
		neogranicen=1;
		this->timeslice=0;
	}

	}
	else this->stack=0;
}
PCB::~PCB(){
	wait_to_complete();
	if(stack!=0){
		delete stack;
	}
	if(waitlist!=0) delete waitlist;
}

