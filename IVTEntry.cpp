/*
 * IVTEntry.cpp
 *
 *  Created on: Aug 19, 2021
 *      Author: OS1
 */

#include"IVTEntry.h"
#include<dos.h>
#include"KernelEv.h"
KernelEv** IVTEntry::ulazi=new KernelEv*[256] ;

IVTEntry::IVTEntry(IVTNo entr,pInterrupt rutina){
	this->entry=entr;
	//newRoutine=rutina;
	kernel_dogadjaj=0;
#ifndef BCC_BLOCK_IGNORE
	asm cli;
	oldRoutine=getvect(entr);
	setvect(entr,rutina);
	asm sti;
#endif
	//ulazi[entr]=this; iz prve verzije
}
IVTEntry::~IVTEntry(){
#ifndef BCC_BLOCK_IGNORE
	asm cli;
	setvect(entry,oldRoutine);
	asm sti;
#endif
	ulazi[entry]=0;
	oldRoutine();
}
void IVTEntry::callOldRoutine(){
	oldRoutine();
}
void IVTEntry::signal(){
	if(ulazi[entry]!=0){
		ulazi[entry]->signal();
		//ovde u if ide ulazi[entry]!=0;
		//kernel_dogadjaj->signal();
		//ulaz[entry] signal
	}
}
//IVTEntry* IVTEntry::getIVT(IVTNo i){
//return ulazi[i];
//}
