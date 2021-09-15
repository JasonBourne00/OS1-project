/*
 * SemList.cpp
 *
 *  Created on: Aug 12, 2021
 *      Author: OS1
 */
#include"semlist.h"
#include"Timer.h"
#include"SCHEDULE.H"
#include"PCB.h"
#include<iostream.h>
#include"kersem.h"

SemList::SemList(){
	prvi=0; posl=0; prev=0; velicina=0;
}

SemList::~SemList(){
	Elem*pomocni=prvi;
	while(prvi!=0){
		pomocni=prvi;
		prvi=prvi->next;
		delete pomocni;
	}
	prvi=0; posl=0; prev=0; velicina=0;
}
void SemList::put(PCB*p, unsigned int t){
	p->myStatus=blokirana;
	velicina+=1;

	if(prvi==0){
		prvi=new Elem(p,t,0);
		posl=prvi;
	}
	else{
		unsigned int pom_time=t;
		if(pom_time>prvi->time){
			Elem*tek=prvi; prev=0;
			while(!(tek==0 ||  pom_time<=0)){
				if (((int) pom_time - (int) tek->time)>= 0){
				prev=tek;
				pom_time-=tek->time;
				tek=tek->next;
			}
				else break;

		}
			prev->next=new Elem(p,pom_time,tek);
	}
		else{
			prvi->time-=pom_time;
			prvi=new Elem(p,pom_time,prvi);
		}
	}
}

void SemList::otkucaj() {
		if (prvi == 0) {
			return;
		}
		prvi->time -= 1;
		PCB* cur;
		while ((cur = get()) != 0) {
			cur->myStatus = aktivna;
			Scheduler::put(cur);
		}
	}

PCB* SemList::get() {
	if (prvi && prvi->time==0) {
		Elem* temp = prvi;
		PCB* ret = temp->pcb;
		prvi = prvi->next;
		ret->force_wakeup=0;
		velicina-=1;
		delete temp;
		return ret;
	} else
		return 0;
}
PCB*SemList::get_prinudno(){
	if (prvi) {
		Elem* temp = prvi;
		Elem*drugi;
		if(prvi->next!=0) {drugi=prvi->next;
		drugi->time+=prvi->time;
		}
		PCB* ret = temp->pcb;
		prvi = prvi->next;
		velicina-=1;
		delete temp;
		if(prvi==0)posl=0;
		return ret;
		} else
		return 0;
}
