/*
 * Allsem.cpp
 *
 *  Created on: Aug 17, 2021
 *      Author: OS1
 */

#include"Allsem.h"
#include"kersem.h"

AllSem::AllSem(){
	prvi=posl=0;
}
AllSem::~AllSem(){
	Elem*pom;
	while(prvi){
		pom=prvi;
		prvi=prvi->next;
		delete pom;
	}
	prvi=posl=0;
}

void AllSem::addSem(KernelSem*k){

	Elem*novi=new Elem(k,0);
	if(prvi==0){
		prvi=novi;
	}
	else posl->next=novi;
	posl=novi;
}
void AllSem::tick_all(){
	Elem*pom=prvi;
	while(pom){
		pom->data->uspavani->otkucaj();
		pom=pom->next;
	}
}

void AllSem::deleteSem(KernelSem*del){
	Elem*pom= 0;
	Elem*tek=prvi;
			while(tek && tek->data!=del){
				pom = tek;
				tek= tek->next;
			}
			if (!tek) return;

			if(tek == prvi) {
				 if (prvi ==0) posl = 0;
				 else {prvi = prvi->next; delete tek;}
			}
			else if(tek == posl) {posl = pom; delete tek; posl->next = 0;}
			else {pom -> next = tek -> next; delete tek;}
}
