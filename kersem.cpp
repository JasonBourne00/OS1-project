/*
 * kersem.cpp
 *
 *  Created on: Aug 12, 2021
 *      Author: OS1
 */
#include"kersem.h"
#include"Timer.h"
#include"PCB.h"
#include"SCHEDULE.H"
#include"semlist.h"
AllSem*KernelSem::svi_semafori=new AllSem();


KernelSem::KernelSem(int init){
	sem_list=new PCBList();
	uspavani=new SemList();
	this->value=init;
	KernelSem::svi_semafori->addSem(this);
}
KernelSem::~KernelSem(){
	KernelSem::svi_semafori->deleteSem(this);
	delete sem_list;
}
int KernelSem::val()const{
	return this->value;
}
int KernelSem::wait(Time time){
	value--;
	if(value<0){
		if(time>0){
			uspavani->put((PCB*)PCB::running,time);
			dispatch();
			if(((PCB*)PCB::running)->force_wakeup==1){
				((PCB*)PCB::running)->force_wakeup=0;
					  return 1; //ako se probudi signalom
				}else return 0;

		}else{
			block();
			return 1;
		}
	}
	else return 1;
}
void KernelSem::signal(){
	if(value++<0)unblock();
}
void KernelSem::block(){
	PCB::running->myStatus=blokirana;
	sem_list->put((PCB*)PCB::running);
	dispatch();
}
void KernelSem::unblock(){
	if(sem_list->isEmpty()==0){
	PCB*pomocna=sem_list->get();
	pomocna->myStatus=aktivna;
	Scheduler::put(pomocna);
 }
	else if(uspavani->get_size()>0){
	PCB*pomocna=uspavani->get_prinudno();
	pomocna->force_wakeup=1;
	pomocna->myStatus=aktivna;
		Scheduler::put(pomocna);

	}
}
