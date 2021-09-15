/*
 * PCBList.cpp
 *
 *  Created on: Aug 10, 2021
 *      Author: OS1
 */
#include "PCBList.h"
#include "PCB.h"

PCBList::PCBList() {
	first = 0;
	last = 0;
	pomocni=0;
}

PCBList::~PCBList() {
	while (!isEmpty()) {
		pomocni = first;
		first = pomocni->next;
		delete pomocni;
	}
}

void PCBList::put(PCB* info) {
	Elem* nel = new Elem(info);
	if (first == 0)
		first = nel;
	else
		last->next = nel;
	last = nel;
}
PCB* PCBList::get() {
	if (first== 0) return 0;
	pomocni = first;
	PCB* ret = first->info;
	first = first->next;
	delete pomocni;
	if (first == 0) last = 0;
	return ret;
}
PCB* PCBList::get_byID(unsigned id){
	if(first==0)return 0;
	pomocni=first;
	while(pomocni!=0){
		if(pomocni->info->myThread->getId()==id)return pomocni->info;
		else pomocni=pomocni->next;
	}
	return 0;

}

int PCBList::isEmpty() {
	if (first == 0)
		return 1;
	else
		return 0;
}
