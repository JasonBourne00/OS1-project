/*
 * KernelEv.cpp
 *
 *  Created on: Aug 19, 2021
 *      Author: OS1
 */
#include"Timer.h"
#include"KernelEv.h"
#include"SCHEDULE.H"
#include"IVTEntry.h"
KernelEv::KernelEv(IVTNo ivt){
	value=0;
	broj_ulaza=ivt;
	blocked=0;
	creator=(PCB*)PCB::running;
	//IVTEntry::getIVT(ivt)->kernel_dogadjaj=this;
	IVTEntry::ulazi[ivt]=this;
}
KernelEv::~KernelEv(){
	IVTEntry::ulazi[this->broj_ulaza]=0;
	blocked=0;
	//blocked skini

}
void KernelEv::signal(){
	/*if(value==1) return;
	else{
		value=1;
		creator->myStatus=aktivna;
		Scheduler::put(creator);
	}*/
	if(value==1)return;
	if(blocked){
		blocked=0;
		creator->myStatus=aktivna;
		Scheduler::put(creator);
		//blocked->myStatus=aktivna;
		//Scheduler::put(blocked);
		//blocked=0;
	}else value=1;
}
void KernelEv::wait(){
	if(PCB::running==creator){
		if(value==0) {
			PCB::running->myStatus=blokirana;
			blocked=(PCB*)PCB::running; //ova linija je dodata
			dispatch();
		}
		else value=0;
	}
}

